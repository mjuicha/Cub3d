/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:20:18 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/07 17:11:15 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] != '1')
			return (FAILURE);
		else
			i++;
	}
	return (SUCCESS);
}

int	check_mline(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] && line[i] == '1')
		i++;
	else
		return (FAILURE);
	i = ft_strlen(line) - 1;
	while (line[i] == ' ')
		i--;
	if (line[i] && line[i] == '1')
		return (SUCCESS);
	return (FAILURE);
}

int	check_middle(t_game *game)
{
	int	i;

	i = 1;
	while (i < game->mapcounter)
	{
		if (!check_mline(game->map[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	check_edges(t_game *game)
{
	char	*line;

	game->mapcounter = limit(game);
	if (!game->map[0] || !game->map[game->mapcounter])
		return (FAILURE);
	line = game->map[0];
	if (!check_line(line))
		return (FAILURE);
	line = game->map[game->mapcounter];
	if (!check_line(line))
		return (FAILURE);
	if (!check_middle(game))
		return (FAILURE);
	return (SUCCESS);
}

int	find_open_space(char c, int i, int j, t_game *game)
{
	if (c == ' ' || c == '1')
		return (FAILURE);
	else if (ft_strchr("NSWED0", c))
	{
		if (!(game->map[i][j - 1]) || !(game->map[i][j + 1])
			|| !(game->map[i - 1][j]) || !(game->map[i + 1][j]))
			return (SUCCESS);
		if (game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' '
			|| game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ')
			return (SUCCESS);
	}
	else
		return (SUCCESS);
	return (FAILURE);
}
