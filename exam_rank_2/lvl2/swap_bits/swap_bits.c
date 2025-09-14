/*
Assignment name  : swap_bits
Expected files   : swap_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Escreva uma função que recebe um byte, troca suas metades (como no exemplo) e retorna o resultado.

Sua função deve ser declarada da seguinte forma:

unsigned char swap_bits(unsigned char octet);

Example:

  1 byte
_____________
 0100 | 0001
     \ /
     / \
 0001 | 0100
*/

unsigned char swap_bits(unsigned char octet)
{
	return ( (octet >> 4) | (octet << 4) );
}