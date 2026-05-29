#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    uint64_t w[4];
} state256_t;

/* -------------------------------------------------
 * Utility functions
 * ------------------------------------------------- */
static inline uint64_t rotl64(uint64_t x, unsigned int n) {
    n &= 63;
    return (x << n) | (x >> (64 - n));
}

/* -------------------------------------------------
 * Sub-operations
 * ------------------------------------------------- */

/* 64-bit wise rotation */
void rotate_words_left_64wise(state256_t *state, state256_t* comp, const unsigned int rot[4]) {
    for (int i = 0; i < 4; i++) {
		for(unsigned int j = 0;j < 64; j++){
			if(rotl64(state->w[i], j) == comp->w[i]){
				printf("rot[%d]: %d\n", i, j);
				break;
			}
		}
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
        state->w[i] -= constants1[i];
    }
}

/* -------------------------------------------------
 * 1) One-round permutation:
 *    rotation -> XOR -> shuffling -> add
 *    (uses a fixed reverse-byte shuffle internally)
 * ------------------------------------------------- */
void permute_one_round(state256_t* comp, state256_t *state,
                       const unsigned int rot[4],
                       const uint8_t shuffle_map[32],
                       const uint64_t constants2[4],
                       const uint64_t constants1[4]) {
	add_constants_64wise(state, constants1); 
	shuffle_bytes_256(state, shuffle_map); 
	xor_constants_256wise(state, constants2); 
	rotate_words_left_64wise(state, comp, rot);
    //rotate_words_left_64wise(state, rot); xor_constants_256wise(state, constants2); shuffle_bytes_256(state, shuffle_map); add_constants_64wise(state, constants1);// TODO: Complete this implementation.
}

/* -------------------------------------------------
 * 3) Main: test + timing
 * ------------------------------------------------- */
int main(void) {
    /* one-round test parameters */
    // TODO: Set rot to proper values.
    const unsigned int rot[4] = { 0, 0, 0, 0 };

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

    printf("=== Test 1: Find rot value ===\n");
    {
        FILE *fv = fopen("testvector.txt", "r");
        if (!fv) {
            perror("fopen testvector.txt for read");
            return 1;
        }

        char line[64];
        int n = 0;
        int all_ok = 1;

        fgets(line, sizeof(line), fv);
            if (line[0] == '#') {
                unsigned long long in0, in1, in2, in3;
                unsigned long long out0, out1, out2, out3;

                fgets(line, sizeof(line), fv);  /* "input" */
                if (fscanf(fv, "%llx %llx %llx %llx",
                           &in0, &in1, &in2, &in3) != 4) {
                    all_ok = 0;
                }
                fgets(line, sizeof(line), fv); /* end of numbers line */
                fgets(line, sizeof(line), fv); /* "output" */
                fscanf(fv, "%llx %llx %llx %llx",
                           &out0, &out1, &out2, &out3);
               
                fgets(line, sizeof(line), fv); /* end of output numbers line */

        state256_t vin = { .w = { in0, in1, in2, in3 } };
        state256_t vout ={ .w = { out0, out1, out2, out3 } };

        permute_one_round(&vin, &vout, rot, shuffle_map, constants2, constants1);

            }
        fclose(fv);

	}

    return 0;
}
