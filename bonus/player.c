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

void	bresenhams_line(int x, int y, int endx, int endy, t_game *game, int color)
{
	int dx = abs(endx - x);
	int dy = abs(endy - y);
	int sx = x < endx ? 1 : -1;
	int sy = y < endy ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, x, y, color);
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

void	get_dir(t_game *game, double angle)
{
	game->player->dir->down = (angle >= 0.0 && angle <= M_PI);
	game->player->dir->up = !game->player->dir->down;
	game->player->dir->right = (angle <= M_PI / 2 || angle >= 3 * M_PI / 2);
	game->player->dir->left = !game->player->dir->right;
}

double phitagore(int x1, int y1, int x2, int y2)
{
	return (sqrtl(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	check_waaal(t_game *game, int y, int x)
{
	if (x < 0 || y < 0 || y >= game->mapcounter || x >= ft_strlen(game->map[y]) || !game->map[y][x])
		return (1);
	if (game->map[y][x] == '1' || game->map[y][x] == 'D')
		return (1);
	return (0);
}

double	hoz(t_game *game, double angle)
{
	game->hy = (floor(game->player->pos_y / game->height) * game->height) + (game->player->dir->down ? game->height : 0);
	game->hx = game->player->pos_x + ((game->hy - game->player->pos_y) / tan(angle));
	double dy = game->height;
	if (game->player->dir->up)
		dy *= -1;
	double dx = game->height / tan(angle);
	if (game->player->dir->left && dx > 0)
		dx *= -1;
	if (game->player->dir->right && dx < 0)
		dx *= -1;
	double vet = 0;
	while (1)
	{
		vet = floor((game->hy + (game->player->dir->up ? -1 : 0)) / game->height);
		if (check_waaal(game, vet, floor(game->hx / game->width)))
			break;
		game->hx += dx;
		game->hy += dy;
	}
	return (phitagore(game->player->pos_x, game->player->pos_y, game->hx, game->hy));
}

double	ver(t_game *game, double angle)
{
	game->vx = (floor(game->player->pos_x / game->width) * game->width) + (game->player->dir->right ? game->width : 0);
	game->vy = game->player->pos_y + ((game->vx - game->player->pos_x) * tan(angle));
	double dx = game->width;
	if (game->player->dir->left)
		dx *= -1;
	double dy = game->width * tan(angle);
	if (game->player->dir->up && dy > 0)
		dy *= -1;
	if (game->player->dir->down && dy < 0)
		dy *= -1;
	double het = 0;
	while (1)
	{
		het = floor((game->vx + (game->player->dir->left ? -1 : 0)) / game->width);
		if (check_waaal(game, floor(game->vy / game->height), het))
			break;
		game->vx += dx;
		game->vy += dy;
	}
	return (phitagore(game->player->pos_x, game->player->pos_y, game->vx, game->vy));
}

int draw_line(t_game *mlx, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, mlx->mlx_win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}
void	rect(t_game *game, int x, int y, int height)
{
	int i = 0;
	while (i < height)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, x, y + i, GREEN);
		if (game->player->fetch == 0)
			printf("************\n");
		i++;
	}
}

void	wall_draw(t_game *game, int ray, int t_pix, int b_pix)
{
	while (t_pix < b_pix)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, ray, t_pix, GREEN);
		t_pix++;
	}
}

void	floor_draw(t_game *game, int ray, int b_pix, int t_pix)
{
	int i = 0;
	i = b_pix;
	while (i < HEIGHT)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, ray, i, YELLOW);
		i++;
	}
	i = 0;
	while (i < t_pix)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, ray, i, BLUE);
		i++;
	}
}
void	is_door(t_game *game, int ray)
{
	int x = game->wallx[ray];
	int y = game->wally[ray];
	if (game->is_hor[ray])
		y = (game->player->dir->up) ? y - 1 : y;
	else
		x = (game->player->dir->left) ? x - 1 : x;
	x = x / game->width;
	y = y / game->height;
	if (game->map[y][x] == 'D')
		game->is_door[ray] = 1;
	else
		game->is_door[ray] = 0;
}

void	cast_ra(t_game *game, double angle, int ray)
{
	angle = normalize_angle(angle);
	get_dir(game, angle);
	double H_dis = hoz(game, angle);
	double V_dis = ver(game, angle);
	game->dis[ray] = (H_dis <= V_dis) ? H_dis : V_dis;
	game->wallx[ray] = (H_dis <= V_dis) ? game->hx : game->vx;
	game->wally[ray] = (H_dis <= V_dis) ? game->hy : game->vy;
	game->t_angle[ray] = angle;
	game->is_hor[ray] = (H_dis <= V_dis) ? 1 : 0;
	is_door(game, ray);
	game->is_spec[ray] = (H_dis == V_dis) ? 1 : 0;
}


void	fov(t_game *game)
{
	double angle = game->player->angle - FOV / 2;
	int i = 0;
	while (i < WIDTH)
	{
		cast_ra(game, angle, i);
		angle += FOV / WIDTH;
		i++;
	}
}
