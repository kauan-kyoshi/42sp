/*
 * Reconstructed logic for level2 crackme.
 * The original binary expects an input where the meaningful data
 * starts at index 2: groups of 3 ASCII digits representing character
 * codes (e.g. "101" -> 'e'). The program builds a string from
 * these codes (starting with a pre-initialized 'd') and compares it
 * against the expected value.
 *
 * This simplified C program reproduces that behavior: it reads a
 * single token, validates minimal length and parses 3-digit groups
 * starting at offset 2 to produce the candidate string for comparison.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[512];
    if (scanf("%511s", buf) != 1) return 1;

    size_t len = strlen(buf);
    if (len < 8) {
        puts("Nope.");
        return 1;
    }

    /* Expected value discovered from the binary */
    const char *expected = "delabere";

    /* Construct candidate: first char fixed to 'd' (as in the binary)
     * then parse 3-digit groups starting at index 2. */
    char out[128];
    size_t out_i = 0;
    out[out_i++] = 'd';

    for (size_t i = 2; i + 2 < len; i += 3) {
        char tmp[4];
        tmp[0] = buf[i];
        tmp[1] = buf[i+1];
        tmp[2] = buf[i+2];
        tmp[3] = '\0';
        int v = atoi(tmp);
        out[out_i++] = (char)v;
        if (out_i >= sizeof(out)-1) break;
    }
    out[out_i] = '\0';

    if (strcmp(out, expected) == 0) {
        puts("Good job.");
        return 0;
    }
    puts("Nope.");
    return 1;
}
/*
 * Example `source.c` template for level2.
 * Replace the contents with your C representation of the crackme algorithm.
 */

#include <stdio.h>
#include <string.h>

int verify(const char *pw) {
    /* TODO: implement algorithmic logic that matches the crackme */
    if (strcmp(pw, "REPLACE_WITH_LEVEL2_PASSWORD") == 0) return 1;
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
