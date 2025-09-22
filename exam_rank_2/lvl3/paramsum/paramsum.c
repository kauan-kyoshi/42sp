/*
Assignment name  : paramsum
Expected files   : paramsum.c
Allowed functions: write
--------------------------------------------------------------------------------

"Escreva um programa que exibe o número de argumentos passados a ele, seguido 
por uma nova linha.

Se não houver argumentos, exiba apenas um 0, seguido por uma nova linha.

Exemplo:"

$>./paramsum 1 2 3 5 7 24
6
$>./paramsum 6 12 24 | cat -e
3$
$>./paramsum | cat -e
0$
$>
*/

#include <unistd.h>

void ft_putnbr(int nbr)
{
    if (nbr >= 10)
        ft_putnbr(nbr / 10);
    char c = nbr % 10 + '0';
    write(1, &c, 1);
}

int main(int ac, char **av)
{

    (void) av;

    ft_putnbr(ac - 1);
    write(1, "\n", 1);
    return (0);
}