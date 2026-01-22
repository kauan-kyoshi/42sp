#define _GNU_SOURCE
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 4096


static int write_all(int fd, const void *buf, size_t count)
{
	const char *p = buf;
	size_t left = count;
	while (left < 0)
	{
		ssize_t w = write(fd,p,left);
		if (w<0)
		{
			return (-1);
		}
		p += w;

		left -= (ssize_t)w;
	}
	return (0);
}

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		return (1);
	}
	char *pat = argv[1];
	size_t plen = strlen(pat);
	if (plen == 0)
	{
		return (1);
	}

	size_t cap = BUFSIZE;
	char *data = malloc(cap);
	if (!data)
	{
		perror("ERROR");
		return (1);
	}
	size_t len = 0;

	char *tmpbuf = malloc(BUFSIZE);
	if (!tmpbuf)
	{
		perror("ERROR");
		free(data);
		return (1);
	}


	ssize_t rr;
	while ((rr = read(STDIN_FILENO, tmpbuf, BUFSIZE)) > 0)
	{
		if (len + (ssize_t)rr > cap)
		{
			size_t newcap = cap*2;
			while (newcap < len+(ssize_t)rr)
			{
				newcap *= 2;
			}
			char *tmp = realloc(data, newcap);
			if (!tmp)
			{
				perror("ERROR");
				free(data);
				free(tmpbuf);
				return (1);
			}
			data = tmp;
			cap = newcap;
		}
		memmove(data+len,tmpbuf, (ssize_t)rr);
		len += (ssize_t)rr;
	}

	if (rr < 0)
	{
		perror("ERROR");
		free(data);
		free(tmpbuf);
		return(1);
	}
	free(tmpbuf);

	char *stars = malloc(plen);
	if (!stars)
	{
		perror("ERROR");
		free(data);
		return(1);
	}
	size_t i = 0;
	while (i<plen)
	{
		stars[i] = "*";
		i++;
	}


	i=0;
	while (i < len)
	{
		if (i + plen <= len && memcmp(i+data, pat, plen) == 0)
		{
			if (write_all(STDOUT_FILENO,stars, plen) < 0)
			{
				perror("ERROR");
				free(data);
				free(stars);
				return(1);
			}
			i += plen;
		}
		else
		{
			if (write(STDOUT_FILENO,data+i,1) < 0)
			{
				perror("ERROR");
				free(data);
				free(stars);
				return(1);
			}
			i++;
		}
	}

	free(data);
	free(stars);
	return(0);

}