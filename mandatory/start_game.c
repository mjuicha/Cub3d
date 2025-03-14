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
    game->img_win = malloc(sizeof(t_texture));
    game->img_win->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img_win->img)
        printf("img failed\n");
    
    game->img_win->endian = malloc(sizeof(int));
	game->img_win->addr = mlx_get_data_addr(game->img_win->img, &game->img_win->bpp, &game->img_win->line_length, game->img_win->endian);
    if (!game->img_win->addr)
        printf("addr failed\n");
}

void    start_game(t_game *game)
{
    if (!game)
        exit(FAILURE);
    init_mlx(game);
    get_map(game);
    if (valid_format(game) == FAILURE)
        exit(FAILURE);
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