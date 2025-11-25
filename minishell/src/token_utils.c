/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:05:52 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/25 18:09:42 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_token *token_new(t_token_type type, const char *raw)
{
	 t_token *t;

	 t = malloc(sizeof *t);
	 if (!t)
		 return (NULL);
	 t->type = type;
	 t->raw = raw ? strdup(raw) : NULL;
	 t->next = NULL;
	 return (t);
}

void    token_append(t_token **head, t_token *node)
{
	 t_token *p;

	 if (!node)
		 return;
	 if (!*head)
	 {
		 *head = node;
		 return;
	 }
	 p = *head;
	 while (p->next)
		 p = p->next;
	 p->next = node;
}

void    token_free_all(t_token *tok)
{
	 while (tok)
	 {
		 t_token *n;

		 n = tok->next;
		 free(tok->raw);
		 free(tok);
		 tok = n;
	 }
}

void    token_debug_print(const t_token *tok)
{
	 static const char *names[] = {
		 "WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
		 "REDIR_APPEND", "HEREDOC", "END", "ERROR"
	 };
	 const char *name;

	 while (tok)
	 {
		 if (tok->type >= 0 && tok->type <= TOK_ERROR)
			 name = names[tok->type];
		 else
			 name = "UNKNOWN";
		 printf("TOKEN %-13s : \"%s\"\n", name,
 tok->raw ? tok->raw : "(null)");
		 tok = tok->next;
	 }
}
