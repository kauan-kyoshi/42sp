
#define _GNU_SOURCE
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 4096

static int write_all(int fd, const void *buf, size_t n)
{
	const char *p = buf;
	while (n > 0)
	{
		ssize_t w = write(fd, p, n);
		//if (w <= 0) return -1;
		p += w;
		n -= (size_t)w;
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) return 1;
	char *pat = argv[1];
	size_t plen = strlen(pat);
	//if (plen == 0) return 1;

	/* buffer único: BUFSIZE + plen para garantir espaço para sobreposição */
	//size_t bufcap = BUFSIZE + plen;
	char *buf = malloc(BUFSIZE);
	//if (!buf) { perror("Error"); return 1; } /* alterado: mensagem em português/format */

	char *stars = malloc(plen);
	//if (!stars) { perror("Error"); free(buf); return 1; }
	for (size_t k = 0; k < plen; k++) stars[k] = '*';

	size_t carry = 0; /* bytes trazidos do último bloco para checar ocorrências atravessando o buffer */
	ssize_t r;
	while ((r = read(STDIN_FILENO, buf + carry, BUFSIZE)) > 0)
	{
		size_t total = carry + (size_t)r;
		char *scan = buf;

		/* processa ocorrências dentro do buffer atual */
		char *end = buf + total; /* ponteiro para o fim válido */
		while ((size_t)(end - scan) >= plen)
		{
			size_t rem = (size_t)(end - scan);
			char *found = memmem(scan, rem, pat, plen); /* alterado: calcula corretamente bytes restantes */
			if (!found) break;
			if (found > scan)
				if (write_all(STDOUT_FILENO, scan, (size_t)(found - scan)) < 0) { perror("Error"); /*free(buf); free(stars); */return 1; }
			if (write_all(STDOUT_FILENO, stars, plen) < 0) { perror("Error"); /*free(buf); free(stars); return 1;*/ }
			scan = found + plen;
		}

		/* decide quantos bytes manter no final (plen-1) para combinar com próxima leitura */
		size_t keep = plen > 1 ? plen - 1 : 0;
		size_t rem_after = (size_t)(end - scan); /* bytes restantes após último processamento */
		if (rem_after > keep)
		{
			size_t towrite = rem_after - keep;
			if (towrite > 0)
				if (write_all(STDOUT_FILENO, scan, towrite) < 0) { perror("Error"); /*free(buf); free(stars); */return 1; }
			/* move os 'keep' bytes finais para o início do buffer */
			memmove(buf, end - keep, keep); /* alterado: move os últimos 'keep' bytes */
			carry = keep;
		}
		else
		{
			/* não há nada a escrever agora; guarda tudo para próxima iteração */
			memmove(buf, scan, rem_after);
			carry = rem_after;
		}
	}

	if (r < 0) { perror("Error"); /*free(buf); free(stars);*/ return 1; }

	/* escreve o que restou no buffer */
	if (carry > 0)
		if (write_all(STDOUT_FILENO, buf, carry) < 0) { perror("Error"); /*free(buf); free(stars); */return 1; }

	//free(buf);
	//free(stars);
	return 0;
}
