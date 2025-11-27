/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:26:53 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/27 16:26:54 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_redir_type
{
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
}   t_redir_type;

typedef struct s_redir
{
    t_redir_type    type;
    char            *target;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char        **argv;
    t_redir     *redirs;
    struct s_cmd *next;
}   t_cmd;

t_cmd   *parse_tokens(t_token *tokens);
void    print_commands(t_cmd *cmds);
void    free_commands(t_cmd *cmds);

#endif
