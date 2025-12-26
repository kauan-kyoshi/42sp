/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:41:10 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/26 18:17:18 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (!parse_args(argc, argv, &args))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	return (0);
}
