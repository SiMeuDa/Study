###############################################################
# GHASH Polynomial Solver (SageMath 10.7)
#
# Solve:
#
# A5*H^5 + A4*H^4 + A3*H^3 + A2*H^2 + A1*H + A0 = 0
#
###############################################################

# -------------------------------------------------------------
# GF(2^128)
# -------------------------------------------------------------

F2 = GF(2)
R.<x> = PolynomialRing(F2)

MOD = x^128 + x^7 + x^2 + x + 1

K.<a> = GF(2^128, modulus=MOD)

PR.<H> = PolynomialRing(K)


# -------------------------------------------------------------
# Convert 128-bit block -> GF(2^128)
#
# GHASH bit order
#
# bit127 -> x^127
# ...
# bit1   -> x^1
# bit0   -> x^0
#
# -------------------------------------------------------------

def block(v):

    if isinstance(v, str):

        v = v.strip()

        if v.startswith("0x") or v.startswith("0X"):
            v = v[2:]

        v = int(v,16)

    else:
        v = int(v)

    poly = R.zero()

    for i in range(128):

        if (v >> (127-i)) & 1:

            poly += x^(127-i)

    return K(poly)


# -------------------------------------------------------------
# INPUT
# -------------------------------------------------------------

A5 = block("0x72000000")
A4 = block("0x30c1a38551405054f")
A3 = block("0x4916455e4249430d010012505b4c0d00")
A2 = block("0x501e520e7341daee867a49665542cd9")
A1 = block("0x90")
A0 = block("0xb38b345b0bc982a474048b8476a74aaa")


# -------------------------------------------------------------
# Polynomial
# -------------------------------------------------------------

poly = (
      A5*H^5
    + A4*H^4
    + A3*H^3
    + A2*H^2
    + A1*H
    + A0
)

print("="*60)
print("Polynomial")
print(poly)
print("="*60)


# -------------------------------------------------------------
# Solve
# -------------------------------------------------------------

roots = poly.roots()

print()
print("Number of roots :",len(roots))
print()

for idx,(root,mult) in enumerate(roots):

    value = 0

    for i in range(128):

        if root.polynomial()[i] == 1:
            value |= (1<<i)

    print("------------------------------------------")
    print("Candidate :",idx+1)
    print("Multiplicity :",mult)
    print("Hex : {:032x}".format(value))
    print()


if len(roots)==0:
    print("No solution")
