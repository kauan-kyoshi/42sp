/*
Assignment name	: ft_strpbrk
Expected files	: ft_strpbrk.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the function strpbrk
(man strpbrk).

The function should be prototyped as follows:

char	*ft_strpbrk(const char *s1, const char *s2);
*/

char	*ft_strpbrk(const char *s1, const char *s2)
{
	unsigned int i;
	unsigned int j;
	
	
	i = 0;
	while(s1[i] != '\0')
	{
		j = 0;
		while(s2[j] != '\0')
		{
			if(s1[i] == s2[j])
			{
				return(&s1[i]);
			}
			j++;
		}
		
		i++;

	}
	return(void *)0;
}
