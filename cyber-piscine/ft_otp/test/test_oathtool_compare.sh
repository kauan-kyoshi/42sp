#!/usr/bin/env bash
set -euo pipefail

# Test script: generate a random key.hex (64 hex chars), store it via ./ft_otp -g,
# then compare the OTP produced by ./ft_otp -k with oathtool's output.

HERE=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
cd "$ROOT"

if ! command -v ./ft_otp >/dev/null 2>&1; then
  echo "Error: ./ft_otp not found. Build it first: go build -o ft_otp" >&2
  exit 2
fi

if ! command -v oathtool >/dev/null 2>&1; then
  echo "Warning: oathtool not found in PATH. Install oathtool to run a full comparison." >&2
  echo "You can still run ./ft_otp -k ft_otp.key to see produced OTP." >&2
  exit 3
fi

KEYFILE=key.hex
ENCRYPTED=ft_otp.key

echo "Generating random 32 bytes -> $KEYFILE (64 hex chars)"
head -c 32 /dev/urandom | xxd -p -c 64 > "$KEYFILE"
wc -c < "$KEYFILE" | xargs echo "key length:" || true

echo "Storing key encrypted with ./ft_otp -g $KEYFILE"
./ft_otp -g "$KEYFILE"

echo "Generating OTP with ./ft_otp -k $ENCRYPTED"
OTP_LOCAL=$(./ft_otp -k "$ENCRYPTED")
echo "Local OTP: $OTP_LOCAL"

echo "Generating OTP with oathtool (using $(cat $KEYFILE) as seed)"
# Note: some oathtool versions expect base32; adjust invocation if needed.
# Try oathtool with --hex; if unsupported, convert hex -> base32 and try with --base32
if oathtool --help 2>&1 | grep -qi -- '--hex'; then
  OTP_OATHTOOL=$(oathtool --totp --hex $(cat "$KEYFILE"))
else
  echo "oathtool does not support --hex; converting key to base32 and trying --base32"
  # convert hex to base32 using python
  BASE32=$(python3 - <<'PY'
import sys,base64
hexs = open('key.hex').read().strip()
raw = bytes.fromhex(hexs)
print(base64.b32encode(raw).decode())
PY
)
  # try with --base32 flag first, fallback to no flag
  if oathtool --help 2>&1 | grep -qi -- '--base32'; then
    OTP_OATHTOOL=$(oathtool --totp --base32 "$BASE32")
  else
    OTP_OATHTOOL=$(oathtool --totp "$BASE32")
  fi
  echo "oathtool OTP: $OTP_OATHTOOL"
fi

if [ "$OTP_LOCAL" = "$OTP_OATHTOOL" ]; then
  echo "OK: OTPs match"
  exit 0
else
  echo "FAIL: OTPs differ"
  echo "Local: $OTP_LOCAL"
  echo "Oath:  $OTP_OATHTOOL"
  exit 1
fi
