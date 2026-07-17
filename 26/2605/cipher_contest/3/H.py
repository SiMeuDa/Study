import galois
import time
import traceback

LOG_FILE = "progress.log"
ROOT_FILE = "roots.txt"

def log(msg):
    t = time.strftime("%Y-%m-%d %H:%M:%S")
    line = f"[{t}] {msg}"
    print(line)
    with open(LOG_FILE, "a") as f:
        f.write(line + "\n")
        f.flush()


# -----------------------------
# Start
# -----------------------------
open(LOG_FILE, "w").close()

log("Program started.")

try:
    # AES-GCM irreducible polynomial
    poly = galois.Poly.Int(
        (1 << 128)
        | (1 << 7)
        | (1 << 2)
        | (1 << 1)
        | 1
    )

    log("Irreducible polynomial created.")

    GF = galois.GF(2**128, irreducible_poly=poly)

    log("GF(2^128) constructed.")

    coeffs = input(
        "Input coefficients (A13 C11 C12 C13 L13 T13):\n"
    ).split()

    if len(coeffs) != 6:
        raise ValueError("Exactly 6 hexadecimal values are required.")

    log("Input received.")

    a5, a4, a3, a2, a1, a0 = [
        GF(int(x, 16)) for x in coeffs
    ]

    log("Coefficients converted.")

    x = galois.Poly.Identity(GF)

    P = (
          a5*x**5
        + a4*x**4
        + a3*x**3
        + a2*x**2
        + a1*x
        + a0
    )

    log("Polynomial generated.")
    log(f"P = {P}")

    # -----------------------------
    # Root Finding
    # -----------------------------
    log("Starting P.roots().")

    start = time.time()

    roots = P.roots()

    elapsed = time.time() - start

    log(f"P.roots() finished.")
    log(f"Elapsed time: {elapsed:.3f} sec")
    log(f"Number of roots: {len(roots)}")

    # -----------------------------
    # Save roots
    # -----------------------------
    with open(ROOT_FILE, "w") as f:

        f.write("Polynomial\n")
        f.write(str(P))
        f.write("\n\n")

        f.write(f"Elapsed: {elapsed:.3f} sec\n")
        f.write(f"Number of roots: {len(roots)}\n\n")

        if len(roots) == 0:
            f.write("No root found.\n")

        else:
            for i, r in enumerate(roots):

                f.write(f"Root {i}\n")
                f.write(f"Decimal : {int(r)}\n")
                f.write(f"Hex     : {int(r):032x}\n\n")

    log(f"Roots saved to {ROOT_FILE}")

except Exception as e:

    log("Exception occurred!")
    log(str(e))

    with open(LOG_FILE, "a") as f:
        f.write("\n========== Traceback ==========\n")
        traceback.print_exc(file=f)

    raise
