#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	char	buffer[8192];
	char	*pos_match;
	char	*pos_buffer;
	ssize_t	chunk;
	size_t	target_len;
	size_t	i;
	size_t	res_len=0;

	if ((argc != 2 )|| (!argv[1]) || (!argv[1][0]) )
	{
		return 1;
	}

	target_len = strlen(argv[1]);

	while((chunk = read(0, buffer+res_len,sizeof(buffer)-res_len))>0)
	{
		res_len += chunk;
		pos_buffer = buffer;

		while ((pos_match = memmem(pos_buffer, res_len-(pos_buffer - buffer), argv[1], target_len)))
		{
			write(1, pos_buffer, pos_match-pos_buffer);

			i=0;
			while(i<target_len)
			{
				write(1, "*", 1);
				i++;
			}

			pos_buffer = pos_match+target_len;
		}
		res_len -= (pos_buffer-buffer);
		memmove(buffer, pos_buffer,res_len);
	}

	write(1,buffer,res_len);
	return 0;
}