/*
Assignment name  : ulstr
Expected files   : ulstr.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que receba uma string e inverta o caso de todas as suas letras.
Outros caracteres permanecem inalterados.

Você deve exibir o resultado seguido de um '\n'.

Se o número de argumentos não for 1, o programa exibe '\n'.

Examples :

$>./ulstr "L'eSPrit nE peUt plUs pRogResSer s'Il staGne et sI peRsIsTent VAnIte et auto-justification." | cat -e
l'EspRIT Ne PEuT PLuS PrOGrESsER S'iL STAgNE ET Si PErSiStENT vaNiTE ET AUTO-JUSTIFICATION.$
$>./ulstr "S'enTOuRer dE sECreT eSt uN sIGnE De mAnQuE De coNNaiSSanCe.  " | cat -e
s'ENtoUrER De SecREt EsT Un SigNe dE MaNqUe dE COnnAIssANcE.  $
$>./ulstr "3:21 Ba  tOut  moUn ki Ka di KE m'en Ka fe fot" | cat -e
3:21 bA  ToUT  MOuN KI kA DI ke M'EN kA FE FOT$
$>./ulstr | cat -e
$
*/

#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}

int main (int argc, char **argv)
{

	int i; 
	i = 0;

	if(argc == 2)
	{
		while(argv[1][i] != '\0')
		{
			if (argv[1][i]>= 'a' && argv[1][i] <= 'z')
			{
				argv[1][i] = argv[1][i] - 32;
			}
			else if(argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			{
				argv[1][i] = argv[1][i] + 32;
			}
			ft_putchar(argv[1][i]);
			i++;
		}
	}
	ft_putchar('\n');
}