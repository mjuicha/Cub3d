/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:12:02 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/01 16:01:48 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_game *game)
{
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->nord = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->door = NULL;
	game->texture_path = NULL;
	game->mini_map = NULL;
	game->wallx = NULL;
	game->wally = NULL;
	game->dis = NULL;
	game->is_spec = NULL;
	game->t_angle = NULL;
	game->is_hor = NULL;
	game->map = NULL;
	game->start_line = NULL;
	game->player = NULL;
	game->img_win = NULL;
	game->floor = -1;
	game->ceiling = -1;
	game->texture_map = 0;
}

int	check_spaces(t_game *game)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		line = game->map[i];
		while (line[j])
		{
			while (line[j] == ' ')
				j++;
			if (line[j] == '\0')
				return (FAILURE);
			while (line[j])
				j++;
		}
		i++;
	}
	return (SUCCESS);
}

void	short_free(t_game *game, char *error)
{
	free_path(game);
	auto_exit(game, error);
}

int	wall_surrounded(t_game *game, int newx, int newy)
{
	int		wallx;
	int		wally;

	wallx = (int)(game->player->pos_x / game->width);
	wally = (int)(game->player->pos_y / game->height);
	if (!(wallx != newx && wally != newy))
		return (0);
	if (game->map[wally][newx] == '1' && game->map[newy][wallx] == '1')
		return (1);
	if (game->map[wally][newx] == 'D' && game->map[newy][wallx] == 'D')
		return (1);
	return (0);
}
