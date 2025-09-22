/*

Assignment name  : str_capitalizer
Expected files   : str_capitalizer.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que receba uma ou mais strings e, para cada argumento, 
coloque em maiúscula o primeiro caractere de cada palavra (se for uma letra, 
obviamente), coloque o restante em minúsculas e exiba o resultado na saída 
padrão, seguido por uma nova linha.

Uma "palavra" é definida como uma parte de uma string delimitada por 
espaços/tabulações, ou pelo início/fim da string. Se uma palavra tiver apenas 
uma letra, ela deve ser maiúscula.

Se não houver argumentos, o programa deve exibir uma nova linha.

Exemplo:

$> ./str_capitalizer | cat -e
$
$> ./str_capitalizer "a FiRSt LiTTlE TESt" | cat -e
A First Little Test$
$> ./str_capitalizer "__SecONd teST A LITtle BiT   Moar comPLEX" "   But... This iS not THAT COMPLEX" "     Okay, this is the last 1239809147801 but not    the least    t" | cat -e
__second Test A Little Bit   Moar Complex$
   But... This Is Not That Complex$
     Okay, This Is The Last 1239809147801 But Not    The Least    T$
$>
*/