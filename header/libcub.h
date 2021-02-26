/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:55:47 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/26 15:59:26 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCUB_H
# define LIBCUB_H

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_node {
	int x;
	int y;
	void *next;
}				t_node;

typedef struct s_queue {
	int count;
	t_node *front;
	t_node *rear;
}				t_queue;

typedef struct s_texdata {
	void	*img; 
	char	*addr; 
	int		bpp; 
	int		line_size; 
	int		endian; 
	int		width;
	int		height;
} t_texdata;

typedef struct s_textures {
	int		texdir;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
}				t_textures;

typedef struct s_sprite_pos {
	double x;
	double y;
}				t_sprite_pos;

typedef struct s_spritedata {
	int nb;
	double *zbuffer;
	int *order;
	double *dist;
	double invdet;
	double transformy;
	double transformx;
	double spritex;
	double spritey;
	int screenx;
	int h;
	int w;
	int drawstarty;
	int drawstartx;
	int drawendy;
	int drawendx;
}				t_spritedata;

typedef struct	s_move {
	int		ta; // mouvement -> a renommer pour que + explicite
	int		ts;
	int		tw;
	int		td;
	int		rl;
	int		rr;
}				t_move;

typedef struct s_parse {
	int res[2];
	char *no_tex_path;
	char *so_tex_path;
	char *we_tex_path;
	char *ea_tex_path;
	char *sp_tex_path;
	unsigned int	floor;
	unsigned int ceiling;
	int step;
	int mapw;
	int maph;
	t_list **lstptr;
	char **lptr;
	int	iszero[2];
	char **gnlptr;
}			t_parse;

typedef struct s_img {
	void	*img;
	void	*img_2;
	char	*addr;
	char	*addr_2;
	int		bpp;
	int		llength;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}				t_img;

typedef struct	s_data {
	int		x; // va etre utiliser pour parcourir tous les rayons
	int		y;
	int		h; //
	int		w; //
	double	posx; // pos x joueur
	double	posy; // pos y joueur
	double	dirx; // vecteur de direction x
	double	diry; // vecteur de direction y
	double	planx; // vecteur du plan x
	double	plany; // vecteur du plan y
	double	raydirx; // calcul de direction x du rayon
	double	raydiry; // calcul de direction y du rayon
	double	rayposx; // point de depart du rayon x
	double	rayposy; // point de depart du rayon y
	double	camerax; // point x sur le plan camera
	int		mapx; // pos x du carre ou se trouve le joueur
	int		mapy; // pos y du carre ou se trouve le joueur
	double	sidedistx; // distance rayon - premiere intersection verticale = 1 cote de x
	double	sidedisty; // distance rayon - premiere intersection horizontale = 1 cote de y
	double	deltadistx; // distance entre toutes les intersections verticales
	double	deltadisty; // distance entre toutes les intersections horizontales
	double	perpwalldist; // distance joueur - mur
	int		stepx; // changement de case dans la direction x
	int		stepy; // changement de case dans la direction y
	int		hit; // est ce que mur rencontre ou non 
	int		side; // quelle orientation a le mur (N/S ou E/O) dans la map / quel cote x ou y du mur est touche
	int		lineh; // hauteur de la ligne a dessiner
	int		drawstart; // position de debut ou il faut dessiner la colonne
	int		drawend; // position de fin ou il faut dessiner la colonne
	char	**map;
	double		movspeed;
	double		rotspeed;
	int		save;
	t_texdata		texdata[5];
	t_textures		t;
	t_sprite_pos	*spos;
	t_spritedata	s;
	t_move			m;
	t_parse			p;
	t_img			i;
}			t_data;

// ERROR
void	ft_parsing_error(char *err, t_data *data, int fd);
void	ft_map_error(char *err, t_data *data);
void	ft_del(void *content);
void	ft_free_map(t_data *data);
int		ft_gnl(int fd, char **line, t_data *data);

// INIT
void	ft_init_parsing_values(t_data *data);

// MAIN
int		main(int argc, char **argv);
void	ft_start_parsing(t_data *data, char *mappath);

// CEILING AND FLOOR PARSE
void	ft_parse_floor_and_ceiling(t_data *data, char *line, int fd, int flag);

// RES PARSE
void	ft_parse_res(t_data *data, char *line, int fd);

// PARSE TEX
int 	ft_capture_pos(t_data *data, char *line, int fd);
void	ft_parse_and_get_texpath(t_data *data, char *line, int fd, int flag);

// PARSE HUB
void	ft_parse_cub_file(t_data *data, int fd);
void	ft_parse_values_before_map(t_data *data, char *line, int fd);
void	ft_check_empty_lines_before_map(t_data *data, char *line, int fd);
void	ft_end_file_read(t_data *data, int fd);

// PARSE MAP
int		ft_check_charset(char src, char *charset);
int		ft_check_spaces_in_map(char *line);
void	ft_parse_map(t_data *data, char *line, int fd);
void	ft_free_line_before_next(t_data *data);
void	ft_link_line(t_list **list, void *content, t_data *data, int fd);

// QUEUE MANAGEMENT
void	ft_initialise_queue(t_queue *q);
int		ft_queue_is_empty(t_queue *q);
void	ft_add_to_queue(t_queue *q, int y, int x, t_data *data);
void	ft_remove_from_queue(t_queue *q);

//FLOODFILL
void	ft_floodfill(t_data *data, int oval, int rval);

// CREATE MAP
void	ft_transform_to_tab(t_list *list, t_data *data);

// A VOIR APRES PARSING
int	ft_key_press(int key, t_data *data);
int	ft_key_release(int key, t_data *data);
int	ft_mouse_exit(t_data *data);
int	ft_loop(t_data *data);
void	ft_init_pos(t_data *data);
void	ft_DDA_compute(t_data *data);
void	ft_sidedist_compute(t_data *data);
void	ft_draw_col(t_data *data);
void	ft_draw_ceiling_and_floor(t_data *data);
void	ft_custom_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_fwd_or_bckwd(t_data *data);
void	ft_strafe_left_or_right(t_data *data);
void	ft_rotate_right(t_data *data);
void	ft_rotate_left(t_data *data);
void	ft_buffer_img(t_data *data);
int		ft_init_tex(t_data *data);
void	ft_get_tex_adress(t_data *data);
void	ft_init_texdir(t_data *data);
void	ft_init_sprite(t_data *data);
void	ft_draw_sprite(t_data *data);
void	ft_sort_sprites(t_data *data);
void	ft_sprite_compute(t_data *data);

#endif
