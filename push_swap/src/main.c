#include <unistd.h>

// A função main é o ponto de entrada do seu programa.
int main(int argc, char **argv)
{
    // Silencia o aviso 'unused parameter' do compilador
    (void)argv;
    
    // Apenas para provar que a compilação funciona:
    // Imprime um caractere na saída padrão.
    if (argc > 1)
        write(1, "Compilado com sucesso!\n", 23);
    else
        write(1, "Uso: ./push_swap <argumentos>\n", 30);
    
    return (0);
}