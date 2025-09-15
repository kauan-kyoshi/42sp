/*
Assignment name  : epur_str
Expected files   : epur_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que receba uma string e exiba essa string com exatamente 
um espaço entre as palavras, sem espaços ou tabulações no início ou no fim,
seguido por um \n.

Uma "palavra" é definida como uma parte de uma string delimitada por 
espaços/tabulações ou pelo início/fim da string.

Se o número de argumentos não for 1, ou se não houver palavras para exibir,
o programa exibe \n.

Example:

$> ./epur_str "vous voyez c'est facile d'afficher la meme chose" | cat -e
vous voyez c'est facile d'afficher la meme chose$
$> ./epur_str " seulement          la c'est      plus dur " | cat -e
seulement la c'est plus dur$
$> ./epur_str "comme c'est cocasse" "vous avez entendu, Mathilde ?" | cat -e
$
$> ./epur_str "" | cat -e
$
$>	
*/
#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int flag_word; // Uma "flag" para saber se já imprimimos a primeira palavra.

    if (argc == 2)
    {
        i = 0;
        flag_word = 0; // Inicialmente, nenhuma palavra foi impressa.

        // 1. Pula todos os espaços/tabs no início da string.
        while (argv[1][i] == ' ' || argv[1][i] == '\t')
        {
            i++;
        }

        // 2. Percorre a string.
        while (argv[1][i] != '\0')
        {
            // Se encontrarmos um caractere que NÃO é um separador...
            if (argv[1][i] != ' ' && argv[1][i] != '\t')
            {
                // Se uma palavra já foi impressa antes (flag_word == 1),
                // significa que precisamos imprimir um espaço antes desta nova palavra.
                if (flag_word == 1)
                {
                    write(1, " ", 1);
                }
                // Imprime o caractere da palavra.
                write(1, &argv[1][i], 1);
                // Marca que acabamos de processar um caractere de palavra.
                // Isso desativa a impressão de espaços múltiplos.
                flag_word = 0; 
            }
            // Se encontrarmos um separador E o caractere anterior era de uma palavra...
            else if (flag_word == 0)
            {
                // Ativa a flag. Isso "prepara" o programa para imprimir um espaço
                // se e somente se a próxima coisa que encontrarmos for outra palavra.
                flag_word = 1;
            }
            i++;
        }
    }

    // 3. Imprime a nova linha no final.
    // Esta linha é executada em todos os casos, conforme solicitado.
    write(1, "\n", 1);
    return (0);
}