/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:33:31 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 16:52:29 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_array(t_game *game, char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n' || ft_strcmpm(line, "F ")
		|| ft_strcmpm(line, "C ") || ft_strcmpm(line, "DO "))
		return (1);
	if (check_path(game))
	{
		if (!(ft_strcmpm(line, "NO ") || ft_strcmpm(line, "SO ")
				|| ft_strcmpm(line, "WE ") || ft_strcmpm(line, "EA ")))
		{
			free(line);
			short_free(game, MAP_ERROR);
		}
		return (1);
	}
	return (0);
}

char	*path(t_game *game, char *line)
{
	int		i;
	int		j;
	int		alloc;
	char	*path;

	i = 0;
	alloc = 0;
	i = skip(line);
	while (line[i + alloc] && !(line[i + alloc] == ' '
			|| line[i + alloc] == '\n'))
		alloc++;
	alloc++;
	path = malloc(sizeof(char) * (alloc));
	if (!path)
	{
		free(line);
		short_free(game, MALLOC_ERROR);
	}
	j = 0;
	while (j++ < alloc - 1)
		path[j - 1] = line[i + j - 1];
	path[j - 1] = '\0';
	return (path);
}

char	**alloc_double_array(char **tab, int size, t_game *game)
{
	int	i;

	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		auto_exit(game, MALLOC_ERROR);
	while (i < size)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}

void	fill_path(t_game *game, char *line, int i)
{
	if (i == 0)
		return ;
	if (game->texture_path[i - 1])
	{
		free(line);
		free_path(game);
		auto_exit(game, MAP_ERROR);
	}
	game->texture_path[i - 1] = path(game, line);
}

char	**get_texture_path(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	game->texture_path = alloc_double_array(game->texture_path, 5, game);
	line = get_next_line(game->mapfd);
	while (line && check_array(game, line))
	{
		i = direction(line, game);
		fill_path(game, line, i);
		free(line);
		line = get_next_line(game->mapfd);
	}
	if (line)
	{
		game->start_line = ft_strdup(line);
		free(line);
	}
	else
		short_free(game, MAP_ERROR);
	return (game->texture_path);
}
