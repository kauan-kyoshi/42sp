#include "libft/libft.h"
#include "ft_printf.h" 

int main(void)
{
	char caractere = 'k';
	char *string = "* Func10n4 c4r4lh0 *";
	int numero_i = -16;
	int numero_d = 999;

    ft_printf("teste do c : %c", caractere);
	write(1,"\n",1);
	ft_printf("teste do s : %s", string);
	write(1,"\n",1);
	ft_printf("teste do i : %i", numero_i);
	write(1,"\n",1);
	ft_printf("teste do d : %d", numero_d);
	write(1,"\n",1);
	ft_printf("teste do % : %%%%%");

}