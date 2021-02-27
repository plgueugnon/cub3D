/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ceiling_and_floor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:04:48 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/23 20:00:42 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void	ft_check_spaces_between_values(t_data *data, char *line, int fd)
{
	int j;

	j = ft_capture_pos(data, line, fd);
	while (line[j])
	{
		if (line[j] != ',' && line[j] != ' ' && !ft_isdigit(line[j]))
			ft_parsing_error("Error\nInvalid ceiling & floor input", data, fd);
		j++;
	}
}

static void	ft_basic_color_validity_check(char *line, t_data *data, int fd)
{
	int j;
	int n;
	int r;

	j = ft_capture_pos(data, line, fd);
	n = 0;
	r = 0;
	while (line[j])
	{
		if (line[j] == ',')
			n++;
		if (ft_isdigit(line[j]))
		{
			if ((n == 1 && r == 0) || (n == 2 && r == 1))
				ft_parsing_error("Error\nMisplaced or missing comma", data, fd);
			r++;
			if ((n == 0 && r == 2) || (n == 1 && r == 3))
				ft_parsing_error("Error\nMisplaced or missing comma", data, fd);
			j += ft_numlen(atoi(&line[j])) - 1;

		}
		j++;
	}
	if (n != 2 || r != 3)
		ft_parsing_error("Error\nInvalid comma(s) or missing values", data, fd);
}

static void	ft_create_color(t_data *data, int *tab, int flag, int fd)
{
	if (flag == 'F')
	{
		if ((signed)data->p.floor != -1)
			ft_parsing_error("Error\nF keycode already treated", data, fd);
		data->p.floor = (255 << 24 | tab[0] << 16 | tab[1] << 8 | tab[2]);
	}
	else
	{
		if ((signed)data->p.ceiling != -1)
			ft_parsing_error("Error\nC keycode already treated", data, fd);
		data->p.ceiling = (255 << 24 | tab[0] << 16 | tab[1] << 8 | tab[2]);
	}
	data->p.step++;
}

void	ft_parse_floor_and_ceiling(t_data *data, char *line, int fd, int flag)
{
	int tab[3];
	int l;
	int i;

	l = 0;
	i = 0;
	ft_check_spaces_between_values(data, line, fd);
	ft_basic_color_validity_check(line, data, fd);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			if (l > 2)
				ft_parsing_error("Error\nToo many numbers in input", data, fd);
			if (l == 0 || l == 1 || l == 2)
				tab[l] = ft_atoi(&line[i]);
			if (tab[l] < 0 || tab[l] > 255)
				ft_parsing_error("Error\nInvalid color input", data, fd);
			i += ft_numlen(tab[l] - 1);
			l++;
		}
		if ((unsigned long)i < ft_strlen(line))
			i++;
	}
	ft_create_color(data, (&tab)[3], flag, fd);
}
