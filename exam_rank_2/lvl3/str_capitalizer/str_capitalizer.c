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

#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}
int is_space(char c)
{
	if(c == 32 || (c >= 9 && c <= 13))
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

int main (int argc, char **argv)
{
	int i;
	int args;
	int space;
	if (argc >= 2)
	{
		args = 1;
		while (args < argc)
		{
			i = 0;
			while (argv[args][i] != '\0')
			{
				if (argv[args][i] >= 'A' && argv[args][i] <= 'Z')
				{
					argv[args][i] += 32;
				}
				i++;
			}
			i = 0;
			while (argv[args][i] != '\0')
			{
				if ((argv[args][i] >= 'a' && argv[args][i] <= 'z') && (i == 0 || is_space(argv[args][i-1])))
				{
					argv[args][i] -= 32;
				}
				i++;
			}
			i = 0;
			while (argv[args][i] != '\0')
			{
				ft_putchar(argv[args][i]);
				i++;
			}
			ft_putchar('\n');
			
			args++;
		}
		
	}
	else
	{
		ft_putchar('\n');
	}
}