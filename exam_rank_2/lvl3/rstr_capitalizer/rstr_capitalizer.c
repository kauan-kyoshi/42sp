/*
Assignment name  : rstr_capitalizer
Expected files   : rstr_capitalizer.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que receba uma ou mais strings e, para cada argumento, 
coloque a última letra de cada palavra em maiúscula e o restante em minúsculas,
em seguida exiba o resultado seguido de uma nova linha.

Uma palavra é uma seção de string delimitada por espaços/tabulações ou pelo 
início/fim da string. Se uma palavra tiver uma única letra, ela deve ser 
maiúscula.

Uma letra é um caractere no conjunto [a-zA-Z].

Se não houver parâmetros, exiba uma nova linha.

Exemplos:

$> ./rstr_capitalizer | cat -e
$
$> ./rstr_capitalizer "a FiRSt LiTTlE TESt" | cat -e
A firsT littlE tesT$
$> ./rstr_capitalizer "SecONd teST A LITtle BiT   Moar comPLEX" "   But... This iS not THAT COMPLEX" "     Okay, this is the last 1239809147801 but not    the least    t" | cat -e
seconD tesT A littlE biT   moaR compleX$
   but... thiS iS noT thaT compleX$
     okay, thiS iS thE lasT 1239809147801 buT noT    thE leasT    T$
$>
*/