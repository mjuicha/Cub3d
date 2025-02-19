#include "cub3d.h"

void get_img(t_game *game);
void get_img2(t_game *game);

void	get_img3(t_game *game)
{
	game->red_wall = mlx_xpm_file_to_image(game->mlx, "xpm_files/red_brick.xpm", &game->width, &game->height);
	game->endian3 = malloc(sizeof(int));
	game->addr3 = mlx_get_data_addr(game->red_wall, &game->bpp3, &game->line_length3, game->endian3);
}

void	get_img4(t_game *game)
{
	game->grey_wall = mlx_xpm_file_to_image(game->mlx, "xpm_files/grey_stone.xpm", &game->width, &game->height);
	game->endian4 = malloc(sizeof(int));
	game->addr4 = mlx_get_data_addr(game->grey_wall, &game->bpp4, &game->line_length4, game->endian4);
}
	
int	main(int ac, char **av)
{
	t_game  *game;

	game = init_cub(ac, av);
    start_game(game);
	get_img(game);
	get_img2(game);
	get_img3(game);
	get_img4(game);
	events_hook(game);
	mlx_loop_hook(game->mlx, render_game, game);
    mlx_loop(game->mlx);
	return (0);
}
  