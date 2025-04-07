/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:20:01 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/07 19:29:48 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_waaal(t_game *game, int y, int x)
{
	if (x < 0 || y < 0 || y >= game->mapcounter \
		|| x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (game->map[y][x] && (game->map[y][x] == '1' || game->map[y][x] == 'D'))
		return (1);
	return (0);
}

double	hoz(t_game *game, double angle)
{
	double	dy;
	double	dx;
	double	vet;

	game->hy = (floor(game->player->pos_y / game->height) * game->height)
		+ is_down(game);
	game->hx = game->player->pos_x + ((game->hy - game->player->pos_y)
			/ tan(angle));
	dy = game->height;
	if (game->player->dir->up)
		dy *= -1;
	dx = game->height / tan(angle);
	if ((game->player->dir->left && dx > 0)
		|| (game->player->dir->right && dx < 0))
		dx *= -1;
	vet = 0;
	while (1)
	{
		vet = floor((game->hy + _up(game)) / game->height);
		if (check_waaal(game, vet, floor(game->hx / game->width)))
			break ;
		game->hx += dx;
		game->hy += dy;
	}
	return (phitagore(game, game->hx, game->hy));
}

double	ver(t_game *game, double angle)
{
	double	het;
	double	dy;
	double	dx;

	game->vx = (floor(game->player->pos_x / game->width) * game->width)
		+ is_right(game);
	game->vy = game->player->pos_y + ((game->vx - game->player->pos_x)
			* tan(angle));
	dx = game->width;
	if (game->player->dir->left)
		dx *= -1;
	dy = game->width * tan(angle);
	if ((game->player->dir->up && dy > 0)
		|| (game->player->dir->down && dy < 0))
		dy *= -1;
	het = 0;
	while (1)
	{
		het = floor((game->vx + _left(game)) / game->width);
		if (check_waaal(game, floor(game->vy / game->height), het))
			break ;
		game->vx += dx;
		game->vy += dy;
	}
	return (phitagore(game, game->vx, game->vy));
}

void	cast_ra(t_game *game, double angle, int ray)
{
	double	h_dis;
	double	v_dis;

	angle = normalize_angle(angle);
	game->player->dir = get_dir(game, angle);
	h_dis = hoz(game, angle);
	v_dis = ver(game, angle);
	free(game->player->dir);
	game->dis[ray] = _short(h_dis, v_dis, h_dis, v_dis);
	game->wallx[ray] = _short(h_dis, v_dis, game->hx, game->vx);
	game->wally[ray] = _short(h_dis, v_dis, game->hy, game->vy);
	game->t_angle[ray] = angle;
	game->is_hor[ray] = inf_equal(h_dis, v_dis);
	is_door(game, ray);
	game->is_spec[ray] = equal(h_dis, v_dis);
}

void	fov(t_game *game)
{
	double	angle;
	int		i;

	i = 0;
	angle = game->player->angle - (game->player->fov / 2);
	while (i < WIDTH)
	{
		cast_ra(game, angle, i);
		angle += game->player->fov / WIDTH;
		i++;
	}
}
