/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:40:43 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 14:47:36 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SUCCESS    1
# define FAILURE    0
# define WIDTH      1024
# define HEIGHT     768
# define TILE_SIZE  64
# define CT		 	2
# define ESC        53
# define W          13
# define S          1
# define A          0
# define D          2
# define LEFT       123
# define RIGHT      124
# define BLACK_WALL "xpm_files/black.xpm"
# define EMPTY_WALL "xpm_files/white.xpm"
# define ERROR_ARG "Error\nWrong number of arguments\n"
# define ERROR_EXT "Error\nWrong extension"
# define OPPEN_ERROR "Error\nCan't open file"
# define MLX_ERROR "Error\nmlx_init failed"
# define MLX_WIN_ERROR "Error\nmlx_new_window failed"
# define XPM_ERROR "Error\nmlx_xpm_file_to_image failed"
# define MAP_ERROR "Error\nInvalid map"
# define COLOR_ERROR "Error\nInvalid color"
# define MALLOC_ERROR "Error\nMalloc failed"
# include <unistd.h>
# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}			t_map;

typedef struct s_dir
{
	int	up;
	int	down;
	int	left;
	int	right;
}				t_dir;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	float	walk_dir;
	float	side_dir;
	float	turn_dir;
	double	angle;
	double	move_speed;
	double	rot_speed;
	double	fov;
	int		fetch;
	int		found_player;
	t_dir	*dir;
}			t_player;

typedef struct alloc
{
	bool	m_player;
	bool	m_dis;
	bool	m_is_spec;
	bool	m_t_angle;
	bool	m_wallx;
	bool	m_wally;
	bool	m_is_hor;
	bool	m_fd;
	bool	t_path;
	bool	n;
	bool	s;
	bool	e;
	bool	w;
}			t_alloc;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	char		**texture_path;
	double		hor_x_intercept;
	double		hor_y_intercept;
	double		ver_x_intercept;
	double		ver_y_intercept;
	double		*wallx;
	double		*wally;
	int			t_pix;
	int			b_pix;
	double		*dis;
	double		*is_spec;
	double		*t_angle;
	int			*is_hor;
	char		**map;
	char		*start_line;
	int			mapfd;
	int			off;
	int			xoff;
	int			yoff;
	int			mapcounter;
	int			floor;
	int			ceiling;
	t_alloc		*alloc_bool;
	t_texture	*nord;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
	t_player	*player;
	t_texture	*img_win;
}				t_game;

int				ft_strchr2(char *str, char *set);
double			normalize_angle(double angle);
void			put_pixel_to_img(t_game *game, int x, int y, int color);
void			turn_player(t_game *game);
void			load_textures(t_game *game);
size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putendl_fd(char *str, int fd);
char			*ft_strdup(const char *s1);
char			*ft_strrmv(char *str, char c);
t_game			*init_cub(int ac, char **av);
t_game			*get_map(t_game *game);
void			start_game(t_game *game);
int				render_game(t_game *game);
int				valid_input(int ac, char **av);
void			cast_all_rays(t_game *game);
void			events_hook(t_game *game);
void			draw_walls(t_game *game);
int				valid_format(t_game *game);
int				ft_atoi(const char *str);
void			auto_exit(t_game *game, char *error);
void			free_path(t_game *game);
void			mlx_free(t_game *game, char *error);
void			free_map(t_game *game);
void			game_free(t_game *game, char *error);
void			free_imgs(t_game *game);
void			free_list(t_map *map);
void			ft_error(char *error);
int				valid_file(char **av);
void			init_bool(t_game *game);
void			alloc_vars(t_game *game);
char			**get_texture_path(t_game *game);
int				direction(char *line, t_game *game);
void			get_color(char *line, t_game *game, int c);
int				skip(char *line);
int				check_edges(t_game *game);
int				check_valid_char(t_game *game);
double			angle_dir(char c);
int				check_open_spaces(t_game *game);
int				find_open_space(char c, int i, int j, t_game *game);
void			update_position(t_game *game);
t_dir			*get_dir(t_game *game, double angle);
int				is_down(t_game *game);
int				is_right(t_game *game);
int				_up(t_game *game);
int				_left(t_game *game);
void			spec_case(t_game *game, int ray);
double			phitagore(t_game *game, int x2, int y2);
int				inf_equal(double a, double b);
int				equal(double a, double b);
double			d_inf_equal(double a, double b, double r1, double r2);
int				is_nord(double angle);
int				is_east(double angle);
int				get_top_pixel(double wall_height);
int				get_bottom_pixel(double wall_height);
double			get_wall_height(t_game *game, int ray);
unsigned int	get_coloor(t_game *game, int x, int y, int ray);
int				limit(t_game *game);
int				check_colors(t_game *game);
int				limit(t_game *game);
int				is_digit(char c);
void			skip_spaces(char *line, int *i);
void			skip_digits(char *line, int *i, int *rgb);
void			init_data(t_game *game);
void			*alloc_img(void);
void			short_free(t_game *game, char *error);
int				check_path(t_game *game);
int				check_spaces(t_game *game);
int				wall_surrounded(t_game *game, int newx, int newy);
#endif