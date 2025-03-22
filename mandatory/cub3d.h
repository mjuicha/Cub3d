/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:40:43 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 12:32:40 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/***********************  defines  ************************/

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

/***********************  colors  *************************/

# define BLACK      0x00000000
# define WHITE      0x00FFFFFF
# define GREY	  	0x00A9A9A9
# define RED	 	0x00FF0000
# define GREEN	 	0x0000FF00
# define BLUE	 	0x000000FF
# define YELLOW	 	0x00FFFF00

/***********************  errors  *************************/

# define ERROR_ARG "\033[31mError: Wrong number of arguments\033[0m"
# define ERROR_EXT "\033[31mError: Wrong extension\033[0m"
# define OPPEN_ERROR "\033[31mError: Can't open file\033[0m"
# define MLX_ERROR "\033[31mError: mlx_init failed\033[0m"
# define MLX_WIN_ERROR "\033[31mError: mlx_new_window failed\033[0m"
# define XPM_ERROR "\033[31mError: mlx_xpm_file_to_image failed\033[0m"
# define MAP_ERROR "\033[31mError: Invalid map\033[0m"
# define COLOR_ERROR "\033[31mError: Invalid color\033[0m"
# define MALLOC_ERROR "\033[31mError: Malloc failed\033[0m"

/***********************  includes  ***********************/

# include <unistd.h>
# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

/***********************  structures  *********************/

typedef struct s_file_cont
{
	char				*line;
	struct s_file_cont	*next;
}				t_file_cont;

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
	int		pos_x;
	int		pos_y;
	int		walk_dir;
	int		side_dir;
	int		turn_dir;
	double	angle;
	double	move_speed;
	double	rot_speed;
	double	fov;
	int		found_player;
	t_dir	*dir;
}			t_player;

typedef struct alloc
{
	bool	m_player;
	bool	m_dir;
	bool	m_dis;
	bool	m_is_spec;
	bool	m_t_angle;
	bool	m_wallx;
	bool	m_wally;
	bool	m_is_hor;
	bool	m_fd;
	bool	n;
	bool	s;
	bool	e;
	bool	w;
}			t_alloc;

typedef struct s_game_data
{
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	char		**texture_path;
	double		hx;
	double		hy;
	double		vx;
	double		vy;
	double		*wallx;
	double		*wally;
	int			t_pix;
	int			b_pix;
	double		*dis;
	double		*is_spec;
	double		*t_angle;
	int			*is_hor;
	char		**map;
	char		**cp_map;
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
}				t_game_data;

/***********************  utils  ***********************/

size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putendl_fd(char *str, int fd);
char			*ft_strdup(const char *s1);
char			*ft_strrmv(char *str, char c);
int				ft_strchr2(char *str, char *set);
int				ft_atoi(const char *str);
int				is_digit(char c);

/***********************  prototypes  ***********************/

t_game_data		*init_cub(int ac, char **av);
t_game_data		*get_map(t_game_data *game);
void			start_game(t_game_data *game);
int				render_game(t_game_data *game);
int				valid_input(int ac, char **av);
void			cast_all_rays(t_game_data *game);
void			events_hook(t_game_data *game);
void			draw_walls(t_game_data *game);
int				valid_format(t_game_data *game);
void			auto_exit(t_game_data *game, char *error);
void			free_path(t_game_data *game);
void			mlx_free(t_game_data *game, char *error);
void			free_map(t_game_data *game);
void			game_free(t_game_data *game, char *error);
void			free_imgs(t_game_data *game);
void			free_list(t_file_cont *map);
void			ft_error(char *error);
int				valid_file(char **av);
void			init_bool(t_game_data *game);
void			alloc_vars(t_game_data *game);
char			**get_texture_path(t_game_data *game);
int				wall_txt_direction(char *line, t_game_data *game);
void			get_color(char *line, t_game_data *game, int c);
int				skip(char *line);
int				check_edges(t_game_data *game);
int				check_valid_char(t_game_data *game);
double			get_angle_dir(char c);
int				check_open_spaces(t_game_data *game);
int				find_open_space(char c, int i, int j, t_game_data *game);
void			update_position(t_game_data *game);
void			get_ray_dir(t_game_data *game, double angle);
int				is_down(t_game_data *game);
int				is_right(t_game_data *game);
int				is_up(t_game_data *game);
int				is_left(t_game_data *game);
void			spec_case(t_game_data *game, int ray);
double			phitagore(t_game_data *game, int x2, int y2);
int				inf_equal(double a, double b);
int				equal(double a, double b);
double			d_inf_equal(double a, double b, double r1, double r2);
int				is_nord(double angle);
int				is_east(double angle);
int				get_top_pixel(double wall_height);
int				get_bottom_pixel(double wall_height);
double			get_wall_height(t_game_data *game, int ray);
unsigned int	get_coloor(t_game_data *game, int x, int y, int ray);
int				limit(t_game_data *game);
int				check_colors(t_game_data *game);
int				limit(t_game_data *game);
void			skip_spaces(char *line, int *i);
void			skip_digits(char *line, int *i, int *rgb);
double			normalize_angle(double angle);
void			put_pixel_to_img(t_game_data *game, int x, int y, int color);
void			turn_player(t_game_data *game);
void			load_textures(t_game_data *game);

/***********************  GET_NEXT_LINE  ***********************/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char			*get_next_line(int fd);
char			*empty_str(void);
char			*ft_strchr(const char *str, int c);
char			*ft_strjoin(char *str, char *buff);
char			*the_line(char *str);
char			*next_line(char *str);
char			*read_line(int fd, char *str);

#endif