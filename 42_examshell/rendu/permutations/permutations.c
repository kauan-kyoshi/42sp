/* permutations: imprime todas permutações em ordem alfabética */
#include <unistd.h>
#include <stdlib.h>

static size_t ft_strlen(char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return i;
}

static void ft_swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

/* simple ascending sort (selection) */
static void sort_str(char *s)
{
    size_t i = 0;
    size_t n = ft_strlen(s);
    while (i < n)
    {
        size_t min = i;
        size_t j = i + 1;
        while (j < n)
        {
            if (s[j] < s[min])
                min = j;
            j++;
        }
        if (min != i)
            ft_swap(&s[i], &s[min]);
        i++;
    }
}

/* reverse s[l..r] inclusive */
static void reverse_range(char *s, size_t l, size_t r)
{
    while (l < r)
    {
        ft_swap(&s[l], &s[r]);
        l++;
        r--;
    }
}

/* next_permutation: returns 1 if next exists, 0 if was last */
static int next_permutation(char *s)
{
    size_t n = ft_strlen(s);
    if (n < 2) return 0;
    ssize_t i = (ssize_t)n - 2;
    while (i >= 0 && s[i] >= s[i+1])
        i--;
    if (i < 0)
        return 0; /* no next */
    ssize_t j = (ssize_t)n - 1;
    while (j > i && s[j] <= s[i])
        j--;
    ft_swap(&s[i], &s[j]);
    reverse_range(s, (size_t)i + 1, n - 1);
    return 1;
}

static void print_line(char *s)
{
    size_t n = ft_strlen(s);
    if (n > 0)
        write(1, s, n);
    write(1, "\n", 1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    size_t n = ft_strlen(argv[1]);
    char *s = malloc(n + 1);
    //if (!s) return 0;
    size_t k = 0;
    while (k < n)
    {
        s[k] = argv[1][k];
        k++;
    }
    s[n] = '\0';
    if (n == 0)
    {
        write(1, "\n", 1);
        //free(s);
        return 0;
    }
    sort_str(s);
    print_line(s);
    while (next_permutation(s))
        print_line(s);
    //free(s);
    return 0;
}
