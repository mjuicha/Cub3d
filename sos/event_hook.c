#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	printf("window closed\n");
	exit(0);
}

t_door_pos *check_door(t_game *game, int mapx, int mapy)
{
    t_door_pos *door;
    door = malloc(sizeof(t_door_pos));

    door->x = 0;
    door->valid = 1;
    if (game->map[mapy - 1][mapx] == 'D' || game->map[mapy - 1][mapx] == 'd')
    {
        door->x = mapx;
        door->y = mapy - 1;
    }
    else if (game->map[mapy + 1][mapx] == 'D' || game->map[mapy + 1][mapx] == 'd')
    {
        door->x = mapx;
        door->y = mapy + 1;
    }
    else if (game->map[mapy][mapx - 1] == 'D' || game->map[mapy][mapx - 1] == 'd')
    {
        door->x = mapx - 1;
        door->y = mapy;
    }
    else if (game->map[mapy][mapx + 1] == 'D' || game->map[mapy][mapx + 1] == 'd')
    {
        door->x = mapx + 1;
        door->y = mapy;
    }
    else if (game->map[mapy - 1][mapx + 1] == 'D' || game->map[mapy - 1][mapx + 1] == 'd')
    {
        door->y = mapy - 1;
        door->x = mapx + 1;
    }
    else if (game->map[mapy - 1][mapx - 1] == 'D' || game->map[mapy - 1][mapx - 1] == 'd')
    {
        door->y = mapy - 1;
        door->x = mapx - 1;
    }
    else if (game->map[mapy + 1][mapx + 1] == 'D' || game->map[mapy + 1][mapx + 1] == 'd')
    {
        door->y = mapy + 1;
        door->x = mapx + 1;
    }
    else if (game->map[mapy + 1][mapx - 1] == 'D' || game->map[mapy + 1][mapx - 1] == 'd')
    {
        door->y = mapy + 1;
        door->x = mapx - 1;
    }
    else 
        door->valid = 0;
    return (door);
}

void    open_close_door(t_game *game)
{
    int mapx;
    int mapy;
    t_door_pos *door;

    mapx = game->player->pos_x / game->width;
    mapy = game->player->pos_y / game->height;
    door = check_door(game, mapx, mapy);
    if (door->valid)
    {
        if (game->map[door->y][door->x] == 'D')
            game->map[door->y][door->x] = 'd';
        else if (game->map[door->y][door->x] == 'd')
            game->map[door->y][door->x] = 'D';
    }
}



int	key_pressed(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == W)
        game->player->walk_dir = 1;
	else if (keycode == S)
        game->player->walk_dir = -1;
    else if (keycode == A)
        game->player->side_dir = -1;
    else if (keycode == D)
        game->player->side_dir = 1;
    else if (keycode == LEFT)
        game->player->turn_dir = -1;
    else if (keycode == RIGHT)
        game->player->turn_dir = 1;
    else if (keycode == SPACE)
        open_close_door(game);
    else if (keycode == M)
        game->set = 1;
	return (0);
}

int	key_released(int keycode, t_game *game)
{
    if (keycode == W || keycode == S)
        game->player->walk_dir = 0;
    else if (keycode == A || keycode == D)
        game->player->side_dir = 0;
    else if (keycode == LEFT || keycode == RIGHT)
        game->player->turn_dir = 0;
    return (0);
}

int mouse_move(int x, int y, t_game *game)
{
    static int old_mouse_x = 0;
    int diff;
    float turn_scale;
    int screen_width = 1024;  // Replace with dynamic screen width if available

    if (old_mouse_x != -1 && x != old_mouse_x)
    {
        diff = abs(x - old_mouse_x);

        // Normalize the turn factor based on screen width
        // This makes sure the turn speed is proportional to screen size
        turn_scale = 180.0f / 2560;  // 360 degrees of rotation for the full width of the screen

        // Set the turn direction based on the relative movement
        if (x > old_mouse_x)
            game->player->turn_dir = turn_scale;  // Rotate to the right
        else
            game->player->turn_dir = -turn_scale; // Rotate to the left

        // Loop to apply the turn (scaled for precision)
        while (diff--)
        {
            turn_player(game);
        }

        game->player->turn_dir = 0;  // Reset turn direction after movement
    }

    old_mouse_x = x;
    return 0;
}

int stop_mouse(int x, int y, t_game *game)
{
    if (game->mouse_ready)
    {
        game->mouse_ready = 0;
        sleep(1);
        game->player->turn_dir = 0;
    }
    return (0);
}

void	events_hook(t_game *game)
{   
	mlx_hook(game->mlx_win, 2, 0, key_pressed, game);
    mlx_hook(game->mlx_win, 3, 0, key_released, game);
    mlx_hook(game->mlx_win, 6, 0, mouse_move, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
}