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
# define SPACE      49
# define M          46
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
# define SKY_BLUE	0x0080DFFF
# define FLOOR		0x00B6855B
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

typedef struct s_door_pos
{
	int x;
	int y;
	int valid;
}               t_door_pos;

typedef struct s_dir
{
	int up;
	int down;
	int left;
	int right;
}               t_dir;
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
	void    *img;
	
	int     width;
	int     height;

	void	*brown;
	void	*green;
	void	*red;
	void	*blue;

	void	*black_wall;
	void	*blue_wall;
	void	*red_wall;
	void	*grey_wall;
	void	*door;
	void	*sky;
	void	*sprite;
	void	*sprite1;
	void	*sprite2;
	void	*sprite3;
	void	*sprite4;
	void	*sprite5;
	void	*sprite6;
	void	*warning;
	void	*aim;
	void	*gun;
	void	*circle;

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
	int 	bpp00;
	int 	line_length00;
	int 	*endian00;
	char    *addr00;
///////////////////
	int 	bppm1;
	int 	line_lengthm1;
	int 	*endianm1;
	char    *addrm1;
///////////////////
	int 	bppm2;
	int 	line_lengthm2;
	int 	*endianm2;
	char    *addrm2;
///////////////////
	int 	bppm3;
	int 	line_lengthm3;
	int 	*endianm3;
	char    *addrm3;
///////////////////
	int 	bpp01;
	int 	line_length01;
	int 	*endian01;
	char    *addr01;
///////////////////
	int 	bpp02;
	int 	line_length02;
	int 	*endian02;
	char    *addr02;
///////////////////
	int 	bpp03;
	int 	line_length03;
	int 	*endian03;
	char    *addr03;
///////////////////
	int 	bpp04;
	int 	line_length04;
	int 	*endian04;
	char    *addr04;
///////////////////
	int 	bpp05;
	int 	line_length05;
	int 	*endian05;
	char    *addr05;
///////////////////
	int 	bpp06;
	int 	line_length06;
	int 	*endian06;
	char    *addr06;
///////////////////
	int 	bpp07;
	int 	line_length07;
	int 	*endian07;
	char    *addr07;
///////////////////
	int 	bpp08;
	int 	line_length08;
	int 	*endian08;
	char    *addr08;
///////////////////
	int 	bpp09;
	int 	line_length09;
	int 	*endian09;
	char    *addr09;
///////////////////
	int 	bpp;
	int 	line_length;
	int 	*endian;
	char    *addr;
///////////////////
	int 	bpp1;
	int 	line_length1;
	int 	*endian1;
	char    *addr1;
	///////////////////
	int 	bpp2;
	int 	line_length2;
	int 	*endian2;
	char    *addr2;
	///////////////////
	int 	bpp3;
	int 	line_length3;
	int 	*endian3;
	char    *addr3;
	///////////////////
	int 	bpp4;
	int 	line_length4;
	int 	*endian4;
	char    *addr4;
	///////////////////
	int 	bpp5;
	int 	line_length5;
	int 	*endian5;
	char    *addr5;
	///////////////////
	int 	bpp6;
	int 	line_length6;
	int 	*endian6;
	char    *addr6;
	///////////////////
	int		t_pix;
	int		b_pix;
	///////////////////
	double 	*dis;
	double  *is_spec;
	double  *t_angle;
	int 	*is_door;
	int 	*is_hor;
	///////////////////
	char    **map;
	char    *start_line;
	int     mapfd;
	int off;
	int 	mouse_ready;
	int	 	old_mouse_x;
	int	 	mapcounter;
	t_door_pos *door_pos;
	t_player *player;
	int set;
	int floor;
	int ceiling;
}               t_game;

/***********************  prototypes  ***********************/
int	ft_strchr2(char *str, char *set);
double	normalize_angle(double angle);
void    put_pixel_to_img(t_game *game, int x, int y, int color);
void	turn_player(t_game *game);
int	white_space(char c);
/***********************  utils  ***********************/
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *str, int fd);
char	*ft_strdup(const char *s1);
/***********************  init  ***********************/
t_game  *init_cub(int ac, char **av);
t_game  *get_map(t_game *game);
void    start_game(t_game *game);
int    	render_game(t_game *game);
int 	valid_input(int ac, char **av);
void	fov(t_game *game);
void	events_hook(t_game *game);
void    draw_walls(t_game *game);
/***********************  draw  ***********************/
#endif
