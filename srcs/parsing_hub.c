/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:34:53 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/02 09:05:38 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void	ft_check_line_is_empty(t_data *data, char *line, int fd)
{
	if (*line != 0 && !ft_strstr(line, "NO ") && !ft_strstr(line, "SO ")
		&& !ft_strstr(line, "WE ") && !ft_strstr(line, "EA ")
		&& !ft_strstr(line, "R ") && !ft_strstr(line, "C ")
		&& !ft_strstr(line, "F ") && !ft_strstr(line, "S "))
		ft_parsing_error("Error\nEither :\n\
		1/ lines between inputs are not empty\n\
		2/ or there is no space between a keycode input and its values\n\
		3/ or an input is missing", data, fd);
}

void	ft_parse_values_before_map(t_data *data, char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (data->p.step < 8 && line[i] == 'R')
			ft_parse_res(data, line, fd);
		else if (data->p.step < 8 && line[i] == 'N' && line[i + 1] == 'O')
			ft_parse_and_get_texpath(data, line, fd, 'N');
		else if (data->p.step < 8 && line[i] == 'S' && line[i + 1] == 'O')
			ft_parse_and_get_texpath(data, line, fd, 'S');
		else if (data->p.step < 8 && line[i] == 'W' && line[i + 1] == 'E')
			ft_parse_and_get_texpath(data, line, fd, 'W');
		else if (data->p.step < 8 && line[i] == 'E' && line[i + 1] == 'A')
			ft_parse_and_get_texpath(data, line, fd, 'E');
		else if (data->p.step < 8 && line[i] == 'S' && line[i + 1] == ' ')
			ft_parse_and_get_texpath(data, line, fd, 's');
		else if (data->p.step < 8 && line[i] == 'F')
			ft_parse_floor_and_ceiling(data, line, fd, 'F');
		else if (data->p.step < 8 && line[i] == 'C')
			ft_parse_floor_and_ceiling(data, line, fd, 'C');
		else if (data->p.step < 8)
			ft_check_line_is_empty(data, line, fd);
		i++;
	}
}

void	ft_check_empty_lines_before_map(t_data *data, char *line, int fd)
{
	if (*line == '\0')
		return ;
	else if (data->p.step == 8 && (ft_strstr(line, "NO")
			|| ft_strstr(line, "SO") || ft_strstr(line, "WE")
			|| ft_strstr(line, "EA") || ft_strstr(line, "R")
			|| ft_strstr(line, "C") || ft_strstr(line, "F")
			|| ft_strstr(line, "S")))
	{
		data->p.step = 9;
		return ;
	}
	if (ft_strstr(line, "1"))
	{
		data->p.step = 10;
		return ;
	}
	else if ((data->p.step == 9 && !ft_strstr(line, "1"))
		|| !ft_strstr(line, " "))
		ft_parsing_error("Error\nLines before map are not empty", data, fd);
}
/*
// A retirer
void	ft_print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
}*/

void	ft_end_file_read(t_data *data, int fd)
{
	if (data->mapx == -1 || data->mapy == -1)
		ft_parsing_error("Error\nPlayer position is missing", data, fd);
	if (data->p.step == 10)
	{
		ft_free_line_before_next(data);
		close(fd);
	}
	else
		ft_parsing_error("Error\nHey the map is missing!", data, fd);
}

void	ft_parse_cub_file(t_data *data, int fd)
{
	char	*line;
	t_list	*list;

	list = NULL;
	data->p.lstptr = &list;
	while (ft_gnl(fd, &line, data) > 0)
	{
		data->p.lptr = &line;
		if (data->p.step < 8)
			ft_parse_values_before_map(data, line, fd);
		if (data->p.step == 8 || data->p.step == 9)
			ft_check_empty_lines_before_map(data, line, fd);
		if (data->p.step == 10)
		{
			if (!ft_check_spaces_in_map(line))
				ft_parsing_error("Error\nInvalid input in map lines", data, fd);
			ft_parse_map(data, line, fd);
			ft_link_line(&list, line, data, fd);
		}
		ft_free_line_before_next(data);
	}
	ft_end_file_read(data, fd);
	ft_transform_to_tab(list, data);
	ft_floodfill(data, 48, 55);
	ft_start_raycasting(data);
	// DEBUG
//	printf("mapw%d\n", data->p.mapw);
//	printf("maph%d\n", data->p.maph);
//	printf("mapx%d\n", data->mapx);
//	printf("mapy%d\n", data->mapy);
//	ft_print_list(list);
//	int z = 0;
//	while (data->map[z] && z < data->p.maph + 2)
//	{
//		printf("%s\n", data->map[z]);
//		z++;
//	}
//	ft_map_error("OK", data);
}
