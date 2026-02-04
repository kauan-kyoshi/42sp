#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	buffer[8129];
	char	*pos_buf;
	char	*pos_match;
	ssize_t	chunk;
	size_t	target_len;
	size_t	i;
	size_t	res_len = 0;

	if (argc != 2 || !argv[1] || !argv[1][0])
		return (1);
	target_len = strlen(argv[1]);
	while ((chunk = read(0, buffer + res_len, sizeof(buffer) - res_len)) > 0)
	{
		res_len += chunk;
		pos_buf = buffer;
		while ((pos_match = memmem(pos_buf, res_len - (pos_buf - buffer), argv[1], target_len)))
		{
			write(1, pos_buf, pos_match - pos_buf);
			i = 0;
			while(i++ < target_len)
				write(1, "*", 1);
			pos_buf = pos_match + target_len;
		}
		res_len -= (pos_buf - buffer);
		memmove(buffer, pos_buf, res_len);
	}
	if (chunk < 0)
	{
		perror("Error");
		return (1);
	}
	write(1, buffer, res_len);
	return (0);
}
