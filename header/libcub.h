/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:55:47 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/06 10:48:20 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCUB_H
# define LIBCUB_H

# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifdef __APPLE__
#  define FORWARD 13
#  define BACKWARD 1
#  define RIGHT 2
#  define LEFT 0x0
#  define ROTATELEFT 123
#  define ROTATERIGHT 124
#  define ESC 53
#  define CROSSEXIT 17
#  define APPLE 1
#  define LINUX 0
# endif

# ifdef __linux__
#  define FORWARD 122
#  define BACKWARD 115
#  define RIGHT 100
#  define LEFT 113
#  define ROTATELEFT 65361
#  define ROTATERIGHT 65363
#  define ESC 65307
#  define CROSSEXIT 33
#  define APPLE 0
#  define LINUX 1
# endif

typedef struct	s_node
{
	int		x;
	int		y;
	void	*next;
}				t_node;

typedef struct	s_queue
{
	int		count;
	t_node	*front;
	t_node	*rear;
}				t_queue;

typedef struct	s_texdata
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}				t_texdata;

typedef struct	s_textures
{
	int		texdir;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
}				t_textures;

typedef struct	s_sprite_pos
{
	double	x;
	double	y;
}				t_sprite_pos;

typedef struct	s_spritedata
{
	int		nb;
	double	*zbuffer;
	int		*order;
	double	*dist;
	double	invdet;
	double	transformy;
	double	transformx;
	double	spritex;
	double	spritey;
	int		screenx;
	int		h;
	int		w;
	int		drawstarty;
	int		drawstartx;
	int		drawendy;
	int		drawendx;
}				t_spritedata;

typedef struct	s_move {
	int		forward;
	int		backward;
	int		strafeleft;
	int		straferight;
	int		rotateleft;
	int		rotateright;
}				t_move;

typedef struct	s_parse
{
	int				res[2];
	char			*no_tex_path;
	char			*so_tex_path;
	char			*we_tex_path;
	char			*ea_tex_path;
	char			*sp_tex_path;
	unsigned int	floor;
	unsigned int	ceiling;
	int				step;
	int				mapw;
	int				maph;
	t_list			**lstptr;
	char			**lptr;
	int				iszero[2];
	char			**gnlptr;
}				t_parse;

typedef struct	s_img
{
	void	*img;
	void	*img_2;
	char	*addr;
	char	*addr_2;
	int		bpp;
	int		line_size;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}				t_img;

typedef struct	s_data
{
	int				x;
	int				y;
	int				h;
	int				w;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			rayposx;
	double			rayposy;
	double			camerax;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineh;
	int				drawstart;
	int				drawend;
	char			**map;
	double			movspeed;
	double			rotspeed;
	int				save;
	t_texdata		texdata[5];
	t_textures		t;
	t_sprite_pos	*spos;
	t_spritedata	s;
	t_move			m;
	t_parse			p;
	t_img			i;
}				t_data;

void			ft_parsing_error(char *err, t_data *data, int fd);
void			ft_map_error(char *err, t_data *data);
void			ft_del(void *content);
void			ft_free_map(t_data *data);
void			ft_free_tex_path(t_data *data);
int				ft_gnl(int fd, char **line, t_data *data);
void			ft_clear_still_reachable(t_data *data);
void			ft_init_parsing_values(t_data *data);
void			ft_get_player_dir(char c, t_data *data);
void			ft_init_raycast_values(t_data *data);
void			ft_init_raycast_pointers(t_data *data);
int				main(int argc, char **argv);
void			ft_start_parsing(t_data *data, char *mappath);
void			ft_parse_floor_and_ceiling(t_data *data, char *line, int fd,
					int flag);
void			ft_parse_res(t_data *data, char *line, int fd);
int				ft_capture_pos(t_data *data, char *line, int fd);
void			ft_parse_and_get_texpath(t_data *data, char *line, int fd,
					int flag);
void			ft_parse_cub_file(t_data *data, int fd);
void			ft_parse_values_before_map(t_data *data, char *line, int fd);
void			ft_check_empty_lines_before_map(t_data *data, char *line,
					int fd);
void			ft_end_file_read(t_data *data, int fd);
int				ft_check_charset(char src, char *charset);
int				ft_check_spaces_in_map(char *line);
void			ft_parse_map(t_data *data, char *line, int fd);
void			ft_free_line_before_next(t_data *data);
void			ft_link_line(t_list **list, void *content, t_data *data,
					int fd);
void			ft_initialise_queue(t_queue *q);
int				ft_queue_is_empty(t_queue *q);
void			ft_add_to_queue(t_queue *q, int y, int x, t_data *data);
void			ft_remove_from_queue(t_queue *q);
void			ft_floodfill(t_data *data, int oval, int rval);
void			ft_cleanup_queue(t_queue *q);
void			ft_transform_to_tab(t_list *list, t_data *data);
void			ft_init_ray_starting_point(t_data *data);
void			ft_dda_compute(t_data *data);
void			ft_sidedist_compute(t_data *data);
void			ft_draw_col(t_data *data);
void			ft_draw_ceiling_and_floor(t_data *data);
void			ft_custom_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_init_texdir(t_data *data);
void			ft_texel_compute(t_data *data);
void			ft_start_raycasting(t_data *data);
int				ft_loop(t_data *data);
void			ft_buffer_img(t_data *data);
void			ft_init_textures(t_data *data);
void			ft_init_sprites(t_data *data);
void			ft_sort_sprites(t_data *data);
void			ft_draw_sprite(t_data *data);
void			ft_sprite_compute(t_data *data);
void			ft_exit(char *err, t_data *data);
int				ft_key_press(int key, t_data *data);
int				ft_key_release(int key, t_data *data);
int				ft_mouse_exit(t_data *data);
void			ft_forward_or_backward(t_data *data);
void			ft_strafe_left_or_right(t_data *data);
void			ft_rotate_right(t_data *data);
void			ft_rotate_left(t_data *data);
void			ft_save(t_data *data);

#endif
