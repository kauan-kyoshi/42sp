# cpp03 - ex00

## O que este exercício faz

Este exercício introduz a classe `ClapTrap`, que simula uma pequena unidade de combate com nome, pontos de vida, energia e dano de ataque.

A classe já possui os fundamentos de uma entidade jogável:

- construção e cópia de objetos
- ataque a um alvo
- receber dano
- ser reparada

## Como funciona

- `_name` guarda o nome do ClapTrap.
- `_hitPoints` representa a vida atual.
- `_energyPoints` controla quantas ações o personagem ainda pode executar.
- `_attackDamage` define quanto dano o ataque causa.
- `attack()` reduz energia e imprime a ação de ataque.
- `takeDamage()` reduz os pontos de vida sem deixar o valor ficar negativo.
- `beRepaired()` recupera vida e também gasta energia.

## Fluxo de trabalho

1. O programa cria um `ClapTrap` chamado `Alpha`.
2. Em seguida, cria uma cópia desse objeto.
3. Cada objeto executa `attack()`, `takeDamage()` e `beRepaired()` em sequência.
4. As mensagens impressas mostram como o estado interno muda conforme cada ação.
5. Ao sair de escopo, os destrutores são chamados automaticamente.

## Lógica do código

O objetivo aqui é manter o estado do personagem coerente.

- `attack()` só funciona se houver vida e energia disponíveis.
- Ao atacar, o objeto consome 1 ponto de energia.
- `takeDamage()` zera a vida quando o dano recebido é maior ou igual à vida atual.
- `beRepaired()` também depende de vida e energia, porque a ação precisa de um personagem ainda ativo.
- O construtor padrão e o construtor com nome inicializam o objeto com valores base definidos no exercício.
- O construtor de cópia e o operador de atribuição garantem que outro `ClapTrap` possa ser duplicado corretamente.

## Como testar

Dentro da pasta `ex00`:

```bash
make
./claptrap
```

Para limpar:

```bash
make clean
make fclean
```

## Conceitos abordados

- Classes em C++
- Encapsulamento
- Construtor padrão e construtor com parâmetro
- Construtor de cópia
- Operador de atribuição
- Destrutor
- Controle de estado interno
- Fluxo condicional com validação de recursos

## O que observar na execução

O comportamento esperado é ver a queda de energia ao atacar e reparar, além da redução de vida ao tomar dano. As mensagens ajudam a validar a ordem das ações.