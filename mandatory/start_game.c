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
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
        printf("img failed\n");
    game->endian = malloc(sizeof(int));
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, game->endian);
    if (!game->addr)
        printf("addr failed\n");
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
				game->player->pos_x = j * TILE_SIZE + (game->width / 2);
				game->player->pos_y = i * TILE_SIZE + (game->height / 2);
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
    if (valid_format(game) == FAILURE)
        exit(FAILURE);
    get_player_info(game);
}

// void    init_img(t_game *game)
// {
//     game->black_wall = mlx_xpm_file_to_image(game->mlx, BLACK_WALL, &game->width, &game->height);
//     if (!game->black_wall)
//     {
//         free(game);
//         ft_putendl_fd(XPM_ERROR, STDERR_FILENO);
//         exit(FAILURE);
//     }
//     game->empty_wall = mlx_xpm_file_to_image(game->mlx, EMPTY_WALL, &game->width, &game->height);
//     if (!game->empty_wall)
//     {
//         free(game);
//         ft_putendl_fd(XPM_ERROR, STDERR_FILENO);
//         exit(FAILURE);
//     }
// }