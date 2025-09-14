/*
Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char    *ft_strdup(char *src);
*/
#include <stdlib.h>

unsigned int ft_strlen(char *str)
{
	unsigned int i;
	i = 0;

	while(str[i] != '\0')
	{
		i++;
	}
	return(i);
}

char    *ft_strdup(char *src)
{
	unsigned int i;
	char *dest;
	unsigned int len;
	
	len = ft_strlen(src);
	dest = (char *)malloc(len + 1);
	if(dest)
	{	i = 0;
		while(src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return(dest);
}
