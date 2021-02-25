/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:48:44 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/25 22:27:02 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void ft_basic_res_validity_check(char *line, t_data *data, int fd)
{
	int j;

	j = 0;
	while (line[j])
	{
		if (line[j] != 'R' && line[j] != ' ' && !ft_isdigit(line[j]))
			ft_parsing_error("Error\nInvalid resolution input", data, fd);
		j++;
	}
}

void ft_parse_res(t_data *data, char *line, int fd)
{
	int l;
	int i;

	l = 0;
	i = 0;
	ft_basic_res_validity_check(line, data, fd);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			if (l > 1)
				ft_parsing_error("Error\nInvalid resolution input", data, fd);
			if (l == 0 || l == 1)
				data->p.res[l] = ft_atoi(&line[i]);
			i += ft_numlen(data->p.res[l] - 1);
			l++;
		}
		if (line[i])
			i++;
	}
	if (data->p.res[0] < 0 || data->p.res[1] < 0)
		ft_parsing_error("Error\nMissing resolution value", data, fd);
	data->p.step++;
}
