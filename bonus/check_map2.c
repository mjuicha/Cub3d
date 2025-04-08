/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:29:14 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/08 12:52:06 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_colors(t_game *game)
{
	if (game->floor == -1 || game->ceiling == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	check_open_spaces(t_game *game)
{
	int		i;
	int		j;
	char	*line;

	i = 1;
	j = 1;
	line = game->map[i];
	while (i < game->mapcounter)
	{
		j = 1;
		while (line[j])
		{
			if (find_open_space(line[j], i, j, game))
				return (FAILURE);
			j++;
		}
		i++;
		line = game->map[i];
	}
	return (SUCCESS);
}

int	valid_chars(char c, t_game *game, int i, int j)
{
	if (ft_strchr("NSWE", c))
	{
		if (game->player->found_player)
			return (FAILURE);
		game->player->found_player = 1;
		game->player->angle = angle_dir(c);
		game->player->pos_x = j * TILE_SIZE + (game->width / 2);
		game->player->pos_y = i * TILE_SIZE + (game->height / 2);
	}
	else if (c != '0' && c != '1' && c != 'D' && c != ' ' && c != '\n')
		return (FAILURE);
	if (c == 'D' && !game->founded_door)
		return (FAILURE);
	return (SUCCESS);
}

int	check_valid_char(t_game *game)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = game->map[i];
	while (game->map[i])
	{
		j = 0;
		while (line[j])
		{
			if (!valid_chars(line[j], game, i, j))
				return (FAILURE);
			j++;
		}
		i++;
		line = game->map[i];
	}
	if (!game->player->found_player)
		return (FAILURE);
	return (SUCCESS);
}
