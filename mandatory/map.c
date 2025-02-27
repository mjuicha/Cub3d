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
	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->line = ft_strdup(line);
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

char	**list2array(t_map *map, t_game *game)
{
	char	**array;
	int		i;
	t_map	*tmp;

	game->mapcounter = mapcounter(map);
	printf("counter %d\n", game->mapcounter);
	array = malloc(sizeof(char *) * (game->mapcounter + 1));
	if (!array)
		return (NULL);
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

	str = game->start_line;
	map = add_back_map(map, new_map(str));
	while (str)
	{
		free(str);
		str = get_next_line(game->mapfd);
		map = add_back_map(map, new_map(str));
	}
	game->map = list2array(map, game);
	close(game->mapfd);
	return (game);
}