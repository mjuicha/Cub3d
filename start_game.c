#include "cub3d.h"

void    init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        free(game);
        ft_putendl_fd(MLX_ERROR, STDERR_FILENO);
        exit(FAILURE);
    }
    game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
    if (!game->mlx_win)
    {
        free(game);
        ft_putendl_fd(MLX_WIN_ERROR, STDERR_FILENO);
        exit(FAILURE);
    }
}



void    get_player_info(t_game *game)
{
    game->player = malloc(sizeof(t_player));
    int i = 0;
    int j = 0;
    while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] && game->map[i][j] == 'P')
			{
				game->player->map_x = j;
				game->player->map_y = i;
				game->player->pos_x = j * TILE_SIZE + (48 / 2);
				game->player->pos_y = i * TILE_SIZE + (48 / 2);
				break ;
			}
			j++;
		}
		i++;
	}
}

void    start_game(t_game *game)
{
    if (!game)
        exit(FAILURE);
    init_mlx(game);
    get_map(game);
    get_player_info(game);
}