/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:33:09 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/23 16:48:16 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*alloc_img(void)
{
	t_texture	*img;

	img = malloc(sizeof(t_texture));
	if (!img)
		return (NULL);
	img->img = NULL;
	img->addr = NULL;
	return (img);
}

void	init_img(t_game *game)
{
	game->img_win = alloc_img();
	if (!game->img_win)
		mlx_free(game, MALLOC_ERROR);
	game->img_win->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img_win->img)
		mlx_free(game, XPM_ERROR);
	game->img_win->addr = mlx_get_data_addr(game->img_win->img,
			&game->img_win->bpp, &game->img_win->line_length,
			&game->img_win->endian);
	if (!game->img_win->addr)
		mlx_free(game, XPM_ERROR);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		game_free(game, MLX_ERROR);
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->mlx_win)
		game_free(game, MLX_WIN_ERROR);
	init_img(game);
}

void	show_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		printf("%s\n", game->map[i]);
		i++;
	}
}

void	start_game(t_game *game)
{
	get_map(game);
	valid_format(game);
	init_mlx(game);
}
