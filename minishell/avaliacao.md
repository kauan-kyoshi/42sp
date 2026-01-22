# Avaliação - Apresentação do minishell

Este documento lista o que você deve demonstrar durante a defesa do Projeto Minishell e onde o avaliador pode encontrar cada parte no código-fonte.

**Como usar**
- Compile: `make`
- Rode: `./minishell`
- Para checar leaks (exemplo): `valgrind --leak-check=full --show-leak-kinds=all ./minishell`

**Introdução (o que explicar rapidamente)**
- Objetivo do projeto: implementar uma shell mínima com parsing, expansão, redirecionamentos, pipes, builtins e tratamento de sinais.
- Arquitetura geral: leitura de input -> lexer -> parser -> expander -> executor -> cleanup.
- Principais diretórios/arquivos:
  - [Makefile](Makefile) — regras de compilação e flags.
  - [src/main.c](src/main.c) — loop principal e inicialização.
  - [src/main_signals.c](src/main_signals.c) — tratamento de sinais em foreground/background.

---


**Checklist por tópico (funções exatas e explicação)**

- Compilação
  - **Arquivo:** [Makefile](Makefile)
  - **O que checar:** `make -n` deve mostrar `-Wall -Wextra -Werror` nas flags.

- Comando simples & variáveis globais
  - **Funções:** `lexer_tokenize()` -> [src/lexer.c](src/lexer.c), `cmd_new()` / `add_arg()` -> [src/parser_cmd.c](src/parser_cmd.c)
  - **Como funciona:** A chamada em `lexer_tokenize()` cria tokens a partir da linha de comando; o parser monta `t_cmd` com `cmd_new()` e `add_arg()` para armazenar argumentos. Para execução, `spawn_children()` e `exec_cmd_type()` em [src/exec/exe_cmd_spawn.c](src/exec/exe_cmd_spawn.c) chamam `find_path()` e `execve()` para caminhos absolutos.

- Argumentos
  - **Funções:** `collect_word()` (helpers em `src/lexer_helpers.c`) chamada por `tokenize_fill()` -> [src/lexer.c](src/lexer.c); `add_arg()` -> [src/parser_cmd.c](src/parser_cmd.c)
  - **Como funciona:** O lexer separa palavras (argumentos) usando `collect_word`; `add_arg()` anexa cada argumento ao array `args` do `t_cmd` alocando nova memória.

- `echo`
  - **Funções:** `is_builtin()` e `exec_builtin()` em [src/exec/builtin/is_builtin.c](src/exec/builtin/is_builtin.c) delegam para `ft_echo()` (arquivo do builtin `echo` em `src/exec/builtin/`).
  - **Como funciona:** `is_builtin()` identifica `echo`, então `exec_builtin()` chama `ft_echo()` que processa `-n` e imprime argumentos com `write`/`ft_putstr`.

- `exit`
  - **Funções:** `exec_builtin()` -> `ft_exit()` (builtin `exit`), e `cleanup_and_exit()` -> [src/cleanup.c](src/cleanup.c)
  - **Como funciona:** `ft_exit()` interpreta argumento (se houver) e chama `cleanup_and_exit(status)` que libera `envp`, limpa histórico e chama `exit(status)`.

- Valor de retorno de um processo
  - **Funções:** `spawn_children()` / `waint_all_pids()` / `handle_wait_status()` em [src/exec/exe_cmd_spawn.c](src/exec/exe_cmd_spawn.c) e [src/exec/exe_cmd_helpers.c](src/exec/exe_cmd_helpers.c)
  - **Como funciona:** Após spawn, o pai espera PIDs com `waitpid()` em `waint_all_pids()` e usa `handle_wait_status()` para setar `last_status` (WEXITSTATUS ou 128+signal). Esse `last_status` é usado para `echo $?` e expansão de `$?`.

- Sinais (Signals)
  - **Funções:** `sigint_handler()`, `sigquit_handler()`, `setup_signals()` em [src/main_signals.c](src/main_signals.c)
  - **Como funciona:** `setup_signals()` registra `sigint_handler` e `sigquit_handler` com `sigaction`, ignora TSTP/TTIN/TTOU e desabilita o comportamento padrão do readline (`rl_catch_signals = 0`). `sigint_handler()` grava `g_last_signal`, escreve `^C\n`, limpa a linha do readline com `rl_replace_line()` e redesenha o prompt, evitando que a linha atual seja executada.

- Aspas Duplas / Aspas Simples
  - **Funções:** `lexer` + `lexer_word_finalize` (tokenização) em [src/lexer.c](src/lexer.c) e [src/lexer_word_finalize.c](src/lexer_word_finalize.c); expansão em [src/expander.c](src/expander.c) (`expand_tokens()`, `expand_segment()`)
  - **Como funciona:** O lexer divide segmentos (`t_seg`) marcando `SEG_SINGLE_QUOTED` para aspas simples (onde não se expande). `expand_segment()` ignora segmentos single-quoted; para outros segmentos chama `expand_line()` que resolve `$VAR` e `$?` usando `envp`.

- `env` / `export` / `unset`
  - **Funções:** `ft_export()` / `export_variable()` em [src/exec/builtin/ft_export.c](src/exec/builtin/ft_export.c) e [src/exec/builtin/ft_export_set.c](src/exec/builtin/ft_export_set.c); `ft_unset()` em `src/exec/builtin/` ; utilitários em [src/env_utils.c](src/env_utils.c)
  - **Como funciona:** `export_variable()` valida e insere/atualiza strings `KEY=VALUE` no array `envp` (alocando uma nova cópia). `unset` remove entradas e realoca o array. `env_utils.c` contém helpers para manipular `envp`.

- `cd` / `pwd`
  - **Funções:** `ft_cd()` (builtin cd) em `src/exec/builtin/` e helpers em [include/ft_cd_helpers.h](include/ft_cd_helpers.h) / [src/main_helpers.c](src/main_helpers.c)
  - **Como funciona:** `ft_cd()` chama `chdir()` e atualiza `PWD`/`OLDPWD` no `envp` usando as funções de `env_utils` e `add_variables`.

- Caminho relativo e `$PATH`
  - **Funções:** `find_path()` / `find_path_string()` / `create_array_path()` em [src/add_variables_path.c](src/add_variables_path.c)
  - **Como funciona:** `find_path_string()` obtém o valor de `PATH=`; `create_array_path()` divide em diretórios. `find_path()` (procura em `src/exec/*`) tenta construir caminhos e testar `access()` para localizar executáveis quando o comando não contém `/`.

- Redirecionamento (<, >, >>) e heredoc (<<)
  - **Funções:** `parse_redir_token()` / `get_redir_type()` / `get_redir_target()` em [src/parser_redir.c](src/parser_redir.c); `read_heredoc_lines()` e `write_heredoc_entry()` em [src/parser_heredoc_io.c](src/parser_heredoc_io.c); `spawn_heredoc_reader()` / `exec_heredoc_child()` em [src/parser_heredoc_spawn.c](src/parser_heredoc_spawn.c)
  - **Como funciona:** `parse_redir_token()` reconhece o tipo (`<`, `>`, `>>`, `<<`) via `get_redir_type()`. Para heredoc, `get_redir_target()` chama `create_heredoc()` que usa `read_heredoc_lines()` para criar um arquivo temporário: `spawn_heredoc_reader()` cria um filho que executa a lógica de leitura do heredoc (`exec_heredoc_child()` chama o próprio binário com `--heredoc-child`), escreve no tmpfile e retorna o caminho para o parser.

- Pipes
  - **Funções:** tokenização de pipes em `handle_pipe()` -> [src/lexer.c](src/lexer.c); montagem de `t_cmd` encadeado em [src/parser_cmd.c](src/parser_cmd.c); `spawn_children()` e `set_child_pgrp()` -> [src/exec/exe_cmd_spawn.c](src/exec/exe_cmd_spawn.c)
  - **Como funciona:** O lexer cria tokens `TOK_PIPE`; o parser cria uma lista encadeada de `t_cmd` conectada por `next`. `spawn_children()` cria processos, usa `pipe()`/`dup2()` em `setup_child_io()` (procura em `src/exec/`) para ligar I/O entre comandos e organiza grupos de processo (pgrp) para sinalização correta.

- Histórico / readline
  - **Funções/itens:** integração com `readline` através de chamadas em `parser_heredoc_utils.c` (ex.: `readline("heredoc> ")`) e uso de `clear_history()` / `rl_*` em [src/parser_heredoc_utils.c](src/parser_heredoc_utils.c) e [src/parser_heredoc_helpers.c](src/parser_heredoc_helpers.c).
  - **Como funciona:** O projeto usa a biblioteca `readline`; `rl_*` e `clear_history()` controlam histórico e reexibição. Conferir se as setas navegam no histórico interativo.

- Variáveis de Ambiente e Expansão
  - **Funções:** `expand_tokens()` / `expand_segment()` em [src/expander.c](src/expander.c); `expand_line()` (implementação nas rotinas do expander) e `write_heredoc_entry()` em [src/parser_heredoc_io.c](src/parser_heredoc_io.c)
  - **Como funciona:** `expand_tokens()` caminha sobre tokens `TOK_WORD` e, para cada segmento que não seja `SEG_SINGLE_QUOTED`, chama `expand_segment()` que usa `expand_line()` para substituir `$VAR` e `$?` por seus valores usando `envp`.


**Confiabilidade e memória**
- O shell não deve segfaultar. Caso ocorra, a nota é 0. Faça testes básicos e cargas.
- Verificação de leaks: mostre ao avaliador que você executou `valgrind` ou `leaks` e o relatório está limpo. Arquivos relevantes de limpeza: [src/cleanup.c](src/cleanup.c), [src/free_all_variables.c](src/free_all_variables.c), [src/mem_instrument.c](src/mem_instrument.c).


**Dicas para a defesa (o que dizer se perguntarem)**
- Explique decisões de design: como separou lexer, parser, expander e executor.
- Mostre exemplos concretos (comandos) e indique os arquivos que implementam cada parte.
- Se houver limitações conhecidas, admita-as e explique por que (tempo, prioridade de funcionalidades).


**Comandos úteis para o avaliador**
```
make -n               # checar flags de compilação
make                  # compilar
./minishell           # rodar
valgrind --leak-check=full ./minishell
```

---

Se quiser, eu adapto este `avaliacao.md` adicionando trechos de código/linhas exatas para cada função citada ou criando um roteiro de apresentação passo-a-passo com exemplos prontos. Basta pedir.

**Trechos de código (funções exatas) e onde elas estão**

- `sigint_handler`, `sigquit_handler`, `setup_signals` — tratamento de sinais

```c
void	sigint_handler(int sig)
{
  (void)sig;
  g_last_signal = sig;
  write(1, "^C\n", 3);
  rl_on_new_line();
  rl_replace_line("", 0);
  rl_redisplay();
}

void	sigquit_handler(int sig)
{
  (void)sig;
}

void	setup_signals(void)
{
  struct sigaction	sa;

  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sigint_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGINT, &sa, NULL) == -1)
    perror("sigaction");
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sigquit_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGQUIT, &sa, NULL) == -1)
    perror("sigaction");
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  rl_catch_signals = 0;
}
```

Arquivo: [src/main_signals.c](src/main_signals.c#L17-L51)

- `expand_tokens` / `expand_segment` — expansão de variáveis em tokens

```c
static void	expand_segment(t_seg *seg, char **envp, int last_status)
{
  const char	*s;
  char		*result;
  char		*dup;

  if (seg->type == SEG_SINGLE_QUOTED)
    return ;
  s = seg->str;
  if (!s)
    s = "";
  result = expand_line(s, envp, last_status);
  if (!result)
    return ;
  {
    dup = ft_strdup(result);
    if (!dup)
    {
      free(result);
      return ;
    }
    free(result);
    free(seg->str);
    seg->str = dup;
  }
}

void	expand_tokens(t_token *head, char **envp, int last_status)
{
  t_token	*tk;
  t_seg	*seg;

  tk = head;
  while (tk)
  {
    if (tk->type == TOK_WORD && !tk->no_expand && tk->segs)
    {
      seg = tk->segs;
      while (seg)
      {
        expand_segment(seg, envp, last_status);
        seg = seg->next;
      }
      rebuild_raw(tk);
    }
    tk = tk->next;
  }
}
```

Arquivo: [src/expander.c](src/expander.c#L15-L55)

- `parse_redir_token`, `get_redir_type`, `get_redir_target` — redirecionamentos

```c
static t_redir_type	get_redir_type(t_token_type type)
{
  t_redir_type	rt;

  if (type == TOK_REDIR_IN)
    rt = REDIR_IN;
  else if (type == TOK_REDIR_OUT)
    rt = REDIR_OUT;
  else if (type == TOK_REDIR_APPEND)
    rt = APPEND;
  else
    rt = HEREDOC;
  return (rt);
}

static char	*get_redir_target(t_redir_type rt, t_token *next, char **envp)
{
  char	*target;

  if (rt == HEREDOC)
    target = create_heredoc(next, envp);
  else
    target = ft_strdup(next->raw);
  return (target);
}

t_token	*parse_redir_token(t_token *tk, t_cmd **head, t_cmd **cur,
  char **envp)
{
  t_redir_type	rt;
  t_token		*next;
  char		*target;

  rt = get_redir_type(tk->type);
  next = tk->next;
  if (!next || next->type != TOK_WORD)
  {
    ft_putendl_fd("parse error: redirection without target", 2);
    free_commands(*head);
    return (NULL);
  }
  if (!ensure_cmd(head, cur))
    return (NULL);
  target = get_redir_target(rt, next, envp);
  if (!target || process_redir(cur, rt, target) == -1)
  {
    free_commands(*head);
    return (NULL);
  }
  return (next->next);
}
```

Arquivo: [src/parser_redir.c](src/parser_redir.c#L15-L66)

- `read_heredoc_lines`, `write_heredoc_entry` — I/O do heredoc

```c
int	write_heredoc_entry(int fd, char *line, int expand, char **envp)
{
  char	*expanded;

  if (expand)
  {
    expanded = expand_line(line, envp, 0);
    if (!expanded)
      return (0);
    write(fd, expanded, ft_strlen(expanded));
    write(fd, "\n", 1);
    free(expanded);
  }
  else
  {
    write(fd, line, ft_strlen(line));
    write(fd, "\n", 1);
  }
  return (1);
}

char	*read_heredoc_lines(const char *delimiter, int expand, char **envp)
{
  char		template[128];
  int			fd;
  int			res;
  t_hdoc_ctx	ctx;

  fd = open_unique_tmpfile(template, sizeof(template));
  if (fd == -1)
    return (NULL);
  close(fd);
  ctx.delimiter = delimiter;
  ctx.expand = expand;
  ctx.envp = envp;
  ctx.template = template;
  res = spawn_heredoc_reader(template, &ctx);
  if (res == -1)
  {
    unlink(template);
    return (NULL);
  }
  return (ft_strdup(template));
}
```

Arquivo: [src/parser_heredoc_io.c](src/parser_heredoc_io.c#L15-L66)

- `spawn_heredoc_reader`, `exec_heredoc_child` — spawn do heredoc

```c
static void	exec_heredoc_child(const char *template, t_hdoc_ctx *ctx)
{
  char	exe_path[PATH_MAX + 1];
  char	*argv_child[6];
  char	expand_str[2];
  ssize_t	rlen;

  rlen = readlink("/proc/self/exe", exe_path, PATH_MAX);
  if (rlen <= 0)
  {
    exe_path[0] = '\0';
    ft_strlcpy(exe_path, "/proc/self/exe", PATH_MAX + 1);
  }
  else
    exe_path[rlen] = '\0';
  build_argv_child(argv_child, exe_path, template, ctx->delimiter);
  set_expand_str(expand_str, ctx->expand);
  argv_child[4] = expand_str;
  argv_child[5] = NULL;
  execve(exe_path, argv_child, ctx->envp);
  _exit(127);
}

int	spawn_heredoc_reader(const char *template, t_hdoc_ctx *ctx)
{
  pid_t			pid;
  int				status;
  struct sigaction	old_sa;

  if (install_sigint_ignore(&old_sa) == -1)
  {
    return (-1);
  }
  pid = fork();
  if (pid == -1)
  {
    sigaction(SIGINT, &old_sa, NULL);
    return (-1);
  }
  if (pid == 0)
  {
    exec_heredoc_child(template, ctx);
  }
  status = handle_heredoc_wait(pid, &old_sa);
  return (status);
}
```

Arquivo: [src/parser_heredoc_spawn.c](src/parser_heredoc_spawn.c#L1-L80)

- `handle_pipe`, `lexer_tokenize` — tokenização e pipes

```c
static int	handle_pipe(const char *line, size_t *i, t_token **head)
{
  t_token	*t;

  if (line[*i] == '|')
  {
    t = token_new(TOK_PIPE, NULL);
    if (!t)
      return (-1);
    t->raw = ft_strdup("|");
    if (!t->raw)
    {
      free(t);
      return (-1);
    }
    token_append(head, t);
    (*i)++;
    return (1);
  }
  return (0);
}

t_token	*lexer_tokenize(const char *line)
{
  size_t	len;

  len = 0;
  if (line)
    len = strlen(line);
  return (lexer_tokenize_core(line, len));
}
```

Arquivo: [src/lexer.c](src/lexer.c#L15-L76)

- `cmd_new`, `add_arg`, `add_redir`, `ensure_cmd` — construção de `t_cmd`

```c
t_cmd	*cmd_new(void)
{
  t_cmd	*c;

  c = malloc(sizeof(t_cmd));
  if (!c)
    return (NULL);
  c->pipein = STDIN_FILENO;
  c->pipeout = STDOUT_FILENO;
  c->args = NULL;
  c->redirs = NULL;
  c->next = NULL;
  (void)0;
  return (c);
}

int	add_arg(t_cmd *cmd, const char *arg)
{
  char	**newargv;
  char	**old;

  if (!cmd)
    return (-1);
  newargv = new_argv_with_arg(cmd->args, arg);
  if (!newargv)
    return (-1);
  old = cmd->args;
  cmd->args = newargv;
  if (old)
    free(old);
  return (0);
}

int	add_redir(t_cmd *cmd, t_redir_type type, const char *target)
{
  t_redir	*r;

  if (!cmd || !target)
    return (-1);
  if (type == REDIR_OUT || type == APPEND)
  {
    if (reject_multiple_out_redirs(cmd) == -1)
      return (-1);
  }
  r = malloc(sizeof(t_redir));
  if (!r)
    return (-1);
  r->type = type;
  r->file = ft_strdup(target);
  if (!r->file)
  {
    free(r);
    return (-1);
  }
  r->next = cmd->redirs;
  cmd->redirs = r;
  return (0);
}

t_cmd	*ensure_cmd(t_cmd **head, t_cmd **cur)
{
  if (!*cur)
  {
    *cur = cmd_new();
    if (!*cur)
      return (NULL);
    if (!*head)
      *head = *cur;
  }
  return (*cur);
}
```

Arquivo: [src/parser_cmd.c](src/parser_cmd.c#L1-L110)

- `spawn_children`, `exec_cmd_type`, `child_prepare_and_exec` — execução e spawn de processos

```c
static void	exec_cmd_type(t_cmd *cuntent, char **env, t_all_variables *all)
{
  char	*path;
  int		exit_code;

  if (!cuntent || !cuntent->args || !cuntent->args[0])
  {
    cleanup_child_and_exit(all, 0);
  }
  if (is_builtin(cuntent->args[0]))
  {
    exit_code = exec_builtin(cuntent, env, all);
    cleanup_child_and_exit(all, exit_code);
  }
  path = find_path(cuntent->args[0], env);
  if (!path)
  {
    report_cmd_not_found_and_exit(cuntent->args[0], all);
  }
  if (execve(path, cuntent->args, env) == -1)
  {
    perror("execve error");
    free(path);
    cleanup_child_and_exit(all, 126);
  }
}

int	spawn_children(t_all_variables *all_variables)
{
  t_cmd	*cuntent;
  int		i;

  cuntent = all_variables->cmd;
  i = 0;
  while (cuntent != NULL)
  {
    all_variables->pids[i] = fork();
    if (all_variables->pids[i] == 0)
    {
      child_prepare_and_exec(cuntent, all_variables);
    }
    else if (all_variables->pids[i] > 0)
    {
      set_child_pgrp(i, all_variables);
    }
    cuntent = cuntent->next;
    i++;
  }
  return (i);
}
```

Arquivo: [src/exec/exe_cmd_spawn.c](src/exec/exe_cmd_spawn.c#L1-L120)

- `waint_all_pids`, `handle_wait_status`, `cleanup_child_and_exit` — espera e limpeza do child

```c
int	waint_all_pids(int *pids, int size)
{
  int	i;
  int	status;
  int	last_status;
  int	seen_sigint;

  i = 0;
  last_status = 0;
  seen_sigint = 0;
  while (i < size)
  {
    if (waitpid(pids[i], &status, 0) > 0)
      handle_wait_status(status, &last_status, &seen_sigint);
    i++;
  }
  if (seen_sigint && isatty(STDIN_FILENO))
    write(STDOUT_FILENO, "\n", 1);
  return (last_status);
}

void	cleanup_child_and_exit(t_all_variables *all, int status)
{
  char	***envp_ref;

  envp_ref = NULL;
  if (all)
    envp_ref = all->envp_ref;
  if (all)
    free_all_variables(all);
  if (envp_ref && *envp_ref)
  {
    free_envp(*envp_ref);
    *envp_ref = NULL;
  }
  unregister_envp_ref();
  exit(status);
}
```

Arquivo: [src/exec/exe_cmd_helpers.c](src/exec/exe_cmd_helpers.c#L1-L120)

- `is_builtin` / `exec_builtin` — builtins (echo, cd, pwd, env, export, unset, exit)

```c
int	is_builtin(char *cmd)
{
  if (!cmd)
    return (0);
  if (ft_strncmp(cmd, "echo", 5) == 0)
    return (1);
  if (ft_strncmp(cmd, "cd", 3) == 0)
    return (1);
  if (ft_strncmp(cmd, "pwd", 4) == 0)
    return (1);
  if (ft_strncmp(cmd, "export", 7) == 0)
    return (1);
  if (ft_strncmp(cmd, "unset", 6) == 0)
    return (1);
  if (ft_strncmp(cmd, "env", 4) == 0)
    return (1);
  if (ft_strncmp(cmd, "exit", 5) == 0)
    return (1);
  return (0);
}

int	exec_builtin(t_cmd *cmd, char **env, t_all_variables *all)
{
  (void)all;
  if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
    return (ft_echo(cmd->args));
  if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
    return (ft_cd(cmd->args, all->envp_ref));
  if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
    return (ft_pwd(cmd->args));
  if (ft_strncmp(cmd->args[0], "env", 4) == 0)
    return (ft_env(env, cmd->args));
  if (ft_strncmp(cmd->args[0], "export", 7) == 0)
    return (ft_export(cmd->args, all->envp_ref));
  if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
    return (ft_unset(cmd->args, all->envp_ref));
  return (0);
}
```

Arquivo: [src/exec/builtin/is_builtin.c](src/exec/builtin/is_builtin.c#L1-L80)

---

Se quiser, eu insiro também os números de linha exatos para cada função após executar uma busca que gere as linhas iniciais/finais exatas; quer que eu faça isso agora e atualize os links com ranges precisos?
