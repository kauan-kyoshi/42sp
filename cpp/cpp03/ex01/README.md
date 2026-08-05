# cpp03 - ex01

## O que este exercício faz

Este exercício cria a classe `ScavTrap` a partir de `ClapTrap` usando herança.

O objetivo é reaproveitar o comportamento base e adicionar características próprias:

- mais pontos de vida
- mais energia
- mais dano de ataque
- habilidade especial `guardGate()`

## Como funciona

- `ScavTrap` herda de `ClapTrap`.
- O construtor redefine os atributos base para os valores específicos da classe filha.
- `attack()` é sobrescrito para exibir a ação com a identidade de `ScavTrap`.
- `guardGate()` imprime uma mensagem exclusiva da classe.
- O restante do comportamento, como `takeDamage()` e `beRepaired()`, continua vindo de `ClapTrap`.

## Fluxo de trabalho

1. O `main()` cria um `ClapTrap` normal para comparar o comportamento com a classe derivada.
2. Em seguida, cria um `ScavTrap` nomeado `Serena`.
3. Um segundo `ScavTrap` é criado por cópia.
4. O programa testa o ataque, o modo `guardGate()` e o uso herdado de `takeDamage()` e `beRepaired()`.
5. As mensagens mostram quais métodos vêm da classe base e quais são específicos da classe filha.

## Lógica do código

O foco aqui é reutilizar a base sem perder a identidade da classe derivada.

- `ScavTrap` começa com atributos mais fortes do que `ClapTrap`.
- `attack()` usa a mesma ideia da classe base, mas imprime o nome da classe derivada.
- Como `takeDamage()` e `beRepaired()` não foram sobrescritos, o comportamento padrão de `ClapTrap` continua válido.
- O método `guardGate()` representa uma habilidade exclusiva e não altera o estado interno.
- A cópia e a atribuição usam o mecanismo herdado para manter o estado consistente.

## Como testar

Dentro da pasta `ex01`:

```bash
make
./scavtrap
```

Para limpar:

```bash
make clean
make fclean
```

## Conceitos abordados

- Herança em C++
- Reaproveitamento de código
- Sobrescrita de método
- Especialização de classe
- Acesso a membros herdados
- Construtores em classes derivadas
- Polimorfismo básico de comportamento

## O que observar na execução

Você deve ver que `ScavTrap` tem identidade própria nas mensagens e valores internos diferentes de `ClapTrap`, mas ainda consegue usar funcionalidades herdadas.