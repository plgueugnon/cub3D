/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:02:02 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/05 12:55:17 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void	ft_create_bmp_header(t_data *data, int fd)
{
	int o;

	write(fd, "BM", 2); // code de signature BMP
	o = 14 + 40 + 4 * data->w * data->h; // 14 = info du file header + 40 pour le stockage des infos relatives au fichier bitmap (le DIB) + la taille totale du fichier stockee sur 4 octets
	write(fd, &o, 4);
	o = 0;
	write(fd, &o, 2);
	write(fd, &o, 2);
	o = 54;
	write(fd, &o, 4);
	o = 40;
	write(fd, &o, 4);
	write(fd, &data->w, 4);
	write(fd, &data->h, 4);
	o = 1;
	write(fd, &o, 2);
	write(fd, &data->i.bpp, 2);
	o = 0;
	write(fd, &o, 4);
	write(fd, &o, 4);
	write(fd, &o, 4);
	write(fd, &o, 4);
	write(fd, &o, 4);
	write(fd, &o, 4);
}

void	ft_save(t_data *data)
{
	int fd;
	int x;
	int y;
	int *addr_int;

	addr_int = (int *)data->i.addr;
	fd = open("./save.bmp", O_CREAT | O_WRONLY, 0666);
	if (fd < 0)
		ft_exit("Error\nFailure to create a save file", data);
	ft_create_bmp_header(data, fd);
	y = data->h;
	while (y > 0)
	{
		x = 0;
		while (x < data->w)
		{
			write(fd, &addr_int[y * data->i.line_size / (data->i.bpp / 8) + x], 4);
			x++;
		}
		y--;
	}

	close(fd);
	ft_exit("Save file created", data);
}
