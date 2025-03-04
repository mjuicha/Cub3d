#include "cub3d.h"

void get_img(t_game *game);
void get_img2(t_game *game);

void	get_img3(t_game *game)
{
	game->red_wall = mlx_xpm_file_to_image(game->mlx, game->texture_path[2], &game->width, &game->height);

	game->endian3 = malloc(sizeof(int));
	game->addr3 = mlx_get_data_addr(game->red_wall, &game->bpp3, &game->line_length3, game->endian3);
}

void	get_img4(t_game *game)
{
	game->grey_wall = mlx_xpm_file_to_image(game->mlx, game->texture_path[3], &game->width, &game->height);
	game->endian4 = malloc(sizeof(int));
	game->addr4 = mlx_get_data_addr(game->grey_wall, &game->bpp4, &game->line_length4, game->endian4);
}
void	sprites_img(t_game *game)
{
	int width = 250;
	int height = 222;
	game->sprite = mlx_xpm_file_to_image(game->mlx, "xpm_files/sprites.xpm", &width, &height);
	game->endian0 = malloc(sizeof(int));
	game->addr0 = mlx_get_data_addr(game->sprite, &game->bpp0, &game->line_length0, game->endian0);
}
int	main(int ac, char **av)
{
	t_game  *game;

	game = init_cub(ac, av); // parsing
    start_game(game); // setup first frame
	get_img(game); // load textures
	get_img2(game); // load textures
	get_img3(game); // 		load textures
	get_img4(game); // 		load textures
	sprites_img(game); // load textures
	events_hook(game); 
	mlx_loop_hook(game->mlx, render_game, game);
    mlx_loop(game->mlx);
	return (0);
}
  