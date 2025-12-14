# ft_otp

Simple TOTP/HOTP helper written in Go for the 42 project exercises.

- `main.go` — source code (generate encrypted key with `-g`, print OTP with `-k`).
- `Makefile` — `make build` builds the binary, `make test` runs the oathtool comparison test.
- `test/` — contains a test script that compares output with `oathtool`.

Before pushing to GitHub, ensure you do NOT commit the generated `ft_otp` binary
or any key files. Those are already ignored by `.gitignore`.

Run the included cleanup script to remove generated artifacts before committing:

```sh
./cleanup.sh
```

