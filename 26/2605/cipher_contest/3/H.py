#!/usr/bin/env python3
"""
GF(2^128) 위의 6차 방정식 풀이기
기약다항식: x^128 + x^7 + x^2 + x + 1  (AES-GCM 표준)

알고리즘:
  - gcd(f, x^(2^128) - x) 로 서로 다른 근들의 squarefree 다항식 추출
  - Cantor-Zassenhaus (특성 2) 로 1차 인수 분해
  - 각 근의 중복도는 반복 나눗셈으로 계산
"""

import random
import sys

# ── GF(2^128) 필드 연산 ─────────────────────────────────────────────────────
# 기약다항식: x^128 + x^7 + x^2 + x + 1
IRRED = (1 << 128) | (1 << 7) | (1 << 2) | (1 << 1) | 1
MASK  = (1 << 128) - 1

def gf_add(a: int, b: int) -> int:
    return a ^ b

def gf_mul(a: int, b: int) -> int:
    result = 0
    while b:
        if b & 1:
            result ^= a
        b >>= 1
        a <<= 1
        if a >> 128:
            a ^= IRRED
    return result & MASK

def gf_pow(base: int, exp: int) -> int:
    result = 1
    base &= MASK
    while exp:
        if exp & 1:
            result = gf_mul(result, base)
        base = gf_mul(base, base)
        exp >>= 1
    return result

def gf_inv(a: int) -> int:
    if a == 0:
        raise ZeroDivisionError("0의 역원 없음")
    return gf_pow(a, (1 << 128) - 2)

# ── GF(2^128)[x] 다항식 연산 ─────────────────────────────────────────────────
# 다항식: list[int], 인덱스 0 = 최고차항
# 예) [1, 0, 3] → x^2 + 3

def poly_normalize(f: list) -> list:
    i = 0
    while i < len(f) - 1 and f[i] == 0:
        i += 1
    return list(f[i:])

def poly_degree(f: list) -> int:
    f = poly_normalize(f)
    return len(f) - 1

def poly_add(f: list, g: list) -> list:
    n = max(len(f), len(g))
    f = [0] * (n - len(f)) + list(f)
    g = [0] * (n - len(g)) + list(g)
    return poly_normalize([gf_add(a, b) for a, b in zip(f, g)])

def poly_mul(f: list, g: list) -> list:
    if not f or not g:
        return [0]
    df, dg = len(f) - 1, len(g) - 1
    result = [0] * (df + dg + 1)
    for i, a in enumerate(f):
        for j, b in enumerate(g):
            result[i + j] = gf_add(result[i + j], gf_mul(a, b))
    return poly_normalize(result)

def poly_divmod(f: list, g: list):
    """GF(2^128)[x] 나눗셈: f = q*g + r"""
    f = poly_normalize(list(f))
    g = poly_normalize(list(g))
    df = poly_degree(f)
    dg = poly_degree(g)
    if df < dg:
        return [0], f

    lc_g_inv = gf_inv(g[0])
    r = list(f)
    q = [0] * (df - dg + 1)

    for i in range(df - dg + 1):
        if r[i] == 0:
            continue
        coeff = gf_mul(r[i], lc_g_inv)
        q[i] = coeff
        for j in range(len(g)):
            r[i + j] = gf_add(r[i + j], gf_mul(coeff, g[j]))

    remainder = poly_normalize(r[df - dg + 1:]) if df - dg + 1 < len(r) else [0]
    return poly_normalize(q), poly_normalize(remainder)

def poly_mod(f: list, g: list) -> list:
    _, r = poly_divmod(f, g)
    return r

def poly_gcd(f: list, g: list) -> list:
    f, g = poly_normalize(f), poly_normalize(g)
    while g != [0]:
        f, g = g, poly_mod(f, g)
    if f and f[0] != 1:
        inv = gf_inv(f[0])
        f = [gf_mul(c, inv) for c in f]
    return poly_normalize(f)

def poly_eval(f: list, x: int) -> int:
    result = 0
    for c in f:
        result = gf_add(gf_mul(result, x), c)
    return result

def poly_powmod(base: list, exp: int, mod: list) -> list:
    """base^exp mod mod"""
    result = [1]
    base = poly_mod(base, mod)
    while exp:
        if exp & 1:
            result = poly_mod(poly_mul(result, base), mod)
        base = poly_mod(poly_mul(base, base), mod)
        exp >>= 1
    return result

# ── x^(2^128) mod f ──────────────────────────────────────────────────────────

def frobenius_mod(f: list) -> list:
    """x^(2^128) mod f — 반복 제곱으로 계산"""
    h = [1, 0]  # x
    for _ in range(128):
        h = poly_mod(poly_mul(h, h), f)
    return h

# ── Equal-Degree Factorization (Cantor-Zassenhaus, char 2) ───────────────────

def edf(f: list, d: int) -> list:
    """f (squarefree, monic)를 차수 d인 기약인수들로 분해
    특성 2: Tr(a) = a + a^2 + ... + a^(2^(128d-1)) mod f 사용"""
    n = poly_degree(f)
    if n == d:
        return [poly_normalize(f)]
    if n == 0:
        return []

    factors = [poly_normalize(f)]

    while len(factors) < n // d:
        deg_a = random.randint(1, n - 1)
        a_coeffs = [random.getrandbits(128) & MASK for _ in range(deg_a + 1)]
        a_coeffs[0] = (a_coeffs[0] | 1) & MASK
        a = poly_mod(a_coeffs, f)
        if a == [0]:
            continue

        # Tr(a) = sum_{i=0}^{128d-1} a^(2^i) mod f
        tr = list(a)
        cur = list(a)
        for _ in range(128 * d - 1):
            cur = poly_mod(poly_mul(cur, cur), f)
            tr = poly_add(tr, cur)
        tr = poly_mod(tr, f)
        if tr == [0]:
            continue

        new_factors = []
        for fac in factors:
            if poly_degree(fac) == d:
                new_factors.append(fac)
                continue
            g = poly_gcd(tr, fac)
            if g == [1] or g == poly_normalize(fac):
                new_factors.append(fac)
            else:
                q, _ = poly_divmod(fac, g)
                new_factors.append(poly_normalize(g))
                new_factors.append(poly_normalize(q))
        factors = new_factors

    return factors

# ── Distinct-Degree Factorization ─────────────────────────────────────────────

def ddf(f: list) -> list:
    """squarefree monic f 를 (같은차수_기약인수들의_곱, 차수) 쌍으로 분해"""
    factors = []
    h = [1, 0]  # x
    f_rem = poly_normalize(f)
    d = 1

    while poly_degree(f_rem) >= 2 * d:
        # h = x^(2^(128d)) mod f_rem
        for _ in range(128):
            h = poly_mod(poly_mul(h, h), f_rem)
        # gcd(h - x, f_rem) = gcd(h XOR x, f_rem) in char 2
        diff = poly_add(h, [1, 0])
        g = poly_gcd(diff, f_rem)
        if g != [1]:
            factors.append((poly_normalize(g), d))
            f_rem, _ = poly_divmod(f_rem, g)
            h = poly_mod([1, 0], f_rem)
        d += 1

    if poly_degree(f_rem) > 0:
        factors.append((poly_normalize(f_rem), poly_degree(f_rem)))

    return factors

# ── 근 추출 ──────────────────────────────────────────────────────────────────

def roots_squarefree(f: list) -> list:
    """squarefree monic f의 GF(2^128) 위 모든 근 반환"""
    if poly_degree(f) == 0:
        return []
    if poly_degree(f) == 1:
        # f = x + c → 근 = c * lc^{-1}
        r = gf_mul(f[1], gf_inv(f[0]))
        return [r]

    dd = ddf(f)
    roots = []
    for g, d in dd:
        if d == 1:
            # g는 1차 인수들의 곱 → edf
            linears = edf(g, 1)
            for lin in linears:
                r = gf_mul(lin[1], gf_inv(lin[0]))
                roots.append(r)
        # d > 1 이면 GF(2^128)에 근 없음
    return roots

def root_multiplicity(f: list, r: int) -> int:
    """f에서 근 r의 중복도"""
    xr = [1, r]
    cur = poly_normalize(f)
    m = 0
    while True:
        q, rem = poly_divmod(cur, xr)
        if rem != [0] and poly_normalize(rem) != [0]:
            break
        cur = poly_normalize(q)
        m += 1
        if poly_degree(cur) == 0:
            break
    return m

def find_roots(f: list) -> list:
    """GF(2^128)[x] 위 f의 모든 근 (중복도 포함)"""
    f = poly_normalize(f)
    if f[0] != 1:
        inv = gf_inv(f[0])
        f = [gf_mul(c, inv) for c in f]

    # 서로 다른 근들의 squarefree 다항식: gcd(f, x^(2^128) - x)
    xq = frobenius_mod(f)           # x^(2^128) mod f
    xq_minus_x = poly_add(xq, [1, 0])  # x^q - x = x^q XOR x (char 2)
    f_rad = poly_gcd(f, xq_minus_x)

    distinct_roots = roots_squarefree(f_rad)

    # 각 근의 중복도 계산
    result = []
    for r in distinct_roots:
        m = root_multiplicity(f, r)
        result.extend([r] * m)

    return result

# ── I/O ──────────────────────────────────────────────────────────────────────

def parse_hex(s: str) -> int:
    s = s.strip().lower().replace("0x", "").replace("_", "")
    if not s or s == "0":
        return 0
    val = int(s, 16)
    if val >> 128:
        raise ValueError(f"128비트 초과: {hex(val)}")
    return val

def input_coefficients() -> list:
    print("\n6차 방정식 계수 입력 (a6·x^6 + a5·x^5 + ... + a0 = 0)")
    print("hex string 7개를 공백 또는 쉼표로 구분해서 입력 (최고차항부터)")
    print("예) 0x1 0xdeadbeef 0x0 0x0 0x0 0x0 0xcafebabe\n")

    while True:
        raw = input(">> ").strip()
        if not raw:
            continue
        # 구분자: 쉼표 or 공백
        import re
        tokens = re.split(r"[,\s]+", raw)
        tokens = [t for t in tokens if t]
        if len(tokens) != 7:
            print(f"  오류: 계수 7개 필요 (입력된 토큰 수: {len(tokens)})")
            continue
        try:
            coeffs = [parse_hex(t) for t in tokens]
            return coeffs  # [a6, a5, ..., a0] 순서 (최고차항 먼저)
        except ValueError as e:
            print(f"  오류: {e}")

def poly_to_str(coeffs: list) -> str:
    coeffs = poly_normalize(coeffs)
    deg = poly_degree(coeffs)
    if deg < 0 or coeffs == [0]:
        return "0"
    terms = []
    for i, c in enumerate(coeffs):
        exp = deg - i
        if c == 0:
            continue
        c_str = hex(c)
        if exp == 0:
            terms.append(c_str)
        elif exp == 1:
            terms.append(f"{c_str}·x")
        else:
            terms.append(f"{c_str}·x^{exp}")
    return " + ".join(terms) if terms else "0"

def main():
    print("=" * 64)
    print("   GF(2^128) 위의 6차 방정식 풀이기")
    print("   기약다항식: x^128 + x^7 + x^2 + x + 1  (AES-GCM)")
    print("=" * 64)

    while True:
        coeffs = input_coefficients()
        actual = poly_normalize(coeffs)

        if actual == [0]:
            print("\n모든 계수가 0 — 방정식 정의 불가\n")
            continue

        deg = poly_degree(actual)
        print(f"\n[차수 {deg}] {poly_to_str(coeffs)} = 0")
        print("풀이 중...", end="", flush=True)

        try:
            roots = find_roots(coeffs)
        except Exception as e:
            print(f"\n오류: {e}")
            import traceback; traceback.print_exc()
            continue

        print("\r" + " " * 20 + "\r", end="")
        print("─" * 64)

        if not roots:
            print("GF(2^128) 위에 근 없음")
        else:
            from collections import Counter
            cnt = Counter(roots)
            print(f"근 {len(set(roots))}개 (중복도 포함 {len(roots)}개):\n")
            for r, m in sorted(cnt.items()):
                mult_str = f"  ← 중근 (중복도 {m})" if m > 1 else ""
                val = poly_eval(coeffs, r)
                ok = "✓" if val == 0 else f"✗  f(x)={hex(val)}"
                print(f"  x = {hex(r)}{mult_str}")
                print(f"      검증: {ok}")

        print("─" * 64)
        again = input("\n다시? [y/N]: ").strip().lower()
        if again != "y":
            break

if __name__ == "__main__":
    main()
