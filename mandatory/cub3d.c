#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game  *game;// is done

	game = init_cub(ac, av);// is done
    start_game(game);// is done
	load_textures(game);// is done

	events_hook(game); // is done
	mlx_loop_hook(game->mlx, render_game, game);// is done (fix text use)
    mlx_loop(game->mlx);// is done
	return (0);
}

