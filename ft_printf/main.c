#include <stdio.h>
#include <limits.h>
#include "ft_printf.h" // Certifique-se de que este é o nome do seu arquivo de cabeçalho

int main(void)
{
    int len_ft;
    int len_orig;
    char *str = "Olá, Mundo!";
    char *null_str = NULL;
    void *ptr = (void *)0x7ffeefbff5c8;
    void *null_ptr = NULL;

    printf("--- Iniciando Testes ---\n\n");

    // ===================================
    //      Teste para %c (Caractere)
    // ===================================
    printf("--- Teste de %%c ---\n");
    len_orig = printf("Original : O caractere é '%c'.\n", 'A');
    len_ft = ft_printf("Sua Ft   : O caractere é '%c'.\n", 'A');
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    // ===================================
    //      Teste para %s (String)
    // ===================================
    printf("--- Teste de %%s ---\n");
    len_orig = printf("Original : A string é \"%s\".\n", str);
    len_ft = ft_printf("Sua Ft   : A string é \"%s\".\n", str);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    printf("Teste com string NULA:\n");
    len_orig = printf("Original : A string nula é \"%s\".\n", null_str);
    len_ft = ft_printf("Sua Ft   : A string nula é \"%s\".\n", null_str);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);


    // ===================================
    //      Teste para %p (Ponteiro)
    // ===================================
    printf("--- Teste de %%p ---\n");
    len_orig = printf("Original : O endereço do ponteiro é %p.\n", ptr);
    len_ft = ft_printf("Sua Ft   : O endereço do ponteiro é %p.\n", ptr);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    printf("Teste com ponteiro NULO:\n");
    len_orig = printf("Original : O endereço do ponteiro nulo é %p.\n", null_ptr);
    len_ft = ft_printf("Sua Ft   : O endereço do ponteiro nulo é %p.\n", null_ptr);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    // ===================================
    //  Teste para %d e %i (Decimal e Inteiro)
    // ===================================
    printf("--- Teste de %%d e %%i ---\n");
    len_orig = printf("Original : Número decimal %d e inteiro %i.\n", 123, -456);
    len_ft = ft_printf("Sua Ft   : Número decimal %d e inteiro %i.\n", 123, -456);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    printf("Teste com INT_MAX e INT_MIN:\n");
    len_orig = printf("Original : INT_MAX=%d, INT_MIN=%i.\n", INT_MAX, INT_MIN);
    len_ft = ft_printf("Sua Ft   : INT_MAX=%d, INT_MIN=%i.\n", INT_MAX, INT_MIN);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    printf("Teste com zero:\n");
    len_orig = printf("Original : Zero como decimal: %d.\n", 0);
    len_ft = ft_printf("Sua Ft   : Zero como decimal: %d.\n", 0);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    // ===================================
    //      Teste para %u (Unsigned Decimal)
    // ===================================
    printf("--- Teste de %%u ---\n");
    len_orig = printf("Original : Número sem sinal: %u.\n", 4294967295U); // UINT_MAX
    len_ft = ft_printf("Sua Ft   : Número sem sinal: %u.\n", 4294967295U);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    printf("Teste com zero sem sinal:\n");
    len_orig = printf("Original : Zero sem sinal: %u.\n", 0);
    len_ft = ft_printf("Sua Ft   : Zero sem sinal: %u.\n", 0);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);


    // ===================================
    //  Teste para %x e %X (Hexadecimal)
    // ===================================
    printf("--- Teste de %%x e %%X ---\n");
    len_orig = printf("Original : Hex minúsculo: %x. Hex maiúsculo: %X.\n", 255, 255);
    len_ft = ft_printf("Sua Ft   : Hex minúsculo: %x. Hex maiúsculo: %X.\n", 255, 255);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);

    printf("Teste com número grande em hexadecimal:\n");
    len_orig = printf("Original : Hex grande min: %x. Hex grande mai: %X.\n", INT_MAX, INT_MAX);
    len_ft = ft_printf("Sua Ft   : Hex grande min: %x. Hex grande mai: %X.\n", INT_MAX, INT_MAX);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);


    // ===================================
    //      Teste para %% (Sinal de Porcentagem)
    // ===================================
    printf("--- Teste de %%%% ---\n");
    len_orig = printf("Original : Imprimindo um sinal de porcentagem: %%.\n");
    len_ft = ft_printf("Sua Ft   : Imprimindo um sinal de porcentagem: %%.\n");
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);


    // ===================================
    //      Teste Combinado
    // ===================================
    printf("--- Teste Combinado ---\n");
    len_orig = printf("Original : %s, char '%c', dec %d, hex %x, ptr %p, unsigned %u, %%. Fim.\n", "Teste", 'Z', -123, 456, ptr, 789);
    len_ft = ft_printf("Sua Ft   : %s, char '%c', dec %d, hex %x, ptr %p, unsigned %u, %%. Fim.\n", "Teste", 'Z', -123, 456, ptr, 789);
    printf("Retorno Original: %d | Retorno ft_printf: %d\n\n", len_orig, len_ft);


    printf("--- Fim dos Testes ---\n");
    return (0);
}