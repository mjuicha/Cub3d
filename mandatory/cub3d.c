#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game  *game;//

	game = init_cub(ac, av);// protected
	if (!game)
		return (1);
    start_game(game);// protected
	load_textures(game);// protected
	events_hook(game);// protected
	mlx_loop_hook(game->mlx, render_game, game);
    mlx_loop(game->mlx);
	return (0);
}

