# cpp03 - ex02

## O que este exercício faz

Este exercício adiciona a classe `FragTrap`, também derivada de `ClapTrap`.

Ela segue a mesma ideia de especialização da `ScavTrap`, mas com outras estatísticas e uma habilidade exclusiva:

- `highFivesGuys()`

## Como funciona

- `FragTrap` herda de `ClapTrap`.
- O construtor redefine os pontos de vida, energia e dano para os valores do exercício.
- `attack()` é sobrescrito para usar a identidade de `FragTrap`.
- `highFivesGuys()` imprime uma solicitação de high five positivo.
- O comportamento de dano e reparo continua vindo da classe base.

## Fluxo de trabalho

1. O `main()` cria um `ClapTrap`, um `ScavTrap` e um `FragTrap`.
2. Depois cria uma cópia de `FragTrap` para validar o construtor de cópia.
3. O programa testa ataque, dano, reparo e a habilidade `highFivesGuys()`.
4. A execução compara o comportamento das três classes para mostrar o que foi herdado e o que foi especializado.

## Lógica do código

Este exercício reforça o uso de herança com personalização de comportamento.

- `FragTrap` usa a infraestrutura de `ClapTrap` como base do estado interno.
- Os valores de atributos são ajustados no construtor para representar uma classe mais resistente.
- `attack()` mantém a mesma lógica de consumo de energia e verificação de vida.
- `highFivesGuys()` é apenas uma função extra, sem alterar pontos ou energia.
- A cópia reaproveita a inicialização da classe base para manter o objeto consistente.

## Como testar

Dentro da pasta `ex02`:

```bash
make
./fragtrap
```

Para limpar:

```bash
make clean
make fclean
```

## Conceitos abordados

- Herança
- Especialização de classes derivadas
- Sobrescrita de métodos
- Reutilização de código da classe base
- Construtor de cópia em hierarquia
- Organização de comportamento por tipo

## O que observar na execução

A principal diferença para o `ClapTrap` é o conjunto de atributos e a presença da habilidade própria `highFivesGuys()`.