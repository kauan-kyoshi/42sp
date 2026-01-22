# Enunciado: rip

Assignment name  : rip
Expected files   : *.c *.h
Allowed functions: puts, write
--------------------------------------------------------------------------------

Escreva um programa que receba como argumento uma string contendo apenas
parênteses `'('` e `')'`.

Se os parênteses estiverem desbalanceados (por exemplo: `())`), o seu programa
deverá remover o número mínimo de parênteses para que a expressão fique
balanceada. Remover significa substituir o caractere por um espaço.

Deverá então imprimir todas as soluções possíveis (pode haver mais de uma).

A ordem das soluções não é importante.

Exemplos de execução esperados:

```
$> ./rip '(()' | cat -e
 ()$
( )$

$> ./rip '((()()())())' | cat -e
((()()())())$

$> ./rip '()())()'| cat -e
()() ()$
()( )()$
( ())()$

$> ./rip '(()(()(' | cat -e
(()  ) $
( )( ) $
( ) () $
 ()( ) $
```

Notas:
- O programa deve apenas usar `puts` e `write` como funções de saída.
- Em caso de erro de execução você pode optar por retornar `1`.

--------------------------------------------------------------------------------
