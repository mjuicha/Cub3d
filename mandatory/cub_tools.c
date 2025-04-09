/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 04:08:42 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 18:05:45 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	limit(t_game *game)
{
	int	i;

	i = game->mapcounter - 1;
	while (game->map[i])
	{
		if (game->map[i][0] != '\0')
			return (i);
		i--;
	}
	return (game->mapcounter - 1);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

void	skip_digits(char *line, int *i, int *rgb)
{
	while (line[*i] && is_digit(line[*i]))
		(*i)++;
	*rgb += 1;
	skip_spaces(line, i);
}

int	check_path(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_path[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}
