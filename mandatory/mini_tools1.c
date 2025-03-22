/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:57:23 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 11:18:39 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_down(t_game_data *game)
{
	if (game->player->dir->down)
		return (game->height);
	return (0);
}

int	is_right(t_game_data *game)
{
	if (game->player->dir->right)
		return (game->width);
	return (0);
}

int	is_up(t_game_data *game)
{
	if (game->player->dir->up)
		return (-1);
	return (0);
}

int	is_left(t_game_data *game)
{
	if (game->player->dir->left)
		return (-1);
	return (0);
}

void	spec_case(t_game_data *game, int ray)
{
	if (game->is_spec[ray] && game->is_hor[ray] && (!game->is_hor[ray - 1]
			|| !game->is_hor[ray + 1]))
		game->is_hor[ray] = 0;
}
