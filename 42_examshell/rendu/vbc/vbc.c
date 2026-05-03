#include "vbc.h" /* inclui o cabeçalho com protótipos e includes necessários */

char *s; /* ponteiro global para a string de entrada atual */

/*
 * Imprime mensagem de erro apropriada quando encontra um token inesperado
 * Se 'c' for zero, indica fim de ficheiro inesperado
 */
void unexpected(char c)
{
	if(c)
		printf("Unexpected token '%c'\n", c); /* token inválido */
	else
		printf("Unexpected end of file\n"); /* fim de input inesperado */
}

/*
 * ft_product: trata multiplicações com precedência maior
 * Lê um fator e, enquanto houver '*' segue lendo fatores e multiplicando
 */
int ft_product()
{
	int a = ft_factor(); /* lê o primeiro fator */
	int b; /* armazenará o próximo fator */
	while(*s == '*') /* enquanto o próximo caractere for '*' */
	{
		s++; /* consome o '*' */
		b = ft_factor(); /* obtém o fator à direita */
		a = a * b; /* acumula a multiplicação */
	}
	return(a); /* retorna o produto acumulado */
}

/*
 * ft_sum: trata somas com precedência menor
 * Lê um produto e, enquanto houver '+' segue lendo produtos e somando
 */
int ft_sum()
{
	int sum1 = ft_product(); /* lê o primeiro termo (produto) */
	int sum2; /* armazenará o próximo termo */
	while(*s == '+') /* enquanto o próximo caractere for '+' */
	{
		s++; /* consome o '+' */
		sum2 = ft_product(); /* lê o próximo produto */
		sum1 = sum1 + sum2 ; /* acumula a soma */
	}
	return(sum1); /* retorna a soma total */
}

/*
 * ft_factor: lê um fator que pode ser um dígito ou uma expressão entre parênteses
 * Se for dígito, converte e avança o ponteiro
 * Se encontrar '(', chama ft_sum() recursivamente para avaliar a expressão interna
 */
int ft_factor()
{
	int n = 0; /* valor do fator */
	if(isdigit(*s)) /* se o caractere atual for dígito */
		return(*s++ - '0'); /* converte char para int e avança */
	while(*s == '(') /* suporta parênteses aninhados: enquanto houver '(' */
	{
		s++; /* consome '(' */
		n = ft_sum(); /* avalia expressão dentro dos parênteses */
		s++; /* consome ')' assumido após ft_sum */
	}
	return(n); /* retorna o valor do fator (ou 0 se não houver) */
}

/*
 * check_input: valida a string de entrada antes de avaliar
 * - verifica paridade de parênteses
 * - rejeita caracteres inválidos
 * - rejeita números com mais de um dígito seguidos
 * - rejeita expressão terminando com operador
 * Retorna 1 em caso de erro (e imprime a mensagem apropriada), 0 caso OK
 */
int check_input(char *str)
{
	int par = 0; /* contador de parênteses: '(' incrementa, ')' decrementa */
	int i = 0; /* índice de iteração */
	char last = 0; /* armazena último caractere lido */
	while(str[i]) /* percorre toda a string até o caractere nulo */
	{
		if(str[i] == '(')
			par++; /* abre parêntese */
		else if(str[i] == ')')
			par--; /* fecha parêntese */
		else if (!isdigit(str[i]) && str[i] != '+' && str[i] != '*' && str[i] != '(' && str[i] != ')')
			return (unexpected(str[i]), 1); /* caractere inválido */
		if(isdigit(str[i]) && isdigit(str[i+1]))
			return(unexpected(str[i+1]), 1); /* dois dígitos consecutivos não permitidos */
		if(isdigit(str[i]) && isdigit(str[i+1]))
			return(unexpected(str[i+1]), 1); /* redundante, mantém comportamento original */
		last = str[i]; /* atualiza último caractere */
		i++;
	}
	if(par > 0)
		return(unexpected('('), 1); /* falta ')' */
	if(par < 0)
		return(unexpected(')'), 1); /* excesso de ')' */
	if(last == '+' || last == '*')
		return(unexpected(0), 1); /* expressão termina com operador */
	return(0); /* entrada válida */
}

/*
 * main: verifica argumentos, valida entrada, avalia e imprime resultado
 */
int main(int argc, char **argv)
{
	if(argc != 2) /* programa espera exatamente um argumento (a expressão) */
		return(1);
	if(check_input(argv[1])) /* valida a expressão e sai em caso de erro */
		return(1);
	s = argv[1]; /* aponta 's' para a string de entrada */
	int res = ft_sum(); /* avalia a expressão inteira (soma de produtos) */
	printf("%d\n", res); /* imprime o resultado seguido de nova linha */
}

