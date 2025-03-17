# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

void    leaks(void)
{
    system("leaks a.out");
}
typedef struct  s_game
{
    void    *mlx;
    void    *mlx_win;
}               t_game;

int vb(int keycode, t_game *game)
{
    printf("keycode: %d\n", keycode);
    if (keycode == 53)
    {
        mlx_destroy_window(game->mlx, game->mlx_win);
        free(game);
        atexit(leaks);
        exit(0);
    }
    return (0);
}
int main(void) {
    t_game *game = malloc(sizeof(t_game));
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(game->mlx, 800, 600, "Hello world!");
    vb(53, game);
    mlx_loop(game->mlx);
    return (0);
}