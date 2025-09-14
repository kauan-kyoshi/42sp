/*
Assignment name	: ft_strspn
Expected files	: ft_strspn.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the strspn function 
(man strspn).

The function should be prototyped as follows:

size_t	ft_strspn(const char *s, const char *accept);
*/
#include <stdio.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t i;
	size_t j;
	int flag;

	i = 0;

	while (s[i]!= '\0')
	{
		j = 0;
		flag = 0;
		while(accept[j] != '\0')
		{
			if(accept[j] == s[i])
			{
				flag = 1;
			}
			j++;
		}
		if (flag == 0)
		{
			return(i);
		}
		
		i++;
	}
	return(i);
	
}
