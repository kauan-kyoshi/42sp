/*
Assignment name  : print_bits
Expected files   : print_bits.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva uma função que recebe um byte e o imprime em binário SEM UMA QUEBRA DE LINHA NO FINAL.

Sua função deve ser declarada da seguinte forma:

void print_bits(unsigned char octet);

Por exemplo, se você passar 2 para print_bits, ela irá imprimir "00000010".
*/
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_bits(unsigned char octet)
{
	int i = 7;

	while (i >= 0)
	{
		if ((octet >> i) & 1)
			ft_putchar('1');
		else
			ft_putchar('0');
		i--;
	}
}