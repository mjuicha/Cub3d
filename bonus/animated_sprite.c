/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:09:05 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/05 12:23:10 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_the_rest(t_game *game)
{
	if (game->sprite->img14)
		free_img(game->sprite->img14, game);
	if (game->sprite->img15)
		free_img(game->sprite->img15, game);
	if (game->sprite->img16)
		free_img(game->sprite->img16, game);
	if (game->sprite->img17)
		free_img(game->sprite->img17, game);
	if (game->sprite->img18)
		free_img(game->sprite->img18, game);
	if (game->sprite->img19)
		free_img(game->sprite->img19, game);
	if (game->sprite->img20)
		free_img(game->sprite->img20, game);
}

void	free_sprites(t_game *game)
{
	if (game->sprite)
	{
		if (game->sprite->img1)
			free_img(game->sprite->img1, game);
		if (game->sprite->img2)
			free_img(game->sprite->img2, game);
		if (game->sprite->img3)
			free_img(game->sprite->img3, game);
		if (game->sprite->img4)
			free_img(game->sprite->img4, game);
		if (game->sprite->img5)
			free_img(game->sprite->img5, game);
		if (game->sprite->img6)
			free_img(game->sprite->img6, game);
		if (game->sprite->img7)
			free_img(game->sprite->img7, game);
		if (game->sprite->img8)
			free_img(game->sprite->img8, game);
		if (game->sprite->img9)
			free_img(game->sprite->img9, game);
		if (game->sprite->img10)
			free_img(game->sprite->img10, game);
		free_the_rest(game);
		free(game->sprite);
	}
}

void	load_p1(t_game *game)
{
	game->sprite->img1 = texture_img(game, "textures/sprite/1.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img2 = texture_img(game, "textures/sprite/2.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img3 = texture_img(game, "textures/sprite/3.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img4 = texture_img(game, "textures/sprite/4.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img5 = texture_img(game, "textures/sprite/5.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img6 = texture_img(game, "textures/sprite/6.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img7 = texture_img(game, "textures/sprite/7.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img8 = texture_img(game, "textures/sprite/8.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img9 = texture_img(game, "textures/sprite/9.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img10 = texture_img(game, "textures/sprite/10.xpm",
			&game->sprite->height, &game->sprite->width);
}

void	load_p2(t_game *game)
{
	game->sprite->img14 = texture_img(game, "textures/sprite/14.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img15 = texture_img(game, "textures/sprite/15.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img16 = texture_img(game, "textures/sprite/16.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img17 = texture_img(game, "textures/sprite/17.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img18 = texture_img(game, "textures/sprite/18.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img19 = texture_img(game, "textures/sprite/19.xpm",
			&game->sprite->height, &game->sprite->width);
	game->sprite->img20 = texture_img(game, "textures/sprite/20.xpm",
			&game->sprite->height, &game->sprite->width);
}

void	load_gun(t_game *game)
{
	game->sprite = malloc(sizeof(t_sprite));
	if (!game->sprite)
		mlx_free(game, MALLOC_ERROR);
	game->sprite->width = 800;
	game->sprite->height = 450;
	game->is_sprite = 1;
	load_p1(game);
	load_p2(game);
}
