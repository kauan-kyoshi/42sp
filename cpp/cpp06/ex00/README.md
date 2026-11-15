# CPP06 — ex00: ScalarConverter

## 1. O que é o exercício

O exercício implementa `ScalarConverter`, uma classe sem estado e não instanciável. Seu único método público é `static void convert(const std::string&)`. Ele recebe um literal C++ em texto, identifica seu tipo original e exibe conversões para `char`, `int`, `float` e `double`.

São reconhecidos caracteres isolados, inteiros decimais, floats com ponto e sufixo `f`, doubles com ponto e os pseudo-literais `nan`, `nanf`, `+inf`, `-inf`, `+inff` e `-inff`. Conversões sem representação válida ou que excedem o tipo de destino são exibidas como `impossível`; caracteres válidos mas não imprimíveis são exibidos como `Não exibível`.

O cast estudado é `static_cast`, adequado para conversões explícitas entre tipos escalares relacionados pela linguagem.

## 2. Como testar e o que é esperado

```bash
cd /home/kyoshi/42/42sp/cpp/cpp06/ex00
make
./convert 0
./convert nan
./convert 42.0f
./convert a
./convert 2147483648
./convert texto
```

Os três primeiros casos devem reproduzir o comportamento do subject: `0` não é um caractere exibível, `nan` não pode virar `char` ou `int`, e `42.0f` vira `'*'`, `42`, `42.0f` e `42.0`. `a` usa seu código numérico nas demais conversões. Os dois últimos casos devem informar literal inválido ou fora dos limites.

O programa exige exatamente um argumento. Compile também com `-Wall -Wextra -Werror -std=c++98`, já incluído no Makefile.

## 3. Fluxo do código e decisões de implementação

O construtor, construtor de cópia, atribuição e destrutor são privados, impedindo que usuários criem instâncias de uma classe que não possui estado. `convert()` é estático e pode ser chamado diretamente pelo nome da classe.

Primeiro, `detectType()` classifica a sintaxe. A validação não aceita texto parcialmente numérico: toda a string precisa corresponder ao formato identificado. Inteiros são lidos com `strtol`; floats e doubles usam `strtod`. `errno`, o ponteiro final e os limites numéricos detectam erros e overflow.

Depois da detecção, o valor é construído em seu tipo real. As conversões para os demais tipos usam `static_cast`. Antes de qualquer cast de ponto flutuante para inteiro ou caractere, o código verifica `nan`, infinito e limites, evitando uma conversão sem representação válida.

As funções de impressão separam as regras de cada destino. Valores integrais de ponto flutuante recebem `.0`; floats recebem o sufixo `f`. Pseudo-literais são normalizados para as formas pedidas pelo enunciado.
