/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:25:20 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/05 19:19:55 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void	ft_start_parsing(t_data *data, char *mappath)
{
	int	fd;
	int	i;

	i = ft_strlen(mappath);
	if (mappath[i - 1] != 'b' || mappath[i - 2] != 'u' || mappath[i - 3] != 'c'
	|| mappath[i - 4] != '.')
	{
		printf("Error\nFirst argument is not a .cub file\n");
		exit(0);
	}
	fd = open(mappath, O_DIRECTORY);
	if (fd != -1)
	{
		printf("Error\nFirst argument is a directory\n");
		close(fd);
		exit(0);
	}
	fd = open(mappath, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nInvalid path or file for .cub file\n");
		exit(0);
	}
	ft_init_parsing_values(data);
	ft_parse_cub_file(data, fd);
}

int		main(int argc, char **argv)
{
	t_data	data;

	data.save = 0;
	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7) != 0)
			{
				printf("Error\nSecond argument is invalid\n");
				return (0);
			}
			else
			{
				data.save = 1;
				ft_start_parsing(&data, argv[1]);
			}
		}
		else
			ft_start_parsing(&data, argv[1]);
	}
	printf("Error\nInvalid number of argument\n");
	return (0);
}
