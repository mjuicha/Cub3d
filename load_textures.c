/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:06:10 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/01 19:16:54 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_texture *img, t_game *game)
{
	if (img->img)
		mlx_destroy_image(game->mlx, img->img);
	free(img);
}

void	free_textures_map(t_game *game)
{
	if (game->mini_map)
	{
		if (game->mini_map->player)
			free_img(game->mini_map->player, game);
		if (game->mini_map->wall)
			free_img(game->mini_map->wall, game);
		if (game->mini_map->door)
			free_img(game->mini_map->door, game);
		if (game->mini_map->space)
			free_img(game->mini_map->space, game);
		free(game->mini_map);
	}
}

void	free_imgs(t_game *game)
{
	if (game->img_win)
		free_img(game->img_win, game);
	if (game->alloc_bool->n)
		free_img(game->nord, game);
	if (game->alloc_bool->s)
		free_img(game->south, game);
	if (game->alloc_bool->e)
		free_img(game->east, game);
	if (game->alloc_bool->w)
		free_img(game->west, game);
	if (game->alloc_bool->d)
		free_img(game->door, game);
	if (game->texture_map)
		free_textures_map(game);
}

t_texture	*texture_img(t_game *game, char *path, int *height, int *width)
{
	t_texture	*texture;

	texture = alloc_img();
	if (!texture)
		mlx_free(game, MALLOC_ERROR);
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			width, height);
	if (!texture->img)
		mlx_free(game, XPM_ERROR);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->addr)
		mlx_free(game, XPM_ERROR);
	return (texture);
}

void	load_textures(t_game *game)
{
	game->nord = texture_img(game, game->texture_path[0],
			&game->height, &game->width);
	game->alloc_bool->n = true;
	game->south = texture_img(game, game->texture_path[1],
			&game->height, &game->width);
	game->alloc_bool->s = true;
	game->east = texture_img(game, game->texture_path[2],
			&game->height, &game->width);
	game->alloc_bool->e = true;
	game->west = texture_img(game, game->texture_path[3],
			&game->height, &game->width);
	game->alloc_bool->w = true;
	game->door = texture_img(game, game->texture_path[4],
			&game->height, &game->width);
	game->alloc_bool->d = true;
	free_path(game);
	game->alloc_bool->t_path = false;
	load_textures_map(game);
}
