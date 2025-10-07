Com certeza! A avaliação do projeto `so_long` na 42 segue uma "régua" ou "barema" bastante específico, que verifica desde a compilação até a lógica do jogo e o gerenciamento de erros. Abaixo está uma lista detalhada dos critérios que são tipicamente verificados durante a correção por pares.

---

### **Critérios de Avaliação do `so_long`**

#### **Parte I: Parte Obrigatória**

**1. Compilação e Normas**
*   **Makefile:** O `Makefile` deve compilar o projeto sem erros.
*   **Regras do Makefile:** Deve conter as regras padrão: `all`, `clean`, `fclean` e `re`.
*   **Norminette:** O código deve estar de acordo com as normas da 42 (Norminette v3).

**2. Gerenciamento de Erros e Parsing do Mapa**
*   **Argumentos:** O programa aceita apenas um argumento, que é o caminho para um mapa (`./so_long maps/map.ber`).
    *   Testar com zero ou mais de um argumento. O programa deve exibir "Error\n" e sair.
*   **Extensão do Arquivo:** O mapa deve ter a extensão `.ber`. Qualquer outra extensão deve resultar em erro.
*   **Leitura do Mapa:** O programa consegue ler e interpretar o mapa corretamente. Um descritor de arquivo inválido (mapa que não existe, sem permissão de leitura) deve ser tratado como erro.
*   **Formato do Mapa:**
    *   **Retangular:** O mapa deve ser retangular (todas as linhas devem ter o mesmo comprimento). Mapas não retangulares devem gerar erro.
    *   **Caracteres Válidos:** O mapa só pode conter os caracteres `0`, `1`, `C`, `E`, `P`. Qualquer outro caractere deve gerar erro.
    *   **Composição Mínima:** O mapa deve conter pelo menos `1` Saída (E), `1` Coletável (C) e `1` Posição de Jogador (P). A falta de qualquer um deles é um erro.
    *   **Composição Única:** O mapa deve conter apenas `1` Posição de Jogador (P) e `1` Saída (E). Múltiplos jogadores ou saídas devem ser tratados como erro.
    *   **Mapa Fechado/Murado:** O mapa deve estar completamente cercado por paredes (`1`). Qualquer abertura nas bordas é um erro.

**3. Validação de Caminho Válido (Pathfinding)**
*   **Existência de um Caminho Válido:** Esta é uma verificação crucial. O avaliador verificará se o programa consegue determinar se existe um caminho possível do jogador (`P`) para todos os coletáveis (`C`) e, depois de coletá-los, para a saída (`E`).
    *   Mapas onde os coletáveis ou a saída são inacessíveis (bloqueados por paredes) devem ser considerados inválidos e gerar um erro.
    *   Geralmente, isso é implementado com um algoritmo como o **Flood Fill**.

**4. Lógica do Jogo e Gráficos**
*   **Abertura da Janela:** O jogo deve abrir uma janela gráfica ao receber um mapa válido.
*   **Renderização:** O mapa (paredes, chão, jogador, coletáveis, saída) deve ser renderizado corretamente na janela usando as texturas (imagens `.xpm`).
*   **Movimentação:**
    *   O jogador se move para cima, baixo, esquerda e direita com as teclas `W`, `A`, `S`, `D`.
    *   O jogador não deve conseguir atravessar paredes.
*   **Contador de Movimentos:** O número de movimentos do jogador deve ser exibido no terminal a cada passo.
*   **Lógica dos Coletáveis:** O jogador deve coletar todos os itens (`C`) ao passar por cima deles. Os coletáveis devem desaparecer do mapa após serem coletados.
*   **Lógica da Saída:**
    *   A saída (`E`) só funciona *depois* que todos os coletáveis forem recolhidos.
    *   Tentar sair antes de coletar tudo não deve ter efeito.
    *   Ao chegar na saída com todos os itens coletados, o jogo termina e a janela fecha.

**5. Gerenciamento de Janela e Finalização**
*   **Tecla ESC:** Pressionar a tecla `ESC` deve fechar a janela e encerrar o programa de forma limpa, sem vazamentos de memória.
*   **Botão de Fechar:** Clicar no "X" vermelho da janela também deve fechar o programa de forma limpa.
*   **Gerenciamento de Memória:** O programa não deve ter vazamentos de memória (memory leaks).

---

#### **Parte II: Bônus**

*   **Animações:** O jogador e/ou os coletáveis possuem sprites animados (por exemplo, o personagem "respira" ou o coletável gira).
*   **Inimigos:** Existem patrulhas ou inimigos no mapa. Se o jogador tocar em um inimigo, o jogo termina (derrota).
*   **Contador na Tela:** O contador de movimentos é exibido na janela do jogo em vez do terminal.
*   **Efeitos Adicionais:** Qualquer outra melhoria visual ou de jogabilidade, como efeitos sonoros, diferentes skins, etc.

É fundamental que a parte obrigatória esteja perfeita antes de tentar os bônus. Um bônus que quebra uma funcionalidade obrigatória resultará em uma nota zero para o projeto.