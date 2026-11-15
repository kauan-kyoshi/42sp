# CPP06 — Casts em C++

## Visão geral

O CPP06 estuda três casts explícitos da linguagem C++. Cada exercício apresenta uma situação na qual um cast diferente expressa corretamente a intenção do programa:

```text
ex00: valor escalar ──static_cast──> outro tipo escalar
ex01: ponteiro ──reinterpret_cast──> inteiro ──reinterpret_cast──> ponteiro
ex02: Base ──dynamic_cast──> descoberta do tipo derivado real
```

Os três exercícios são obrigatórios. O subject não possui exercício bônus. Cada pasta é um programa independente, com seu próprio Makefile, classes e testes.

A regra adicional do módulo exige que a conversão de cada exercício seja tratada com um tipo específico de cast. A escolha faz parte do que será avaliado durante a defesa; por isso, entender por que cada cast foi usado é tão importante quanto obter a saída correta.

## Comparação dos exercícios

| Exercício | Conversão | Cast principal | Informação disponível | Verificação em tempo de execução |
| --- | --- | --- | --- | --- |
| `ex00` | Entre `char`, `int`, `float` e `double` | `static_cast` | A relação entre os tipos é conhecida pelo compilador | Limites e casos especiais são verificados pelo código |
| `ex01` | Entre `Data*` e `uintptr_t` | `reinterpret_cast` | O programa preserva a representação numérica do endereço | O cast não valida se o endereço aponta para um objeto vivo |
| `ex02` | De `Base*` ou `Base&` para `A`, `B` ou `C` | `dynamic_cast` | O tipo estático é `Base`, mas o tipo real varia | O RTTI verifica a hierarquia durante a execução |

## Antes dos casts: tipo estático e tipo dinâmico

O tipo estático é conhecido pelo compilador a partir da declaração. No exemplo abaixo, o tipo estático de `object` é `Base*`:

```cpp
Base *object = new A;
```

O tipo dinâmico é o tipo real do objeto durante a execução: nesse caso, `A`. Essa distinção é central no `ex02`.

Nos tipos escalares do `ex00`, não existe essa relação polimórfica. O programa possui um valor numérico e solicita outra representação escalar. No `ex01`, a conversão também não depende de herança: ela preserva um endereço em um tipo inteiro.

## ex00 — Conversão de tipos escalares

### Objetivo

`ScalarConverter::convert()` recebe uma string que representa um literal C++ e imprime o valor como:

- `char`;
- `int`;
- `float`;
- `double`.

A classe não guarda estado e não pode ser instanciada. O método é estático e os membros canônicos ficam privados.

### Progressão interna do exercício

O trabalho acontece em quatro etapas:

1. Detectar o tipo representado pela string.
2. Validar e converter o texto para seu tipo real.
3. Converter explicitamente o valor para os outros tipos escalares.
4. Exibir cada resultado ou informar que a conversão é impossível.

Essa ordem é exigida pelo subject. Não basta converter tudo diretamente para um tipo conveniente sem primeiro identificar o literal original.

### Tipos reconhecidos

| Entrada | Tipo detectado | Observação |
| --- | --- | --- |
| `a` | `char` | Caractere isolado que não é um dígito |
| `0`, `-42`, `42` | `int` | Inteiro decimal dentro dos limites de `int` |
| `0.0f`, `-4.2f`, `1e-3f` | `float` | Marcador decimal ou expoente e sufixo `f` |
| `0.0`, `-4.2`, `1e3` | `double` | Marcador decimal ou expoente, sem sufixo `f` |
| `nanf`, `+inff`, `-inff` | pseudo-literal `float` | Valores especiais |
| `nan`, `+inf`, `-inf` | pseudo-literal `double` | Valores especiais |

Entradas como `42f`, `1.2.3`, `texto` ou texto numérico com caracteres restantes são rejeitadas. `42f` não é um literal de ponto flutuante válido em C++ porque não contém ponto decimal nem expoente.

### Por que `static_cast`

`static_cast` é apropriado quando existe uma conversão conhecida entre os tipos. C++ define conversões entre os quatro tipos escalares usados no exercício:

```cpp
float value = 42.0f;
int integer = static_cast<int>(value);
double wider = static_cast<double>(value);
```

O cast torna explícito que uma mudança de representação foi solicitada. Ele é verificado sintaticamente pelo compilador, mas não impede sozinho perda de informação ou overflow. Por isso o código verifica limites antes de casts perigosos.

### Conversões impossíveis

`nan` e infinito não possuem representação válida como `int` ou `char`. Um valor fora de `INT_MIN..INT_MAX` também não pode ser convertido com segurança para `int`. Da mesma forma, um valor finito maior que `float::max()` não pode ser representado como `float` finito.

As verificações acontecem antes do cast. Isso evita depender do resultado de uma conversão fora da faixa representável.

### Caractere impossível e não exibível

Esses resultados significam coisas diferentes:

- `impossível`: não existe conversão válida, como `nan → char` ou um valor fora da faixa de `char`;
- `Não exibível`: existe um código de caractere válido, mas ele não representa um caractere imprimível, como o valor zero.

Quando o valor está entre 32 e 126, ele é exibido entre aspas simples.

### Conversão do texto

Inteiros usam `strtol`, enquanto floats e doubles usam `strtod`. Essas funções ajudam a obter o valor, mas o código ainda precisa:

- validar que toda a string foi consumida;
- verificar `errno == ERANGE`;
- conferir os limites do tipo final;
- remover o sufixo `f` somente depois de identificar um float;
- tratar pseudo-literais separadamente.

### Formatação

Valores de ponto flutuante sem parte fracionária recebem `.0`, e floats recebem o sufixo `f`. Assim, `42.0f` é distinguido de `42.0`, mesmo quando ambos representam o mesmo valor matemático.

## ex01 — Serialização de um endereço

### Objetivo

`Serializer` fornece dois métodos estáticos:

```cpp
uintptr_t serialize(Data *ptr);
Data *deserialize(uintptr_t raw);
```

O teste cria uma estrutura `Data` não vazia, converte seu endereço para inteiro, converte o inteiro de volta e confirma que o ponteiro restaurado é igual ao original.

### O que “serialização” significa aqui

Em aplicações reais, serializar normalmente significa transformar dados em bytes que possam ser armazenados ou transmitidos. Este exercício usa o termo em um sentido limitado: transformar temporariamente o valor de um ponteiro em um inteiro sem sinal.

O resultado:

- não contém uma cópia independente dos campos de `Data`;
- não pode ser salvo e reutilizado em outra execução;
- não prolonga a vida do objeto;
- não é um endereço válido em outro processo ou máquina.

O objeto original precisa continuar vivo quando o ponteiro restaurado for usado.

### Por que `uintptr_t`

`uintptr_t`, quando disponibilizado pela plataforma, é um inteiro sem sinal capaz de receber a representação convertida de um ponteiro. Usar simplesmente `unsigned int` seria incorreto em máquinas nas quais ponteiros são maiores que esse tipo.

O exercício inclui `<stdint.h>`, compatível com a compilação usada no projeto, para obter essa definição.

### Por que `reinterpret_cast`

`reinterpret_cast` expressa uma conversão de baixo nível entre representações que não possuem uma relação numérica comum:

```cpp
uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
Data *restored = reinterpret_cast<Data *>(raw);
```

`static_cast` não é o cast correto para essa conversão direta entre ponteiro e inteiro. `dynamic_cast` também não se aplica, porque não há descoberta de tipo dentro de uma hierarquia polimórfica.

### O que o cast garante e o que não garante

Na ida e volta correta, o ponteiro reconstruído compara igual ao original. Entretanto, `reinterpret_cast` não verifica:

- se o inteiro veio realmente de um `Data*`;
- se o objeto ainda existe;
- se o endereço está alinhado;
- se é seguro desreferenciar o resultado.

O programador é responsável por preservar essas condições. No teste, o objeto `Data` é local ao `main()` e continua vivo durante toda a conversão.

### Classe sem estado

Assim como `ScalarConverter`, `Serializer` não precisa de instâncias. Seus construtores, atribuição e destrutor ficam privados e sem definição; somente os métodos estáticos são acessíveis.

## ex02 — Identificação do tipo real

### Objetivo

O exercício cria a hierarquia:

```text
        Base
       /  |  \
      A   B   C
```

`Base` possui apenas um destrutor virtual público. `A`, `B` e `C` são classes vazias que herdam publicamente da base. Essas quatro classes estão explicitamente dispensadas da Forma Canônica Ortodoxa.

`generate()` escolhe aleatoriamente uma das classes concretas e retorna a instância como `Base*`. Duas funções precisam descobrir o tipo real:

```cpp
void identify(Base *p);
void identify(Base &p);
```

É proibido usar `std::typeinfo`, incluir `<typeinfo>` ou usar ponteiros dentro da versão que recebe referência.

### Por que a base precisa ser polimórfica

`dynamic_cast` precisa de informações de tipo em tempo de execução quando realiza uma conversão descendente. Uma classe com ao menos uma função virtual é polimórfica. O destrutor virtual cumpre essa função e também torna seguro apagar objetos derivados por `Base*`.

```cpp
Base *object = new A;
delete object;
```

O tipo estático do ponteiro é `Base*`, mas o destrutor virtual garante que o tipo dinâmico seja respeitado.

### `dynamic_cast` com ponteiros

A conversão para ponteiro falha retornando `0`:

```cpp
if (dynamic_cast<A *>(p))
    std::cout << "A" << std::endl;
```

Esse comportamento permite tentar `A*`, depois `B*` e por fim `C*`. Um `Base*` nulo também resulta em casts nulos e é tratado como tipo desconhecido.

### `dynamic_cast` com referências

Referências não possuem um valor nulo para representar falha. Portanto, um cast incorreto de referência lança uma exceção:

```cpp
try
{
    (void)dynamic_cast<A &>(p);
    std::cout << "A" << std::endl;
}
catch (...)
{
}
```

O código repete a tentativa para `B&` e `C&`. O `catch (...)` é usado porque nomear `std::bad_cast` exigiria `<typeinfo>`, cabeçalho proibido pelo enunciado. Nenhum ponteiro é criado dentro dessa função.

### Por que `dynamic_cast`

`dynamic_cast` foi projetado para conversões seguras dentro de hierarquias polimórficas. Ele consulta o tipo real do objeto e sinaliza uma incompatibilidade de forma definida.

Usar `static_cast<A*>(p)` poderia compilar, mas afirmaria sem verificação que o objeto é `A`. Se ele fosse realmente `B`, usar o resultado como `A` seria inseguro. `reinterpret_cast` seria ainda menos apropriado, pois apenas reinterpretaria a representação do endereço sem consultar a hierarquia.

### Aleatoriedade e memória

`generate()` inicializa o gerador pseudoaleatório uma vez, escolhe um valor entre 0 e 2 e usa `new` para criar o objeto. O chamador recebe a propriedade e precisa executar `delete` depois das duas identificações.

A saída pode repetir tipos e não precisa conter obrigatoriamente `A`, `B` e `C` em toda execução. Aleatoriedade não garante distribuição uniforme em uma amostra pequena.

## Progressão conceitual

### 1. Conversão de valores conhecidos

O `ex00` trabalha com valores e tipos escalares conhecidos. O desafio está em interpretar texto, reconhecer limites e controlar perda de representação.

### 2. Conversão de representação

O `ex01` deixa o domínio das conversões numéricas comuns. O endereço é preservado como um inteiro, e a linguagem exige um cast que explicite essa operação de baixo nível.

### 3. Conversão baseada no objeto real

O `ex02` introduz uma decisão que só pode ser feita durante a execução. O tipo estático não revela se o objeto é `A`, `B` ou `C`; `dynamic_cast` usa as informações da hierarquia polimórfica.

## Como escolher entre os casts estudados

Uma forma prática de raciocinar é perguntar qual relação existe entre origem e destino:

```text
Os tipos possuem uma conversão de valor definida?
    └── sim: static_cast

É necessário preservar/reinterpretar uma representação de baixo nível?
    └── sim: reinterpret_cast

É necessário verificar o tipo real em uma hierarquia polimórfica?
    └── sim: dynamic_cast
```

Essa árvore não cobre todos os casts e situações possíveis da linguagem, mas explica as escolhas específicas do CPP06.

## O cast ausente: `const_cast`

O módulo se concentra em `static_cast`, `reinterpret_cast` e `dynamic_cast`. `const_cast` é o cast usado para adicionar ou remover qualificadores `const` e `volatile`. Nenhum dos três exercícios exige remover constância, portanto ele não é necessário nesta implementação.

Remover `const` não torna automaticamente seguro modificar um objeto. Se o objeto original foi realmente criado como constante, alterá-lo depois de remover o qualificador provoca comportamento indefinido.

## Regras comuns de implementação

Todos os exercícios compilam com:

```bash
c++ -Wall -Wextra -Werror -std=c++98
```

Também são respeitadas as regras gerais do módulo:

- sem bibliotecas externas ou recursos de C++11;
- sem `using namespace` ou `friend`;
- sem contêineres STL ou `<algorithm>`;
- sem `printf`, funções de alocação da família C ou `free`;
- implementações fora dos cabeçalhos, exceto as classes vazias permitidas;
- cabeçalhos independentes e protegidos contra inclusão dupla;
- liberação de toda memória criada com `new`.

## Ordem recomendada de estudo

1. Execute `ex00/convert` com os exemplos do subject.
2. Leia `detectType()` e acompanhe como a string é classificada.
3. Localize cada `static_cast` e identifique a verificação feita antes dele.
4. No `ex01`, compare o endereço antes e depois da ida e volta.
5. Explique por que o inteiro não é uma cópia dos dados de `Data`.
6. No `ex02`, observe primeiro a diferença entre `Base*` e o objeto criado por `generate()`.
7. Compare a falha de `dynamic_cast` para ponteiro com a falha para referência.
8. Confirme onde cada objeto criado com `new` é liberado.

Os READMEs individuais apresentam comandos de teste e detalhes de cada implementação:

- [`ex00/README.md`](ex00/README.md)
- [`ex01/README.md`](ex01/README.md)
- [`ex02/README.md`](ex02/README.md)
