# cpp03 - ex03

## O que este exercício faz

Este exercício cria a classe `DiamondTrap`, que combina funcionalidades de `ScavTrap` e `FragTrap`.

Ele é o primeiro exercício do cpp03 que trabalha com uma herança em formato de diamante, por isso o uso de herança virtual nas classes intermediárias.

## Como funciona

- `DiamondTrap` herda de `ScavTrap` e `FragTrap`.
- As classes intermediárias herdando virtualmente de `ClapTrap` evitam duplicação da subclasse base.
- O construtor define um nome próprio para `DiamondTrap` e também o nome interno de `ClapTrap` com o sufixo `_clap_name`.
- Os atributos de batalha são ajustados para os valores do exercício.
- `attack()` usa o comportamento de `ScavTrap`.
- `whoAmI()` mostra o nome de `DiamondTrap` e o nome armazenado na parte `ClapTrap`.

## Fluxo de trabalho

1. O `main()` cria instâncias de `ClapTrap`, `ScavTrap`, `FragTrap` e `DiamondTrap`.
2. Depois cria uma cópia de `DiamondTrap` para validar a construção por cópia.
3. O programa executa ataques, `guardGate()`, `highFivesGuys()` e `whoAmI()`.
4. A saída mostra como `DiamondTrap` reaproveita comportamento das classes base sem perder sua identidade.

## Lógica do código

Aqui o ponto principal é resolver o problema do diamante de herança.

- A herança virtual em `ScavTrap` e `FragTrap` garante que exista apenas um subobjeto `ClapTrap` dentro de `DiamondTrap`.
- Isso evita ambiguidade ao acessar membros da classe base.
- `DiamondTrap` tem seu próprio nome, separado do nome interno herdado de `ClapTrap`.
- `attack()` delega para `ScavTrap`, aproveitando o comportamento já definido lá.
- `whoAmI()` deixa explícita a diferença entre o nome da composição principal e o nome da base virtual.
- A classe também herda `guardGate()` e `highFivesGuys()` das respectivas bases, mostrando reutilização dos dois ramos da hierarquia.

## Como testar

Dentro da pasta `ex03`:

```bash
make
./diamondtrap
```

Para limpar:

```bash
make clean
make fclean
```

## Conceitos abordados

- Herança múltipla
- Herança virtual
- Problema do diamante
- Resolução de ambiguidade em hierarquias
- Reutilização de comportamento de múltiplas classes
- Polimorfismo por especialização
- Separação entre nome da classe derivada e nome da base

## O que observar na execução

O teste principal é ver `whoAmI()` mostrando dois nomes diferentes: o nome próprio de `DiamondTrap` e o nome da parte `ClapTrap`. Isso confirma que a herança virtual está funcionando como esperado.