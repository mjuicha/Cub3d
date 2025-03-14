/***********************  includes  ***********************/
#ifndef CUB3D_H
# define CUB3D_H
/***********************  defines  ************************/
# define SUCCESS    1
# define FAILURE    0
/***********************  window  *************************/
# define WIDTH      1024
# define HEIGHT     768
# define TILE_SIZE  64
/***********************  keys  ***************************/
# define ESC        53
# define W          13
# define S          1
# define A          0
# define D          2
# define LEFT       123
# define RIGHT      124
/***********************  movement  ***********************/
# define FOV		60 * (M_PI / 180)
/***********************  colors  *************************/
# define BLACK      0x00000000
# define WHITE      0x00FFFFFF
# define GREY	  	0x00A9A9A9
# define RED	 	0x00FF0000
# define GREEN	 	0x0000FF00
# define BLUE	 	0x000000FF
# define YELLOW	 	0x00FFFF00
/***********************  XPM Files  **********************/
# define BLACK_WALL "xpm_files/black.xpm"
# define EMPTY_WALL "xpm_files/white.xpm"
/***********************  errors  *************************/
# define ERROR_ARG "\033[31mError: Wrong number of arguments\n\033[0m"
# define ERROR_EXT "\033[31mError: Wrong extension\n\033[0m"
# define OPPEN_ERROR "\033[31mError: Can't open file\n\033[0m"
# define MLX_ERROR "\033[31mError: mlx_init failed\n\033[0m"
# define MLX_WIN_ERROR "\033[31mError: mlx_new_window failed\n\033[0m"
# define XPM_ERROR "\033[31mError: mlx_xpm_file_to_image failed\n\033[0m"
# define MAP_ERROR "\033[31mError: Invalid map\n\033[0m"
# define COLOR_ERROR "\033[31mError: Invalid color\n\033[0m"
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
# include "get_next_line.h"
/***********************  structures  *********************/
typedef struct s_map
{
	char        *line;
	struct s_map *next;
	
}               t_map;

typedef struct s_dir
{
	int up;
	int down;
	int left;
	int right;
}               t_dir;

typedef struct s_texture
{
	void    *img;
	char	*addr;
	int     bpp;
	int     line_length;
	int     *endian;
}			   t_texture;

typedef struct s_player // nadi
{
	double 	pos_x;
	double	pos_y;
	float	walk_dir;
	float	side_dir;
	float	turn_dir;
	double  angle;
	double  move_speed;
	double  rot_speed;
	int		fetch;
	t_dir   *dir;
}            t_player;

typedef struct s_game
{
	void    *mlx;
	void    *mlx_win;
	t_texture *img_win;
	
	int     width;
	int     height;

	char	**texture_path;
	
///	///////////////
	double  hx;
	double  hy;
///	///////////////
	double  vx;
	double  vy;
///////////////////
	double 	*wallx;
	double 	*wally;
///////////////////
	int		t_pix;
	int		b_pix;
	///////////////////
	double 	*dis;
	double  *is_spec;
	double  *t_angle;
	int 	*is_hor;
	///////////////////
	char    **map;
	char	**cp_map;
	char    *start_line;
	int     mapfd;
	int off;
	int		mapcounter;
	int 	floor;
	int 	ceiling;
	t_texture *nord;
	t_texture *south;
	t_texture *east;
	t_texture *west;
	t_player *player;
}               t_game;

/***********************  prototypes  ***********************/
int	ft_strchr2(char *str, char *set);
double	normalize_angle(double angle);
void    put_pixel_to_img(t_game *game, int x, int y, int color);
void	turn_player(t_game *game);
void	load_textures(t_game *game);
/***********************  utils  ***********************/
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *str, int fd);
char	*ft_strdup(const char *s1);
char	*ft_strrmv(char *str, char c);
/***********************  init  ***********************/
t_game  *init_cub(int ac, char **av);
t_game  *get_map(t_game *game);
void    start_game(t_game *game);
int    	render_game(t_game *game);
int 	valid_input(int ac, char **av);
void	fov(t_game *game);
void	events_hook(t_game *game);
void    draw_walls(t_game *game);
int	valid_format(t_game *game);
int	white_space(char c);
int	ft_atoi(const char *str);
/***********************  draw  ***********************/
#endif