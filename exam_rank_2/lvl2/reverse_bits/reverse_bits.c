/*
Assignment name  : reverse_bits
Expected files   : reverse_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Escreva uma função que recebe um byte, inverte-o, bit a bit (como no exemplo) e retorna o resultado.

Sua função deve ser declarada da seguinte forma:

unsigned char reverse_bits(unsigned char octet);

Example:

  1 byte
_____________
 0010  0110
     ||
     \/
 0110  0100

*/

unsigned char reverse_bits(unsigned char octet)
{
	int i =7;
	unsigned char res = 0;

	while (i>=0)
	{
		res = (res << 1) | (octet & 1);
		octet = octet >> 1;
		i--;
	}
	return(res);
}
