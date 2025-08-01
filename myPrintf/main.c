#include "libft/libft.h"
#include "ft_printf.h" 

int main(void)
{
	char caractere = 'k';
	char *string = "* Func10n4 c4r4lh0 *";
	int numero_i = -16;
	int numero_d = 999;
	unsigned int sem_sinal = 4294967295;
	unsigned int sem_sinal0 = 0;
	unsigned int xis = 255;


    ft_printf("teste do c : %c", caractere);
	write(1,"\n",1);
	ft_printf("teste do s : %s", string);
	write(1,"\n",1);
	ft_printf("teste do i : %i", numero_i);
	write(1,"\n",1);
	ft_printf("teste do i com conta : %i", 5+2);

	write(1,"\n",1);
	ft_printf("teste do d : %d", numero_d);
	write(1,"\n",1);
	ft_printf("teste do % : %%%%%");
	write(1,"\n",1);
	ft_printf("teste do u : %u", sem_sinal);
	write(1,"\n",1);
	ft_printf("teste do u = 0 : %u", sem_sinal0);
	write(1,"\n",1);
	ft_printf("teste do x  : %X", xis);

}