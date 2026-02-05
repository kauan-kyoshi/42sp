#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("test_input.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    char *line;
    int i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        printf("[%02d] %s", i++, line);
        free(line);
        if (i > 1000) { printf("Too many lines, aborting\n"); break; }
    }
    close(fd);
    return 0;
}
