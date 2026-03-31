/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:28:26 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:01:42 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_scene_requirements(t_rt *rt)
{
	if (!rt->ambient.id)
		return (report_error(ERR_MISSING_AMBIENT_PARAMS));
	if (!rt->camera.id)
		return (report_error(ERR_MISSING_CAMERA_PARAMS));
	if (!rt->light)
		return (report_error(ERR_MISSING_LIGHT_PARAMS));
	return (0);
}

int	has_rt_extension(char *path)
{
	int	len;

	len = ft_strlen(path) - 3;
	if (len > 3)
		return (ft_strncmp(path + len, ".rt", 3) == 0);
	return (0);
}

int	parse_scene_from_fd(t_rt *rt, int fd)
{
	int		num;
	int		ret;
	char	*line;

	num = 0;
	ret = 0;
	while (ret != 1)
	{
		num++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line = normalize_scene_line(line);
		rt->lnum = num;
		if (line[0] && line[0] != '#' && parse_scene_line(rt, line))
			ret = 1;
		free(line);
	}
	if (!ret && validate_scene_requirements(rt))
		ret = 1;
	close(fd);
	return (ret);
}

int	load_scene_file(t_rt *rt, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (!report_error(ERR_FILE_NOT_FOUND));
	if (!has_rt_extension(path))
		return (!report_error(ERR_IS_NOT_RT_FILE));
	if (parse_scene_from_fd(rt, fd))
		return (0);
	return (1);
}

char	*normalize_scene_line(char *line)
{
	int		i;
	char	*tmp;
	char	*clean;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n' || tmp[i] == '\r')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	if (line && ft_strncmp(line, "\xEF\xBB\xBF", 3) == 0)
	{
		clean = ft_strdup(line + 3);
		free(line);
		line = clean;
	}
	return (line);
}
