/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:33:31 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/26 02:45:25 by mjuicha          ###   ########.fr       */
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
	if (check_path(game))
	{
		if (!(ft_strchr2(line, "NO") || ft_strchr2(line, "SO")
				|| ft_strchr2(line, "WE") || ft_strchr2(line, "EA")))
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
		short_free(game, MALLOC_ERROR);
	j = 0;
	while (j < alloc - 1)
	{
		path[j] = line[i + j];
		j++;
	}
	path[j] = '\0';
	return (path);
}

char	**alloc(char **tab, int size, t_game *game)
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
	game->texture_path = alloc(game->texture_path, 5, game);
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
