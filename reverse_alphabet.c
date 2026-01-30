#include <unistd.h>

int main (void)
{
	char c;
	int i = 0;
	while (i < 26)
	{
		if (i % 2 == 0)
		{
			c = 'a' + i;
		}
		else
		{
			c = 'A' + i;
		}
		write(1, &c, 1);
		
		i++;
	}
	write(1, "\n", 1);
	return 0;

}