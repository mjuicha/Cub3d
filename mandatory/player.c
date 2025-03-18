/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:20:01 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 16:31:11 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_dir(t_game *game, double angle)
{
	game->player->dir->down = (angle >= 0.0 && angle <= M_PI);
	game->player->dir->up = !game->player->dir->down;
	game->player->dir->right = (angle <= M_PI / 2 || angle >= 3 * M_PI / 2);
	game->player->dir->left = !game->player->dir->right;
}

double	phitagore(int x1, int y1, int x2, int y2)
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
	if (x < 0 || y < 0 || y >= game->mapcounter \
		|| x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (game->map[y][x] && game->map[y][x] == '1')
		return (1);
	return (0);
}

double	hoz(t_game *game, double angle)
{
	double	dy;
	double	dx;
	double	vet;

	game->hy = (floor(game->player->pos_y / game->height) * game->height) + (game->player->dir->down ? game->height : 0);
	game->hx = game->player->pos_x + ((game->hy - game->player->pos_y) / tan(angle));
	dy = game->height;
	if (game->player->dir->up)
		dy *= -1;
	dx = game->height / tan(angle);
	if (game->player->dir->left && dx > 0)
		dx *= -1;
	if (game->player->dir->right && dx < 0)
		dx *= -1;
	vet = 0;
	while (1)
	{
		vet = floor((game->hy + (game->player->dir->up ? -1 : 0)) / game->height);
		if (check_waaal(game, vet, floor(game->hx / game->width)))
			break ;
		game->hx += dx;
		game->hy += dy;
	}
	return (phitagore(game->player->pos_x, game->player->pos_y, game->hx, game->hy));
}

double	ver(t_game *game, double angle)
{
	double	het;
	double	dy;
	double	dx;

	game->vx = (floor(game->player->pos_x / game->width) * game->width) + (game->player->dir->right ? game->width : 0);
	game->vy = game->player->pos_y + ((game->vx - game->player->pos_x) * tan(angle));
	dx = game->width;
	if (game->player->dir->left)
		dx *= -1;
	dy = game->width * tan(angle);
	if (game->player->dir->up && dy > 0)
		dy *= -1;
	if (game->player->dir->down && dy < 0)
		dy *= -1;
	het = 0;
	while (1)
	{
		het = floor((game->vx + (game->player->dir->left ? -1 : 0)) / game->width);
		if (check_waaal(game, floor(game->vy / game->height), het))
			break ;
		game->vx += dx;
		game->vy += dy;
	}
	return (phitagore(game->player->pos_x, game->player->pos_y, game->vx, game->vy));
}

void	cast_ra(t_game *game, double angle, int ray)
{
	double	h_dis;
	double	v_dis;

	angle = normalize_angle(angle);
	get_dir(game, angle);
	h_dis = hoz(game, angle);
	v_dis = ver(game, angle);
	game->dis[ray] = (h_dis <= v_dis) ? h_dis : v_dis;
	game->wallx[ray] = (h_dis <= v_dis) ? game->hx : game->vx;
	game->wally[ray] = (h_dis <= v_dis) ? game->hy : game->vy;
	game->t_angle[ray] = angle;
	game->is_hor[ray] = (h_dis <= v_dis) ? 1 : 0;
	game->is_spec[ray] = (h_dis == v_dis) ? 1 : 0;
}

void	fov(t_game *game)
{
	float	dis_proj;
	float	angle;
	int		i;

	i = 0;
	dis_proj = (WIDTH / 2) / tan(game->player->fov / 2);
	while (i < WIDTH)
	{
		angle = game->player->angle + atan((i - WIDTH / 2) / dis_proj);
		cast_ra(game, angle, i);
		i++;
	}
}
