# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

typedef struct s_game
{
    void    *mlx;
    void    *mlx_win;
}               t_game;

void    leaks(void)
{
    system("leaks a.out");
}
int    exict(int key, t_game *game)
{
    if (key == 53)
    {
    printf("window closed\n");
    mlx_destroy_window(game->mlx, game->mlx_win);
    free(game);
    game = NULL;
    atexit(leaks);
    exit(0);
    }
    return (0);
}
int main()
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(game->mlx, 1920, 1080, "Hello world!");
    if (!game->mlx)
    {
        exict(53, game);
    }
    mlx_hook(game->mlx_win, 2, 0, exict, game);
    mlx_loop(game->mlx);
    free(game->mlx);
    return (0);
}