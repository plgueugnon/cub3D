/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:56:09 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/01 12:46:20 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

int			ft_capture_pos(t_data *data, char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'S' && line[i + 1] == 'O')
			return (i + 2);
		if (line[i] == 'E' && line[i + 1] == 'A')
			return (i + 2);
		if (line[i] == 'W' && line[i + 1] == 'E')
			return (i + 2);
		if (line[i] == 'N' && line[i + 1] == 'O')
			return (i + 2);
		if (line[i] == 'S' && line[i + 1] == ' ')
			return (i + 1);
		if ((line[i] == 'F' && line[i + 1] == ' ') || (line[i] == 'C'
					&& line[i + 1] == ' '))
			return (i + 1);
		if (line[i] == ' ')
			i++;
		else
			break ;
	}
	ft_parsing_error("Error\nInvalid texture or color input", data, fd);
	return (0);
}

static void	ft_get_texpath(t_data *data, char *line, int i, int flag)
{
	if (flag == 'N')
		data->p.no_tex_path = ft_strdup(line + i + 1);
	if (flag == 'S')
		data->p.so_tex_path = ft_strdup(line + i + 1);
	if (flag == 'W')
		data->p.we_tex_path = ft_strdup(line + i + 1);
	if (flag == 'E')
		data->p.ea_tex_path = ft_strdup(line + i + 1);
	if (flag == 's')
		data->p.sp_tex_path = ft_strdup(line + i + 1);
}

static void	ft_test_path_validity(t_data *data, int flag, int fd)
{
	int	testfd;

	testfd = 0;
	if (flag == 'N')
		testfd = open(data->p.no_tex_path, O_RDONLY);
	if (flag == 'S')
		testfd = open(data->p.so_tex_path, O_RDONLY);
	if (flag == 'E')
		testfd = open(data->p.ea_tex_path, O_RDONLY);
	if (flag == 'W')
		testfd = open(data->p.we_tex_path, O_RDONLY);
	if (flag == 's')
		testfd = open(data->p.sp_tex_path, O_RDONLY);
	if (testfd < 0)
		ft_parsing_error("Error\nTexture path is invalid", data, fd);
	else
		close(testfd);
	data->p.step++;
}

static void	ft_check_if_xpm_file(t_data *data, char *line, int fd)
{
	int	i;

	i = ft_strlen(line);
	if (line[i - 1] != 'm' && line[i - 2] != 'p' && line[i - 3] != 'x')
		ft_parsing_error("Error\nEither :\n\
		1/ texture file is not an xpm file\n\
		2/ or there are characters left after path passed as input", data, fd);
}

void		ft_parse_and_get_texpath(t_data *data, char *line, int fd, int flag)
{
	int	i;
	int	c;

	c = 0;
	i = ft_capture_pos(data, line, fd);
	while (line[i] && line[i] == ' ')
	{
		if ((line[i] == ' ' && line[i + 1] == '.' && line[i + 2] == '/')
			|| (line[i] == ' ' && line[i + 1] == '.' && line[i + 2] == '.'
					&& line[i + 3] == '/'))
		{
			ft_get_texpath(data, line, i, flag);
			c = 1;
		}
		i++;
	}
	if (!c)
		ft_parsing_error("Error\nInvalid texture input, either :\n\
			1/ there is no space between keycode input and path\n\
			2/ or there are invalid char before path beginning", data, fd);
	ft_check_if_xpm_file(data, line, fd);
	ft_test_path_validity(data, flag, fd);
}
