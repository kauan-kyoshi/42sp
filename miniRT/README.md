*Este projeto foi criado como parte do currículo da 42 por klima-do.*

# miniRT

## Descrição

`miniRT` é um ray tracer em C que renderiza cenas 3D descritas por arquivo `.rt`, exibindo o resultado em uma janela via MiniLibX.

Objetivo principal do projeto:
- implementar interseções geométricas e iluminação básica do zero;
- interpretar uma cena textual e gerar uma imagem por ray tracing;
- manter uma arquitetura modular (parsing, núcleo de ray tracing, UI e utilitários).

No estado atual, o projeto cobre os elementos obrigatórios (`A`, `C`, `L`, `sp`, `pl`, `cy`) e inclui extensões extras (como `co`, `tr`, `to`, texturas e bump map).

## Instruções

### Requisitos

- `gcc`
- `make`
- X11 (Linux)
- `libm` (`-lm`)
- MiniLibX (fornecida em `libmlx/`)
- libft (fornecida em `libft/`)

### Compilação

Na raiz do repositório:

```bash
make
```

Alvos disponíveis:
- `make` / `make all`
- `make clean`
- `make fclean`
- `make re`
- `make bonus`

### Execução

```bash
./minirt scenes/mandatory.rt
```

Também é possível usar qualquer cena em `scenes/*.rt`.

### Controles em runtime

- `ESC`: fechar janela e encerrar o programa
- `I`: alternar overlay de informações
- `A`: alternar anti-aliasing

### Exemplo mínimo de cena

```text
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
```

## Recursos

### Referências técnicas

- MiniLibX (fontes do projeto):
  - `libmlx/linux/`
- Documentação C/POSIX:
  - `man 2 open`, `man 2 read`, `man 3 malloc`, `man 3 free`
- Matemática para ray tracing:
  - [Scratchapixel - Ray Tracing](https://www.scratchapixel.com/)
  - [Ray Tracing in One Weekend](https://raytracing.github.io/)

### Uso de IA neste projeto

A IA foi usada como apoio de engenharia, principalmente para:
- refatoração de nomenclatura (funções e variáveis) em módulos de parsing/UI/RT;
- identificação e correção de erros de build e integração;
- ajustes de conformidade de norma (norminette);
- revisão textual e estrutura deste README.

A lógica final, validação com `make`/`norminette` e decisões de arquitetura foram mantidas e verificadas no próprio repositório.

## Estrutura do repositório

- `incs/` — headers principais
- `srcs/main/` — ponto de entrada
- `srcs/parsing/` — parser de cenas `.rt`
- `srcs/rt/` — interseções, shading, ray tracing
- `srcs/ui/` — janela, eventos e render em MLX
- `srcs/utils/` — utilitários gerais
- `scenes/` — cenas de teste
