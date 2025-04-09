/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:04:26 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 16:52:29 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_list(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->line);
		free(tmp);
	}
}

void	free_path(t_game *game)
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
	if (game->founded_door)
		free(game->door_path);
}

void	free_map(t_game *game)
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

void	game_free(t_game *game, char *error)
{
	free_map(game);
	auto_exit(game, error);
}

void	mlx_free(t_game *game, char *error)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	free_imgs(game);
	game_free(game, error);
}
