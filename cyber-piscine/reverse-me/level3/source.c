#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char in[24] = {0};
    char out[16];

    printf("Please enter key: ");
    if (scanf("%23s", in) != 1) {
        puts("Nope.");
        return 1;
    }

    /* quick prefix checks observed in the binary */
    if (in[0] != '4' || in[1] != '2') {
        puts("Nope.");
        return 1;
    }

    out[0] = '*';
    int i = 2; /* parsing starts at index 2 */
    int j = 1; /* out index (out[0] already set) */
    size_t len = strlen(in);

    while (i + 2 < (int)len && j < 8) {
        char tmp[4];
        tmp[0] = in[i];
        tmp[1] = in[i + 1];
        tmp[2] = in[i + 2];
        tmp[3] = '\0';
        out[j++] = (char)atoi(tmp);
        i += 3;
    }
    out[j] = '\0';

    if (strcmp(out, "********") == 0) {
        puts("Good job.");
    } else {
        puts("Nope.");
    }

    return 0;
}
