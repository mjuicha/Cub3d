/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:33:31 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 23:20:53 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_array(t_game *game, char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n' || ft_strchr2(line, "F ")
		|| ft_strchr2(line, "C "))
		return (1);
	while (i < 4)
	{
		if (game->texture_path[i] == NULL)
			return (1);
		i++;
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
	i = skip(line);
	alloc = 0;
	while (line[i + alloc] && !(line[i + alloc] == ' '))
		alloc++;
	path = malloc(sizeof(char) * (alloc));
	if (!path)
	{
		free_path(game);
		auto_exit(game, MALLOC_ERROR);
	}
	j = 0;
	while (j < alloc - 1)
	{
		path[j] = line[i + j];
		j++;
	}
	path[j] = '\0';
	return (path);
}

char	**alloc(char **tab, int size)
{
	int	i;

	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		auto_exit(NULL, MALLOC_ERROR);
	while (i < size)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}

char	**get_texture_path(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	game->texture_path = alloc(game->texture_path, 5);
	line = get_next_line(game->mapfd);
	while (line && check_array(game, line))
	{
		i = direction(line, game);
		if (i)
			game->texture_path[i - 1] = path(game, line);
		free(line);
		line = get_next_line(game->mapfd);
	}
	if (line)
	{
		game->start_line = ft_strdup(line);
		free(line);
	}
	else
	{
		free_path(game);
		auto_exit(game, MAP_ERROR);
	}
	return (game->texture_path);
}
