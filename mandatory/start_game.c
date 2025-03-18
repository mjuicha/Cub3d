/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:33:09 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 16:36:28 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_free(t_game *game, char *error)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	free_path(game);
	auto_exit(game, error);
}

void	init_img(t_game *game)
{
	game->img_win = malloc(sizeof(t_texture));
	if (!game->img_win)
		mlx_free(game, MALLOC_ERROR);
	game->img_win->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img_win->img)
	{
		free(game->img_win);
		mlx_free(game, MALLOC_ERROR);
	}
	game->img_win->addr = mlx_get_data_addr(game->img_win->img,
			&game->img_win->bpp, &game->img_win->line_length,
			&game->img_win->endian);
	if (!game->img_win->addr)
	{
		mlx_destroy_image(game->mlx, game->img_win->img);
		free(game->img_win);
		mlx_free(game, MALLOC_ERROR);
	}
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_path(game);
		auto_exit(game, MLX_ERROR);
	}
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->mlx_win)
	{
		free_path(game);
		auto_exit(game, MLX_WIN_ERROR);
	}
	init_img(game);
}

void	start_game(t_game *game)
{
	init_mlx(game);
	get_map(game);
	valid_format(game);
}
