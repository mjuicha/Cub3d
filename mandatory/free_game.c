/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:04:26 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 11:13:55 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list(t_file_cont *map)
{
	t_file_cont	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->line);
		free(tmp);
	}
}

void	free_path(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_path[i])
			free(game->texture_path[i]);
		i++;
	}
	free(game->texture_path);
	if (game->start_line)
		free(game->start_line);
}

void	free_map(t_game_data *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	game_free(t_game_data *game, char *error)
{
	free_map(game);
	free_imgs(game);
	mlx_free(game, error);
}
