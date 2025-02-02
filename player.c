#include "cub3d.h"

void	pl(t_game *game)
{
	int x = game->player->pos_x;
	int y = game->player->pos_y;
	int r = 10;
	int i = -r;
	int j = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
				mlx_pixel_put(game->mlx, game->mlx_win, x + i, y + j, RED);
			j++;
		}
		i++;
	}
}

void	circle(t_game *game, int x, int y, int r)
{
	int i = -r;
	int j = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
				mlx_pixel_put(game->mlx, game->mlx_win, x + i, y + j, RED);
			j++;
		}
		i++;
	}
}
// void	cast_ray(t_game *game, double angle)
// {
// 	double x = game->player->pos_x;
// 	double y = game->player->pos_y;
// 	double dx = cos(angle);
// 	double dy = sin(angle);
// 	int map_x, map_y;
// 	int Ax, Ay, Bx, By;
// 	Ay = (int)y / game->height * game->height;
// 	Ax = x + (Ay - y) / tan(angle);
// 	By = Ay + game->height;
// 	Bx = By / tan(angle);
// 	int delta_x = Bx - Ax;
// 	int delta_y = game->height;
// 	map_x = Ax / game->width;
// 	map_y = Ay / game->height;
// 	printf("Ax is %d, Ay is %d\n", Ax, Ay);
// 	printf("Bx is %d, By is %d\n", Bx, By);
// 	printf("delta_x is %d, delta_y is %d\n", delta_x, delta_y);
// 	int xx = 0;
// 	while (1)
// 	{
// 		xx++;
// 		Ax += delta_x;
// 		Ay += delta_y;
// 		map_x = Ax / game->width;
// 		map_y = Ay / game->height;
// 		if (map_x < 0 || map_y < 0 || map_x >= 10 || map_y >= 10)
// 			break;
// 		printf("xx is %d\n", xx);
// 		if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1')
// 		{
// 			printf("break is on %d, %d\n", map_x, map_y);
// 			printf("heet is on %d, %d\n", Ax, Ay);
// 			break;
// 		}
// 	}
// }
void	bresenhams_line(int x, int y, int endx, int endy, t_game *game)
{
	int dx = abs(endx - x);
	int dy = abs(endy - y);
	int sx = x < endx ? 1 : -1;
	int sy = y < endy ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, x, y, GREEN);
		if (x == endx && y == endy)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

void	get_dir(t_game *game)
{
	double angle = game->player->angle;
	game->player->dir->up = (angle >= 0 && angle <= M_PI);
	game->player->dir->down = !game->player->dir->up;
	game->player->dir->right = (angle <= M_PI / 2 || angle >= 3 * M_PI / 2);
	game->player->dir->left = !game->player->dir->right;
}

int phitagore(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
void	cast_ray(t_game *game, double angle)
{
	double x = game->player->pos_x;
	double y = game->player->pos_y;
	double dx = cos(angle);
	double dy = sin(angle);
	int map_x, map_y;
	while (1)
	{
		x += dx;
		y += dy;
		map_x = (int)x / game->width;
		map_y = (int)y / game->height;
		if (map_x < 0 || map_y < 0 || map_x >= 10 || map_y >= 10)
			break;
		if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1')
			break;
		mlx_pixel_put(game->mlx, game->mlx_win, (int)x, (int)y, GREEN);
	}
}
void	cast_rayy(t_game *game, double angle)
{
	double x = game->player->pos_x;
	double y = game->player->pos_y;
	get_dir(game);
	int map_x, map_y;
	int hAx, hAy;
	int HTx, HTy;
	int vAx, vAy;
	int delta_hx = 0;
	int delta_hy = 0;
	int delta_vx = 0;
	int delta_vy = 0;
	bool fh = false;
	bool fv = false;
	/////////////////////
	/// HORIZONTAL RAY //
	/////////////////////
	hAy = (int)y / game->height * game->height;
	printf("hAy is %d\n", hAy);
	if (game->player->dir->down)
		hAy += game->height;
	hAx = x + (hAy - y) / tan(angle);
	delta_hy = game->height;
	if (game->player->dir->up)
		delta_hy *= -1;//clear
	delta_hx = game->height / tan(angle);
	if (game->player->dir->left && delta_hx > 0)
		delta_hx *= -1;
	if (game->player->dir->right && delta_hx < 0)
		delta_hx *= -1;
	HTx = hAx;
	HTy = hAy;
	if (game->player->dir->up)
		HTy -= 1;
	while (1)
	{
		map_x = HTx / game->width;
		map_y = HTy / game->height;
		if (map_x < 0 || map_y < 0 || map_x >= 10 || map_y >= 10)
			break;
		if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1')
		{
			fh = true;
			break;
		}
		HTx += delta_hx;
		HTy += delta_hy;
	}
	///////////////////
	/// VERICAL  RAY //
	///////////////////
	int VTx, VTy;
	vAx = (int)x / game->width * game->width;// done
	if (game->player->dir->right)
		vAx += game->width;
	vAy = y + (vAx - x) * tan(angle);
	delta_vx = game->width;
	if (game->player->dir->left)
		delta_vx *= -1;
	delta_vy = game->width * tan(angle);
	if (game->player->dir->up && delta_vy > 0)
		delta_vy *= -1;
	if (game->player->dir->down && delta_vy < 0)
		delta_vy *= -1;
	VTx = vAx;
	VTy = vAy;
	if (game->player->dir->left)
		VTx -= 1;
	while (1)
	{
		map_x = VTx / game->width;
		map_y = VTy / game->height;
		if (map_x < 0 || map_y < 0 || map_x >= 10 || map_y >= 10)
			break;
		if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1')
		{
			fv = true;
			break;
		}
		VTx += delta_vx;
		VTy += delta_vy;
	}
	int H_dis = (fh) ? phitagore(x, y, HTx, HTy) : 1000000;
	int V_dis = (fv) ? phitagore(x, y, VTx, VTy) : 1000000;
	vAy = (V_dis < H_dis) ? VTy : HTy;
	vAx = (H_dis < V_dis) ? HTx : VTx;
	int dis = (H_dis < V_dis) ? H_dis : V_dis;
	bresenhams_line(x, y, vAx, vAy, game);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
void	fov(t_game *game)
{
	game->player->angle = normalize_angle(game->player->angle);
	// exit(0);
	// double angle = game->player->angle - FOV / 2;
	// while (angle < game->player->angle + FOV / 2)
	// {
		cast_rayy(game, game->player->angle);
		// cast_ray(game, game->player->angle);
		// angle += FOV / WIDTH;
	// }
}

void    player(t_game *game)
{
    pl(game);
	fov(game);
}