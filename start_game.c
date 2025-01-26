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

void    init_img(t_game *game)
{
    game->black_wall = mlx_xpm_file_to_image(game->mlx, BLACK_WALL, &game->width, &game->height);
    if (!game->black_wall)
    {
        free(game);
        ft_putendl_fd(XPM_ERROR, STDERR_FILENO);
        exit(FAILURE);
    }
    game->empty_wall = mlx_xpm_file_to_image(game->mlx, EMPTY_WALL, &game->width, &game->height);
    if (!game->empty_wall)
    {
        free(game);
        ft_putendl_fd(XPM_ERROR, STDERR_FILENO);
        exit(FAILURE);
    }
}

void    start_game(t_game *game)
{
    if (!game)
        exit(FAILURE);
    init_mlx(game);
    init_img(game);
    get_map(game);
    get_player_info(game);
}