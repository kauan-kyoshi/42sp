# Reverse-me project scaffold

This folder contains the cracked binaries archive and a scaffold to prepare your
submission for the Reverse-me project.

Contents:
- `binary.tgz` — archive provided by the course containing the three crackme
  binaries inside `binary/level1`, `binary/level2`, and `binary/level3`.
- `level1/`, `level2/` — folders for your mandatory submissions (we create them
  here as placeholders). Each folder should contain at least:
  - `password` — a file containing a password that solves the crackme
  - `source.c` — a C source file reproducing the algorithmic logic of the
    crackme (not necessarily the original source, but a clear representation)

How to use:
1. Inspect the provided archive:

```sh
cd reverse-me
tar -tzf binary.tgz
```

2. Extract binaries to a safe working folder for analysis (we ignore this
   folder in `.gitignore`):

```sh
mkdir -p binary && tar -xzf binary.tgz -C binary
ls -la binary
```

3. Reverse the first two programs (level1, level2). For each level create the
   folder named `levelX/` (already present) containing:

- `password` — the string that makes the binary validate
- `source.c` — a C file implementing the algorithm used by the binary

4. (Bonus) If you implement patches that accept any password, include the
   patched binary and a `patch_description.txt` that explains what you changed
   and why.

Notes:
- Do NOT commit extracted binaries or patched binaries into the repository
  unless explicitly asked; the provided `.gitignore` excludes `binary/`.
- The scaffold here is a starting point — replace the placeholder `password`
  and `source.c` files with your real reversed outputs.
