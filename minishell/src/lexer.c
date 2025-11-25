/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:03:07 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/25 18:05:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int	handle_metachar(const char *line, size_t *i, size_t len,
	 t_token **head)
{
	 t_token *t;

	 if (line[*i] == '|')
	 {
		t = token_new(TOK_PIPE, "|");
		if (!t)
			return (0);
		token_append(head, t);
		(*i)++;
		return (1);
	 }
	 if (line[*i] == '>' || line[*i] == '<')
	 {
		 if (line[*i] == '>' && *i + 1 < len && line[*i + 1] == '>')
		 {
			 t = token_new(TOK_REDIR_APPEND, ">>");
			 if (!t)
				 return (0);
			 token_append(head, t);
			 *i += 2;
			 return (1);
		 }
		 if (line[*i] == '<' && *i + 1 < len && line[*i + 1] == '<')
		 {
			 t = token_new(TOK_HEREDOC, "<<");
			 if (!t)
				 return (0);
			 token_append(head, t);
			 *i += 2;
			 return (1);
		 }
		 if (line[*i] == '>')
		 {
			 t = token_new(TOK_REDIR_OUT, ">");
			 if (!t)
				 return (0);
			 token_append(head, t);
			 (*i)++;
			 return (1);
		 }
		 if (line[*i] == '<')
		 {
			 t = token_new(TOK_REDIR_IN, "<");
			 if (!t)
				 return (0);
			 token_append(head, t);
			 (*i)++;
			 return (1);
		 }
	 }
	 return (0);
}

static int	append_word_token(const char *line, size_t start, size_t end,
	t_token **head)
{
	 char *raw;
	 t_token *t;

	 raw = malloc(end - start + 1);
	 if (!raw)
		 return (-1);
	 memcpy(raw, line + start, end - start);
	 raw[end - start] = '\0';
	 t = token_new(TOK_WORD, raw);
	 free(raw);
	 if (!t)
		 return (-1);
	 token_append(head, t);
	 return (0);
}

static int	collect_word(const char *line, size_t *i, size_t len,
	t_token **head)
{
	 size_t start;
	 char q;

	 start = *i;
	 while (*i < len)
	 {
		 if (line[*i] == '\'' || line[*i] == '"')
 {
 q = line[(*i)++];
 while (*i < len && line[*i] != q)
 (*i)++;
 if (*i >= len)
 {
 token_free_all(*head);
 *head = token_new(TOK_ERROR, "unterminated_quote");
 return (-2);
 }
 (*i)++;
 continue;
 }
 if (isspace((unsigned char)line[*i]) || line[*i] == '|' ||
 line[*i] == '<' || line[*i] == '>')
 break;
 (*i)++;
 }
 if (append_word_token(line, start, *i, head) == -1)
 return (-1);
 return (0);
}

t_token	*lexer_tokenize(const char *line)
{
 size_t i;
 size_t len;
 t_token *head;

 i = 0;
 len = line ? strlen(line) : 0;
 head = NULL;
 while (i < len)
 {
 if (isspace((unsigned char)line[i]))
 {
 i++;
 continue;
 }
 if (handle_metachar(line, &i, len, &head))
 continue;
 if (collect_word(line, &i, len, &head) != 0)
 return (head);
 }
 return (head);
}
