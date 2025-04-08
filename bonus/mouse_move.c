/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:13:29 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/08 14:42:14 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	static int	old_mouse_x = 0;
	int			diff;
	float		turn_scale;

	(void)y;
	diff = abs(x - old_mouse_x);
	turn_scale = 0.2;
	if (x > old_mouse_x)
		game->player->turn_dir = turn_scale;
	else
		game->player->turn_dir = -turn_scale;
	while (diff--)
		turn_player(game);
	game->player->turn_dir = 0;
	old_mouse_x = x;
	return (0);
}

void	frame1(t_game *game, void **img, int frame)
{
	if (!frame)
		*img = game->sprite->img1->img;
	else if (frame == 1)
		*img = game->sprite->img2->img;
	else if (frame == 2)
		*img = game->sprite->img3->img;
	else if (frame == 3)
		*img = game->sprite->img4->img;
	else if (frame == 4)
		*img = game->sprite->img5->img;
	else if (frame == 5)
		*img = game->sprite->img6->img;
	else if (frame == 6)
		*img = game->sprite->img7->img;
	else if (frame == 7)
		*img = game->sprite->img8->img;
	else if (frame == 8)
		*img = game->sprite->img9->img;
}

void	frame2(t_game *game, void **img, int frame)
{
	if (frame == 9)
		*img = game->sprite->img10->img;
	else if (frame == 10)
		*img = game->sprite->img14->img;
	else if (frame == 11)
		*img = game->sprite->img15->img;
	else if (frame == 12)
		*img = game->sprite->img16->img;
	else if (frame == 13)
		*img = game->sprite->img17->img;
	else if (frame == 14)
		*img = game->sprite->img18->img;
	else if (frame == 15)
		*img = game->sprite->img19->img;
	else if (frame == 16)
		*img = game->sprite->img20->img;
}

void	player_attack(t_game *game, void **img)
{
	static int	frame = 0;

	if (frame <= 8)
		frame1(game, img, frame);
	else
		frame2(game, img, frame);
	frame++;
	if (frame == 16)
	{
		frame = 0;
		game->is_fighting = 0;
	}
}

void	animated_sprite(t_game *game)
{
	void	*img;

	img = NULL;
	if (game->is_fighting)
		player_attack(game, &img);
	else
		img = game->sprite->img1->img;
	mlx_put_image_to_window(game->mlx, game->mlx_win, img, 140, 320);
}
