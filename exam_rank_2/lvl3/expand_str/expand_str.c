/*
Assignment name  : expand_str
Expected files   : expand_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que receba uma string e a exiba com exatamente três espaços 
entre cada palavra, sem espaços ou tabulações no início ou no fim, seguido por 
uma nova linha.

Uma palavra é uma seção da string delimitada por espaços/tabulações, ou pelo 
início/fim da string.

Se o número de parâmetros não for 1, ou se não houver palavras, simplesmente exiba
uma nova linha.

Exemplos:

$> ./expand_str "vous   voyez   c'est   facile   d'afficher   la   meme   chose" | cat -e
vous   voyez   c'est   facile   d'afficher   la   meme   chose$
$> ./expand_str " seulement          la c'est      plus dur " | cat -e
seulement   la   c'est   plus   dur$
$> ./expand_str "comme c'est cocasse" "vous avez entendu, Mathilde ?" | cat -e
$
$> ./expand_str "" | cat -e
$
$>

*/
#include <unistd.h>

void ft_putchar(char c)
{
    // Função auxiliar para imprimir um caractere.
    write(1, &c, 1);
}

int ft_is_space(char c)
{
    // Verifica se o caractere é um espaço ou tabulação.
    return (c == ' ' || (c >= 9 && c <= 13));
}

int main(int argc, char **argv)
{
    // Apenas um argumento é permitido e não pode ser uma string vazia.
    if (argc == 2 && argv[1][0] != '\0')
    {
        int i = 0;
        int first_word = 1;

        // Pula os espaços em branco no início da string.
        while (ft_is_space(argv[1][i]))
        {
            i++;
        }
        
        // Loop principal para processar as palavras.
        while (argv[1][i] != '\0')
        {
            // Se não for a primeira palavra, imprime três espaços.
            if (!first_word)
            {
                ft_putchar(' ');
                ft_putchar(' ');
                ft_putchar(' ');
            }
            
            // Imprime a palavra atual.
            while (argv[1][i] != '\0' && !ft_is_space(argv[1][i]))
            {
                ft_putchar(argv[1][i]);
                i++;
            }
            first_word = 0;

            // Pula os espaços entre as palavras.
            while (ft_is_space(argv[1][i]))
            {
                i++;
            }
        }
    }
    
    // Imprime uma nova linha no final.
    ft_putchar('\n');
    return 0;
}