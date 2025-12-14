set pagination off
set disable-randomization on
file binary/level1
break *0x0000123c
run < tools/inp_lvl1.txt
echo ---- registers ----\n
info registers
echo ---- stack words ----\n
x/8wx $esp
echo ---- arg0 (as string) ----\n
x/s *((char**) $esp)
echo ---- arg1 (as string) ----\n
x/s *((char**) ($esp+4))
quit
