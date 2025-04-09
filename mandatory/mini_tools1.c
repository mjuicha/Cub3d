/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:57:23 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 18:22:40 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_down(t_game *game)
{
	if (game->player->dir->down)
		return (game->height);
	return (0);
}

int	is_right(t_game *game)
{
	if (game->player->dir->right)
		return (game->width);
	return (0);
}

int	is_up(t_game *game)
{
	if (game->player->dir->up)
		return (-1);
	return (0);
}

int	is_left(t_game *game)
{
	if (game->player->dir->left)
		return (-1);
	return (0);
}

void	spec_case(t_game *game, int ray)
{
	if (ray > 0 && ray < WIDTH - 1)
	{
		if (game->is_spec[ray] && game->is_hor[ray]
			&& (!game->is_hor[ray - 1] || !game->is_hor[ray + 1]))
			game->is_hor[ray] = 0;
	}
}
