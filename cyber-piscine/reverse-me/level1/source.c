/*
 * Example `source.c` template for level1.
 * Replace the contents with your C representation of the crackme algorithm.
 */

#include <stdio.h>
#include <string.h>

int verify(const char *pw) {
    /* Reconstructed logic: the crackme compares input with the literal
     * string "__stack_check" and returns success when equal.
     */
    if (strcmp(pw, "__stack_check") == 0) return 1;
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    if (verify(argv[1])) {
        puts("OK");
        return 0;
    }
    puts("KO");
    return 1;
}
