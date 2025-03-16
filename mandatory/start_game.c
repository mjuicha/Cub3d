#include "cub3d.h"


void    mlx_free(t_game *game, char *error)
{
    mlx_destroy_window(game->mlx, game->mlx_win);
    free(game->mlx);
    free_path(game);
    auto_exit(game, error);
}

void    free_img(t_texture *img)
{
    free(img->endian);
    free(img);
}

void    init_img(t_game *game)
{
    game->img_win = malloc(sizeof(t_texture));
    if (!game->img_win)
        mlx_free(game, MALLOC_ERROR);
    game->img_win->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img_win->img)
    {
        free(game->img_win);
        mlx_free(game, MALLOC_ERROR);
    }
    game->img_win->endian = malloc(sizeof(int));
    if (!game->img_win->endian)
    {
        free(game->img_win->img);
        free(game->img_win);
        mlx_free(game, MALLOC_ERROR);
    }
    game->img_win->addr = mlx_get_data_addr(game->img_win->img, &game->img_win->bpp, &game->img_win->line_length, game->img_win->endian);
    if (!game->img_win->addr)
    {
        free_img(game->img_win);
        mlx_free(game, MALLOC_ERROR);
    }
}

void    init_mlx(t_game *game)
{
    
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        free_path(game);
        auto_exit(game, MLX_ERROR);
    }

    game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
    if (!game->mlx_win)
    {
        mlx_destroy_window(game->mlx, game->mlx_win);
        free_path(game);
        auto_exit(game, MLX_WIN_ERROR);
    }
    //end
    mlx_destroy_window(game->mlx, game->mlx_win);
    free(game->mlx);
    free_path(game);
    auto_exit(game, NULL);
}

void    start_game(t_game *game)
{
    init_mlx(game);
    get_map(game);
    valid_format(game);
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