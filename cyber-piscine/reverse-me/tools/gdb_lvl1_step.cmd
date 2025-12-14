set pagination off
set disable-randomization on
set arch i386
file binary/level1
break main
commands 1
  set $bpaddr = $pc + 0x7c
  printf "computed bpaddr=0x%x\n", $bpaddr
  break *$bpaddr
  continue
end
commands 2
  echo "---hit strcmp call---\n"
  info registers
  x/32wx $esp
  x/s ((char**) $esp)[0]
  x/s ((char**) ($esp+4))
  quit
end
run < tools/inp_lvl1.txt
