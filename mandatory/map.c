#include "cub3d.h"

int	mapcounter(t_map *map)
{
	t_map	*tmp;
	int		counter;

	counter = 0;
	tmp = map;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

t_map	*new_map(char *line)
{
	t_map *new;

	if (!line)
		return (NULL);
	line = ft_strrmv(line, 10);
	if (!line)
		return (NULL);
	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->line = line;
	if (!new->line)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_map	*add_back_map(t_map *map, t_map *new_map)
{
	t_map	*tmp;

	if (!new_map)
		return (map);
	if (!map)
		return (new_map);
	tmp = map;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_map;
	return (map);
}

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

char	**list2array(t_map *map, t_game *game)
{
	char	**array;
	int		i;
	t_map	*tmp;

	game->mapcounter = mapcounter(map);
	array = malloc(sizeof(char *) * (game->mapcounter + 1));
	if (!array)
	{
		free_list(map);
		mlx_destroy_image(game->mlx, game->img_win->img);
		free(game->img_win);
		mlx_free(game, MALLOC_ERROR);
		return (NULL);
	}
	i = 0;
	while (map && i < game->mapcounter)
	{
		array[i] = ft_strdup(map->line);
		free(map->line);
		tmp = map;
		map = map->next;
		free(tmp);
		i++;
	}
	array[i] = NULL;
	return (array);
}

t_game	*get_map(t_game *game)
{
	t_map	*map = NULL;
	char	*str;

	str = ft_strdup(game->start_line);
	free(game->start_line);
	game->start_line = NULL;
	map = add_back_map(map, new_map(str));
	if (!map)
	{
		mlx_destroy_image(game->mlx, game->img_win->img);
		free(game->img_win);
		mlx_free(game, MALLOC_ERROR);
	}
	while (str)
	{
		free(str);
		str = get_next_line(game->mapfd);
		map = add_back_map(map, new_map(str));
		if (!map)
		{
			mlx_destroy_image(game->mlx, game->img_win->img);
			free(game->img_win);
			mlx_free(game, MALLOC_ERROR);
		}
	}
	game->map = list2array(map, game);
	close(game->mapfd);
	game->alloc_bool->m_fd = 0;
	return (game);
}