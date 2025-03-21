/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:20:18 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/21 04:08:22 by mjuicha          ###   ########.fr       */
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
	int	limite;

	i = 1;
	limite = limit(game);
	while (i < limite)
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

	if (!game->map[0] || !game->map[game->mapcounter - 1])
		return (FAILURE);
	line = game->map[0];
	if (!check_line(line))
		return (FAILURE);
	line = game->map[game->mapcounter - 1];
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
	else if (c == '0' || ft_strchr("NSWE", c))
	{
		if (!(game->map[i][j - 1]) || !(game->map[i][j + 1])
			|| !(game->map[i - 1][j]) || !(game->map[i + 1][j]))
			return (FAILURE);
		if (game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' '
			|| game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ')
			return (SUCCESS);
	}
	else
		return (SUCCESS);
	return (FAILURE);
}
