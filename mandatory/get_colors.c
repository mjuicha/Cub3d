/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:01:39 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 10:52:42 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_rgb(char *line, int *r, int *g, int *b)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && (line[i] == 'F' || line[i] == 'C'))
		i += 2;
	*r = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	*g = ft_atoi(line + i);
	while (line[i] != ',')
		i++;
	i++;
	*b = ft_atoi(line + i);
}

int	is_rgb(char *line)
{
	int	i;
	int	rgb;

	i = 0;
	rgb = 0;
	skip_spaces(line, &i);
	if (line[i] && (ft_strchr2(line + i, "F ") || ft_strchr2(line + i, "C ")))
		i += 2;
	else
		return (FAILURE);
	skip_spaces(line, &i);
	while (line[i] && rgb < 3)
	{
		if (!is_digit(line[i]))
			return (FAILURE);
		skip_digits(line, &i, &rgb);
		if ((line[i] != ',' && rgb < 3) || (rgb == 3 && line[i] == ','))
			return (FAILURE);
		if (rgb < 3)
			i++;
	}
	skip_spaces(line, &i);
	if (line[i] != '\n')
		return (FAILURE);
	return (SUCCESS);
}

void	get_color(char *line, t_game_data *game, int c)
{
	int	r;
	int	g;
	int	b;
	int	color;

	if (!is_rgb(line))
	{
		free(line);
		free_path(game);
		auto_exit(game, COLOR_ERROR);
	}
	get_rgb(line, &r, &g, &b);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(line);
		free_path(game);
		auto_exit(game, COLOR_ERROR);
	}
	color = (r << 16) + (g << 8) + b;
	if (c == 'F')
		game->floor = color;
	else
		game->ceiling = color;
}

unsigned int	get_coloor(t_game_data *game, int x, int y, int ray)
{
	char	*dst;

	if (game->off)
	{
		if (is_nord(game->t_angle[ray]))
			dst = game->nord->addr
				+ (y * game->nord->line_length + x * (game->nord->bpp / 8));
		else
			dst = game->south->addr
				+ (y * game->south->line_length + x * (game->south->bpp / 8));
	}
	else
	{
		if (is_east(game->t_angle[ray]))
			dst = game->east->addr
				+ (y * game->east->line_length + x * (game->east->bpp / 8));
		else
			dst = game->west->addr
				+ (y * game->west->line_length + x * (game->west->bpp / 8));
	}
	return (*(unsigned int *)dst);
}

void	put_pixel_to_img(t_game_data *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img_win->addr + (y * game->img_win->line_length
			+ x * (game->img_win->bpp / 8));
	*(unsigned int *)dst = color;
}
