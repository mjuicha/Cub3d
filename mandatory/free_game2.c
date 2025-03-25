/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:02:04 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/23 17:53:45 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	auto_free(t_game *game)
{
	if (game->alloc_bool->m_player)
		free(game->player);
	if (game->alloc_bool->m_is_hor)
		free(game->is_hor);
	if (game->alloc_bool->m_wallx)
		free(game->wallx);
	if (game->alloc_bool->m_wally)
		free(game->wally);
	if (game->alloc_bool->m_t_angle)
		free(game->t_angle);
	if (game->alloc_bool->m_is_spec)
		free(game->is_spec);
	if (game->alloc_bool->m_dis)
		free(game->dis);
	if (game->alloc_bool->m_fd)
		close(game->mapfd);
	if (game->alloc_bool->t_path)
		free_path(game);
	free(game->alloc_bool);
	free(game);
}

void	ft_putendl_fd(char *str, int fd)
{
	if (fd == -1 || !str)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_error(char *error)
{
	if (!error)
		return ;
	ft_putendl_fd(error, STDERR_FILENO);
}

void	auto_exit(t_game *game, char *error)
{
	ft_error(error);
	auto_free(game);
	if (!error)
		exit(SUCCESS);
	exit(FAILURE);
}
