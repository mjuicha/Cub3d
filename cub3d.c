#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game  *game;

	game = init_cub(ac, av);
    start_game(game);
	events_hook(game);
    launch_game(game);
    mlx_loop(game->mlx);
	return (0);
}
  