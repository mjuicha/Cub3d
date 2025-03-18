/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:06:10 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 16:18:35 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_imgs(t_game *game)
{
	if (game->img_win->img)
		mlx_destroy_image(game->mlx, game->img_win->img);
	free(game->img_win);
	if (game->alloc_bool->n)
	{
		mlx_destroy_image(game->mlx, game->nord->img);
		free(game->nord);
	}
	if (game->alloc_bool->s)
	{
		mlx_destroy_image(game->mlx, game->south->img);
		free(game->south);
	}
	if (game->alloc_bool->e)
	{
		mlx_destroy_image(game->mlx, game->east->img);
		free(game->east);
	}
	if (game->alloc_bool->w)
	{
		mlx_destroy_image(game->mlx, game->west->img);
		free(game->west);
	}
}

t_texture	*texture_img(t_game *game, char *path)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		game_free(game, MALLOC_ERROR);
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&game->width, &game->height);
	if (!texture->img)
	{
		free(texture);
		game_free(game, MALLOC_ERROR);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(game->mlx, texture->img);
		free(texture);
		game_free(game, MALLOC_ERROR);
	}
	return (texture);
}

void	load_textures(t_game *game)
{
	game->nord = texture_img(game, game->texture_path[0]);
	game->alloc_bool->n = true;
	game->south = texture_img(game, game->texture_path[1]);
	game->alloc_bool->s = true;
	game->east = texture_img(game, game->texture_path[2]);
	game->alloc_bool->e = true;
	game->west = texture_img(game, game->texture_path[3]);
	game->alloc_bool->w = true;
}
