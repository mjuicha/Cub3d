/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:23 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 15:40:02 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = init_cub(ac, av);
	if (!game)
		return (1);
	start_game(game);
	load_textures(game);
	events_hook(game);
	mlx_loop_hook(game->mlx, render_game, game);
	mlx_loop(game->mlx);
	return (0);
}
