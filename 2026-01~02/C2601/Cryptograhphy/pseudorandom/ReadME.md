# 의사난수(Pseudo-Random Number Generator, PRNG) 완전 가이드

## 1. 난수란 무엇인가?

**진난수(True Random Number)** 는 물리적 현상(방사성 붕괴, 열잡음, 광자 편광 등)에서 생성되는 완전히 예측 불가능한 수입니다. 반면 **의사난수(Pseudo-Random Number)** 는 결정론적 알고리즘으로 생성되지만, 통계적으로 난수처럼 보이는 수열입니다.

핵심 개념: **시드(Seed)** — 같은 시드를 넣으면 항상 같은 수열이 나옵니다. 이것이 의사난수의 본질적 특성이자 한계입니다.

---

## 2. 역사적 흐름

```
1946  Middle-Square Method        (Von Neumann)
 
	=>

1948  Linear Congruential Gen.    (Lehmer)

	=>

1965  Tausworthe Generator        (Tausworthe)

	=>

1979  Blum Blum Shub              (암호학적 PRNG 시대 시작)

	=>

1997  Mersenne Twister            (현대 범용 PRNG의 표준)

	=>

2003  WELL (MT 개선)

	=>

2009  ChaCha20 / Salsa20          (암호학적 PRNG 혁신)

	=>

2014  PCG Family                  (현재 가장 균형잡힌 범용 PRNG)

	=>

2019  xoshiro / xoroshiro         (초경량 고성능 PRNG)
```

---
<br> </br> <br> </br>

## 3. 각 알고리즘 상세 설명

### 🔴 Middle-Square Method (1946, Von Neumann)

역사상 최초의 의사난수 알고리즘입니다. 폰 노이만이 맨하튼 프로젝트 중 제안했습니다.

**로직:**
1. n자리 시드를 제곱한다
2. 결과의 가운데 n자리를 추출한다
3. 그 값을 다음 시드로 사용한다

```
시드: 1234
1234² = 01522756
중간 4자리 → 5227
5227² = 27321529
중간 4자리 → 3215
...
```

**문제점:** 0에 수렴하거나 짧은 주기에 빠지는 경우가 자주 발생합니다 (예: 0000² = 0000, 무한 반복). 폰 노이만 본인도 "이 방법을 신뢰하는 사람은 죄악 상태에 있다"고 말했습니다.

---

### 🟠 Linear Congruential Generator, LCG (1948, Lehmer)

수십 년간 가장 널리 쓰인 알고리즘으로, C의 `rand()`, Java의 `java.util.Random` 등에 사용되었습니다.

**점화식:**
```
Xₙ₊₁ = (a × Xₙ + c) mod m
```
- `m`: 모듈러스 (주기의 최대값, 보통 2³²)
- `a`: 승수 (multiplier)
- `c`: 증분 (increment)
- `X₀`: 시드

**대표적인 파라미터 (glibc):**
```
m = 2³¹,  a = 1103515245,  c = 12345
```

**Hull-Dobell 정리** — 주기가 m이 되려면:
1. c와 m이 서로소
2. m의 모든 소인수 p에 대해 (a-1)이 p의 배수
3. m이 4의 배수면 (a-1)도 4의 배수

**장점:** 매우 빠르고, 구현이 단순합니다.

**단점:** 하위 비트의 주기가 매우 짧고, 3D 공간에 점을 찍으면 평면 위에 배열되는 구조적 패턴이 나타납니다 (Marsaglia의 발견).

---

### 🟡 Linear Feedback Shift Register, LFSR (1965, Tausworthe)

하드웨어 구현에 최적화된 알고리즘입니다. 비트 시프트와 XOR 연산만 사용합니다.

**로직:**
레지스터의 특정 비트들을 XOR해서 새 비트를 만들고, 전체를 한 칸 시프트합니다.

```
레지스터: [1 0 1 1 0 1 0 1]  (8비트 예시)
탭 위치:  8, 6, 5, 4번째 비트 XOR
새 비트: 1 XOR 0 XOR 1 XOR 0 = 0
시프트 후: [0 1 0 1 1 0 1 0]
```

**탭 다항식(Primitive Polynomial)** 에 의해 최대 주기 `2ⁿ - 1`이 보장됩니다. 예: 32비트 LFSR의 최대 주기는 약 43억입니다.

**용도:** Wi-Fi(802.11), Bluetooth, GPS, 스트림 암호의 기반 구조로 활용됩니다.

---

### 🟢 Mersenne Twister, MT19937 (1997, 松本 & 西村)

현재까지도 Python(`random` 모듈), R, Ruby, PHP 등 수많은 언어의 기본 PRNG입니다.

**핵심 파라미터:**
- 주기: **2¹⁹⁹³⁷ - 1** (메르센 소수, 천문학적 주기)
- 상태 크기: 624 × 32비트 = 19,968비트
- 차원: 623차원 균등분포 보장

**로직 (3단계):**

**① 초기화:** 624개의 32비트 정수로 상태 배열 구성

**② Twist (핵심 변환):**
```python
# 624번 반복
y = (mt[i] & 0x80000000) | (mt[(i+1) % 624] & 0x7fffffff)
mt[i] = mt[(i+397) % 624] ^ (y >> 1)
if y % 2 != 0:
    mt[i] ^= 0x9908b0df  # 매직 넘버
```

**③ Tempering (출력 품질 향상):**
```python
y = mt[index]
y ^= (y >> 11)
y ^= (y << 7)  & 0x9d2c5680
y ^= (y << 15) & 0xefc60000
y ^= (y >> 18)
```

**치명적 단점:** 624개의 연속 출력값을 관측하면 내부 상태 전체를 역산할 수 있어, **암호학적으로 안전하지 않습니다.**

---

### 🔵 PCG (Permuted Congruential Generator) (2014, O'Neill)

LCG의 빠른 속도 + 출력 단계의 순열(Permutation)을 결합한 현대적 알고리즘입니다.

**로직:**
```
내부 상태: 128비트 LCG로 전진
출력 함수: 상태의 일부를 ROR(Rotate Right) + XOR로 뒤섞기

state = state × 6364136223846793005 + increment
xorshifted = ((state >> 18) ^ state) >> 27
rot = state >> 59
output = (xorshifted >> rot) | (xorshifted << ((-rot) & 31))
```

LCG의 구조적 패턴 문제를 출력 단계의 비선형 회전으로 완전히 제거했습니다.

**장점:** 빠르고, 통계 품질이 뛰어나며, 크기도 작습니다 (128비트 상태). 현재 많은 언어의 기본 PRNG로 채택 추세입니다.

---

### 🟣 xoshiro / xoroshiro (2018~2019, Blackman & Vigna)

"xor + shift + rotate"의 조합으로, 게임 엔진·임베디드 시스템 등 극한의 성능이 필요한 곳에 사용됩니다.

**xoshiro256 예시 (256비트 상태):**
```c
uint64_t s[4];  // 상태 4개

uint64_t result = rotl(s[1] * 5, 7) * 9;

// 상태 업데이트
uint64_t t = s[1] << 17;
s[2] ^= s[0]; s[3] ^= s[1];
s[1] ^= s[2]; s[0] ^= s[3];
s[2] ^= t;
s[3] = rotl(s[3], 45);
```

단 4개의 변수, 몇 개의 XOR/시프트/회전 연산으로 통계적으로 우수한 수열을 생성합니다. Rust, Julia 등의 기본 PRNG로 사용됩니다.

---

### 🔒 암호학적 PRNG (CSPRNG)

일반 PRNG와 달리, 과거 출력으로 미래를 예측할 수 없는 **계산적 안전성**을 보장합니다.

| 알고리즘 | 기반 | 사용처 |
|---|---|---|
| ChaCha20 | 스트림 암호 | Linux `/dev/urandom`, TLS |
| Fortuna | AES + 엔트로피 풀 | macOS, iOS |
| HMAC-DRBG | HMAC-SHA256 | NIST 표준 |
| Blum Blum Shub | 이론적 기반 | 수학적 증명용 |

**OS 레벨 CSPRNG:**
- Linux: `getrandom()` 시스템콜, 하드웨어 인터럽트·네트워크 타이밍 등을 엔트로피 소스로 사용
- Windows: `BCryptGenRandom()`

---

## 4. 품질 평가: 통계 테스트

의사난수의 품질은 수학적 테스트로 검증합니다.

**대표적인 테스트 스위트:**
- **Diehard Tests** (Marsaglia, 1995) — Birthday spacing, Overlapping permutations 등
- **TestU01** (L'Ecuyer, 2007) — SmallCrush(10개), Crush(96개), BigCrush(106개) 테스트
- **PractRand** — 현재 가장 엄격한 테스트, 수 TB의 출력을 분석

| PRNG | BigCrush | 속도 | 상태 크기 | 암호학적 안전 |
|---|---|---|---|---|
| LCG | ❌ 실패 | 매우 빠름 | 32~64비트 | ❌ |
| MT19937 | ✅ 통과 | 빠름 | 2.5KB | ❌ |
| PCG | ✅ 통과 | 매우 빠름 | 16바이트 | ❌ |
| xoshiro256 | ✅ 통과 | 최고속 | 32바이트 | ❌ |
| ChaCha20 | ✅ 통과 | 빠름 | 가변 | ✅ |

---

## 5. 언제 어떤 PRNG를 써야 하는가?

| 용도 | 권장 알고리즘 |
|---|---|
| 시뮬레이션·통계·게임 | PCG 또는 xoshiro256 |
| 암호학·보안·토큰 | OS 제공 CSPRNG (`getrandom`, `BCryptGenRandom`) |
| 재현 가능한 실험 | MT19937 (시드 고정) |
| 극한 성능·임베디드 | xoroshiro128 |
| 레거시 코드 유지 | LCG (단, 보안 무관한 용도만) |

---

> 의사난수는 단순한 수학 공식에서 시작해, 현대 암호학·통계학·게임 개발까지 컴퓨팅 전반에 깊숙이 뿌리내린 분야입니다.
