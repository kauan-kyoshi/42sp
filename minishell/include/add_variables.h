/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 03:50:13 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/01/17 03:51:05 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_VARIABLES_H
# define ADD_VARIABLES_H

# include "exec.h"

char	**copy_env(char **env);
char	**create_array_path(char **env);
void	free_vars_and_arrays(t_all_variables *vars);

#endif
