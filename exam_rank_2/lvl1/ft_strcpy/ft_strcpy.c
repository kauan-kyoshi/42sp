/*
Assignment name  : ft_strcpy
Expected files   : ft_strcpy.c
Allowed functions:
--------------------------------------------------------------------------------

Reproduza o comportamento da função strcpy (consulte man strcpy).
Sua função deve ser declarada da seguinte forma: 

char *ft_strcpy(char *s1, char *s2);


*/

char *ft_strcpy(char *s1, char *s2)
{
	unsigned int i;
	i = 0;

	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return(s1);
}
