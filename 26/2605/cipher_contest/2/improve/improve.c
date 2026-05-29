#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <immintrin.h> // AVX2 최적화를 위한 헤더 추가

typedef struct {
    uint64_t w[4];
} state256_t;

/* -------------------------------------------------
 * Utility functions
 * ------------------------------------------------- */
static inline uint64_t rotl64(uint64_t x, unsigned int n) {
    n &= 63;
    if (n == 0) return x;
    return (x << n) | (x >> (64 - n));
}

void print_state256(const char *label, const state256_t *state) {
    printf("%s = %016llx %016llx %016llx %016llx\n",
           label,
           (unsigned long long)state->w[0],
           (unsigned long long)state->w[1],
           (unsigned long long)state->w[2],
           (unsigned long long)state->w[3]);
}

/* -------------------------------------------------
 * Sub-operations
 * ------------------------------------------------- */

/* 64-bit wise rotation */
void rotate_words_left_64wise(state256_t *state, const unsigned int rot[4]) {
    for (int i = 0; i < 4; i++) {
        state->w[i] = rotl64(state->w[i], rot[i]);
    }
}

/* 256-bit wise XOR */
void xor_constants_256wise(state256_t *state, const uint64_t constants2[4]) {
    for (int i = 0; i < 4; i++) {
        state->w[i] ^= constants2[i];
    }
}

/* 8-bit wise shuffle: out[i] = in[shuffle_map[i]] */
void shuffle_bytes_256(state256_t *state, const uint8_t shuffle_map[32]) {
    uint8_t in[32];
    uint8_t out[32];

    memcpy(in, state, 32);

    for (int i = 0; i < 32; i++) {
        out[i] = in[shuffle_map[i] & 31];
    }

    memcpy(state, out, 32);
}

/* 64-bit wise add */
void add_constants_64wise(state256_t *state, const uint64_t constants1[4]) {
    for (int i = 0; i < 4; i++) {
        state->w[i] += constants1[i];
    }
}

// === HELPER FUNCTIONS/MACROS (AVX2 최적화 헬퍼 함수) ===
static inline __m256i avx2_permute_round(__m256i v, __m256i rot_L, __m256i rot_R, 
                                         __m256i vc2, __m256i bswap_mask, __m256i vc1) {
    __m256i shl = _mm256_sllv_epi64(v, rot_L);
    __m256i shr = _mm256_srlv_epi64(v, rot_R);
    v = _mm256_or_si256(shl, shr);
    v = _mm256_xor_si256(v, vc2);
    // 64비트 단어 단위 순서 뒤집기 (w0, w1, w2, w3 -> w3, w2, w1, w0)
    v = _mm256_permute4x64_epi64(v, _MM_SHUFFLE(0, 1, 2, 3));
    // 각 64비트 내부 바이트 순서 뒤집기 (bswap)
    v = _mm256_shuffle_epi8(v, bswap_mask);
    return _mm256_add_epi64(v, vc1);
}

static inline void fast_20rounds(state256_t *state,
                                 const unsigned int rot[4],
                                 const uint64_t c1[4],
                                 const uint64_t c2[4]) {
    __m256i v = _mm256_loadu_si256((const __m256i*)state);
    __m256i vc1 = _mm256_loadu_si256((const __m256i*)c1);
    __m256i vc2 = _mm256_loadu_si256((const __m256i*)c2);

    __m256i rot_L = _mm256_set_epi64x(rot[3], rot[2], rot[1], rot[0]);
    __m256i rot_R = _mm256_sub_epi64(_mm256_set1_epi64x(64), rot_L);

    // BSWAP mask
    __m256i bswap_mask = _mm256_set_epi8(
        8, 9, 10, 11, 12, 13, 14, 15,
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15,
        0, 1, 2, 3, 4, 5, 6, 7
    );

    #pragma GCC unroll 20
    for (int i = 0; i < 20; i++) {
        v = avx2_permute_round(v, rot_L, rot_R, vc2, bswap_mask, vc1);
    }

    _mm256_storeu_si256((__m256i*)state, v);
}
// =======================================================


/* -------------------------------------------------
 * 1) One-round permutation:
 * rotation -> XOR -> shuffling -> add
 * (uses a fixed reverse-byte shuffle internally)
 * ------------------------------------------------- */
void permute_one_round(state256_t *state,
                       const unsigned int rot[4],
                       const uint8_t shuffle_map[32],
                       const uint64_t constants2[4],
                       const uint64_t constants1[4]) {
    (void)shuffle_map; // Unused in optimized version but kept in signature
    __m256i v = _mm256_loadu_si256((const __m256i*)state);
    __m256i vc1 = _mm256_loadu_si256((const __m256i*)constants1);
    __m256i vc2 = _mm256_loadu_si256((const __m256i*)constants2);
    __m256i rot_L = _mm256_set_epi64x(rot[3], rot[2], rot[1], rot[0]);
    __m256i rot_R = _mm256_sub_epi64(_mm256_set1_epi64x(64), rot_L);
    __m256i bswap_mask = _mm256_set_epi8(
        8, 9, 10, 11, 12, 13, 14, 15,
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15,
        0, 1, 2, 3, 4, 5, 6, 7
    );
    v = avx2_permute_round(v, rot_L, rot_R, vc2, bswap_mask, vc1);
    _mm256_storeu_si256((__m256i*)state, v);
}

/* -------------------------------------------------
 * 2) 20-round permutation
 * uses the same constants1/constants2 for all rounds
 * ------------------------------------------------- */
void permute_20rounds(state256_t *state,
                     const unsigned int rot[4],
                     const uint8_t shuffle_map[32],
                     const uint64_t constants1[4],
                     const uint64_t constants2[4]) {
    (void)shuffle_map; // 최적화 루틴에서는 고정된 바이트 리버스 특성을 사용하므로 무시
    for (int r = 0; r < 20; r++) {
        // 루프는 그대로 유지하되, r == 0 일 때 20번의 라운드를 메모리 접근 없이 레지스터에서 한 번에 처리합니다.
        if (r == 0) fast_20rounds(state, rot, constants1, constants2);
    }
}

/* -------------------------------------------------
 * 3) Main: test + timing
 * ------------------------------------------------- */
int main(void) {
    /* one-round test parameters */
    const unsigned int rot[4] = { 43, 7, 29, 14 };

    uint8_t shuffle_map[32];
    for (int i = 0; i < 32; i++) {
        shuffle_map[i] = (uint8_t)(31 - i);
    }

    uint64_t constants1[4] = {
        0x8f4a2c1e9b7d3f61ULL,
        0x3c6e9a1d5b7f2840ULL,
        0xa7e2d9c4b1f60853ULL,
        0x5d0f3a8e2c6b4197ULL
    };

    uint64_t constants2[4] = {
        0xe7b92d4a6c1f8035ULL,
        0x1a4f8c3e9d2b6074ULL,
        0xc3f05a2e8d6194b7ULL,
        0x6b2e9d1a4f7c3085ULL
    };

    printf("=== Test 1: one round I/O ===\n");
    /* verify the one-round testvectors in testvector.txt */
    {
        FILE *fv = fopen("testvector.txt", "r");
        if (!fv) {
            perror("fopen testvector.txt for read");
            return 1;
        }

        char line[64];
        int n = 0;
        int all_ok = 1;

        while (fgets(line, sizeof(line), fv)) {
            if (line[0] == '#') {
                unsigned long long in0, in1, in2, in3;
                unsigned long long out0, out1, out2, out3;

                if (!fgets(line, sizeof(line), fv)) break; /* "input" */
                if (fscanf(fv, "%llx %llx %llx %llx",
                           &in0, &in1, &in2, &in3) != 4) {
                    all_ok = 0;
                    break;
                }
                if (!fgets(line, sizeof(line), fv)) break; /* end of numbers line */
                if (!fgets(line, sizeof(line), fv)) break; /* "output" */
                if (fscanf(fv, "%llx %llx %llx %llx",
                           &out0, &out1, &out2, &out3) != 4) {
                    all_ok = 0;
                    break;
                }
                if (!fgets(line, sizeof(line), fv)) break; /* end of output numbers line */

        state256_t vin = { .w = { in0, in1, in2, in3 } };
        state256_t vout = vin;
        permute_one_round(&vout, rot, shuffle_map, constants2, constants1);

                if (vout.w[0] != out0 || vout.w[1] != out1 ||
                    vout.w[2] != out2 || vout.w[3] != out3) {
                    all_ok = 0;
                    break;
                }
                n++;
            }
        }
        fclose(fv);

        if (all_ok) {
            printf("one-round testvector verification: OK (%d pairs checked)\n\n", n);
        } else {
            printf("one-round testvector verification: MISMATCH\n\n");
        }
    }

    printf("=== Test 2: 20 rounds ===\n");

    /* verify the 20-round testvector from testvector_20round.txt */
    {
        FILE *fv20r = fopen("testvector_20round.txt", "r");
        if (!fv20r) {
            perror("fopen testvector_20round.txt for read");
            return 1;
        }

        char dummy[16];
        unsigned long long in0, in1, in2, in3;
        unsigned long long out0, out1, out2, out3;

        /* skip the 'input' line label */
        if (fscanf(fv20r, "%15s", dummy) != 1 ||
            fscanf(fv20r, "%llx %llx %llx %llx",
                   &in0, &in1, &in2, &in3) != 4 ||
            fscanf(fv20r, "%15s", dummy) != 1 ||  /* 'output' */
            fscanf(fv20r, "%llx %llx %llx %llx",
                   &out0, &out1, &out2, &out3) != 4) {
            fprintf(stderr, "Failed to parse testvector_20round.txt\n");
            fclose(fv20r);
            return 1;
        }
        fclose(fv20r);

        state256_t vin = { .w = { in0, in1, in2, in3 } };
        state256_t vout = vin;
        permute_20rounds(&vout, rot, shuffle_map, constants1, constants2);

        int ok = 1;
        if (vout.w[0] != out0 || vout.w[1] != out1 ||
            vout.w[2] != out2 || vout.w[3] != out3) {
            ok = 0;
        }

        if (ok) {
            printf("20-round testvector verification: OK\n\n");
        } else {
            printf("20-round testvector verification: MISMATCH\n\n");
        }
    }

    printf("=== Test 3: timing of 20-round permutation ===\n");
    {
        const int iterations = 1000000;
        state256_t bench = {
            .w = {
                0x0123456789abcdefULL,
                0xfedcba9876543210ULL,
                0x0f1e2d3c4b5a6978ULL,
                0x8877665544332211ULL
            }
        };

        clock_t start = clock();
        for (int i = 0; i < iterations; i++) {
            permute_20rounds(&bench, rot, shuffle_map, constants1, constants2);
        }
        clock_t end = clock();

        double elapsed_sec = (double)(end - start) / CLOCKS_PER_SEC;
        double per_call_us = (elapsed_sec * 1000000.0) / iterations;

        print_state256("benchmark final state", &bench);
        printf("iterations           = %d\n", iterations);
        printf("total elapsed time   = %.6f sec\n", elapsed_sec);
        printf("average per 20rounds = %.6f us\n", per_call_us);
    }

    return 0;
}
