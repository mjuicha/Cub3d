/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_vars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:07:44 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 17:24:48 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_bool(t_game *game)
{
	game->alloc_bool->m_player = 0;
	game->alloc_bool->m_dis = 0;
	game->alloc_bool->m_is_spec = 0;
	game->alloc_bool->m_t_angle = 0;
	game->alloc_bool->m_wallx = 0;
	game->alloc_bool->m_wally = 0;
	game->alloc_bool->m_is_hor = 0;
	game->alloc_bool->m_is_door = 0;
	game->alloc_bool->m_fd = 1;
	game->alloc_bool->t_path = 0;
	game->alloc_bool->n = 0;
	game->alloc_bool->s = 0;
	game->alloc_bool->e = 0;
	game->alloc_bool->w = 0;
	game->alloc_bool->d = 0;
}

void	alloc_vars_1(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_player = 1;
	game->dis = malloc(sizeof(double) * WIDTH);
	if (!game->dis)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_dis = 1;
	game->is_spec = malloc(sizeof(double) * WIDTH);
	if (!game->is_spec)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_is_spec = 1;
	game->wallx = malloc(sizeof(double) * WIDTH);
	if (!game->wallx)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_wallx = 1;
	game->wally = malloc(sizeof(double) * WIDTH);
	if (!game->wally)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_wally = 1;
}

void	alloc_vars(t_game *game)
{
	alloc_vars_1(game);
	game->t_angle = malloc(sizeof(double) * WIDTH);
	if (!game->t_angle)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_t_angle = 1;
	game->is_hor = malloc(sizeof(int) * WIDTH);
	if (!game->is_hor)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_is_hor = 1;
	game->is_door = malloc(sizeof(int) * WIDTH);
	if (!game->is_door)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_is_door = 1;
}

void	init_load_animation(t_game *game)
{
	game->sprite->img1 = NULL;
	game->sprite->img2 = NULL;
	game->sprite->img3 = NULL;
	game->sprite->img4 = NULL;
	game->sprite->img5 = NULL;
	game->sprite->img6 = NULL;
	game->sprite->img7 = NULL;
	game->sprite->img8 = NULL;
	game->sprite->img9 = NULL;
	game->sprite->img10 = NULL;
	game->sprite->img14 = NULL;
	game->sprite->img15 = NULL;
	game->sprite->img16 = NULL;
	game->sprite->img17 = NULL;
	game->sprite->img18 = NULL;
	game->sprite->img19 = NULL;
	game->sprite->img20 = NULL;
	game->sprite->height = 450;
	game->sprite->width = 800;
}
