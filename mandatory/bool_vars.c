/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:07:44 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 10:52:42 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_bool(t_game_data *game)
{
	game->alloc_bool->m_player = 0;
	game->alloc_bool->m_dir = 0;
	game->alloc_bool->m_dis = 0;
	game->alloc_bool->m_is_spec = 0;
	game->alloc_bool->m_t_angle = 0;
	game->alloc_bool->m_wallx = 0;
	game->alloc_bool->m_wally = 0;
	game->alloc_bool->m_is_hor = 0;
	game->alloc_bool->m_fd = 1;
	game->alloc_bool->n = 0;
	game->alloc_bool->s = 0;
	game->alloc_bool->e = 0;
	game->alloc_bool->w = 0;
}

void	alloc_vars_1(t_game_data *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_player = 1;
	game->player->dir = malloc(sizeof(t_dir));
	if (!game->player->dir)
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_dir = 1;
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

void	alloc_vars(t_game_data *game)
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
}
