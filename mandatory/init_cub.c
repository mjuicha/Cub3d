#include "cub3d.h"

void	ft_error(char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
}

int	valid_extension(char **av)
{
	if (!av || !av[1])
	{
		ft_error(ERROR_EXT);
		return (FAILURE);
	}
	if (ft_strcmp(".cub", &av[1][ft_strlen(av[1]) - 4]) != 0)
	{
		ft_error(ERROR_EXT);
		return (FAILURE);
	}
	return (SUCCESS);
}

int valid_args(int ac)
{
	if (ac == 2)
		return (SUCCESS);
	ft_error(ERROR_ARG);
	return (FAILURE);
}

int	valid_file(char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error(OPPEN_ERROR);
	return (fd);
}

void	show_map(t_game *game)
{
	int i = 0;
	while (game->map[i])
	{
		printf(">> %d %s", i,game->map[i]);
		i++;
	}
}

int	check_line(char *line)
{
	int i = 0;

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
	int i = 0;
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
	int i = 1;
	while (i < game->mapcounter - 1)
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
		if (game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' ' || game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ')
			return (printf("<%c >%c i%d !%c\n",game->map[i][j - 1], game->map[i][j + 1], game->map[i - 1][j], game->map[i + 1][j])
				,SUCCESS);
	}
	else
		return (printf ("c %d\n", c),
			SUCCESS);
	return (FAILURE);
}

int check_open_spaces(t_game *game)
{
	int i = 1;
	int j = 1;

	char *line = game->map[i];
	printf("mapcounter %d\n", game->mapcounter);
	while (i < game->mapcounter - 1)
	{
		j = 1;
		while (line[j])
		{
			if (find_open_space(line[j], i , j, game))
				return (printf("gi %d %d %d\n",i,j,line[j]), FAILURE);
			j++;
		}
		i++;
		line = game->map[i];
	}
	return (SUCCESS);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->mapcounter || y >= ft_strlen(game->map[x]))
		return ;
	if (game->cp_map[x][y] == '1' || game->cp_map[x][y] == 'x' || game->cp_map[x][y] == ' ')
		return ;
	game->cp_map[x][y] = 'x';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}

double	angle_dir(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'W')
		return (M_PI);
	if (c == 'E')
		return (0);
	return (0);
}

int	check_valid_char(t_game *game)
{
	int i = 0;
	int j = 0;
	int found_player = 0;
	char *line = game->map[i];

	while (i < game->mapcounter)
	{
		j = 0;
		while (line[j])
		{
			if (ft_strchr("NSWE", line[j]))
			{
				if (found_player)
					return (FAILURE);
				found_player = 1;
				game->player->angle = angle_dir(line[j]);
				game->player->pos_x = j * TILE_SIZE + (game->width / 2);
				game->player->pos_y = i * TILE_SIZE + (game->height / 2);
			}
			else if (line[j] != '0' && line[j] != '1' && line[j] != ' ')
				return (FAILURE);
			j++;
		}
		i++;
		line = game->map[i];
	}
	if (!found_player)
		return (FAILURE);
	return (SUCCESS);
}

int	valid_format(t_game *game)
{
	if (!check_edges(game) || !check_valid_char(game) || !check_open_spaces(game))
	{
		ft_error(MAP_ERROR);
		return (FAILURE);
	}
	printf("map is valid\n");
	return (SUCCESS);
}

int valid_input(int ac, char **av)
{
	if (!valid_args(ac))
		return (FAILURE);
	if (!valid_extension(av))
		return (FAILURE);
	return (SUCCESS);
}

int	direction(char *line)
{
	if (ft_strchr2(line, "NO"))
		return (1);
	if (ft_strchr2(line, "SO"))
		return (2);
	if (ft_strchr2(line, "WE"))
		return (3);
	if (ft_strchr2(line, "EA"))
		return (4);
	return (0);
}
int	white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	skip(char *line)
{
	int i = 0;
	while (white_space(line[i]))
		i++;
	if (direction(line + i))
		i += 2;
	while (white_space(line[i]))
		i++;
	return (i);
}


char	*path(char *line)
{
	int i = 0;
	i = skip(line);
	int alloc = 0;
	while (line[i + alloc] && !white_space(line[i + alloc]))
		alloc++;
	char *path = malloc(sizeof(char) * (alloc + 1));
	if (!path)
	{
		ft_error(MLX_ERROR);
		exit(FAILURE);
	}
	int j = 0;
	while (j < alloc)
	{
		path[j] = line[i + j];
		j++;
	}
	path[j] = '\0';
	return (path);
}

char	**alloc(char **tab, int size)
{
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
	{
		ft_error(MLX_ERROR);
		exit(FAILURE);
	}
	int i = 0;
	while (i < size)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}

int	check_array(t_game *game, char *line)
{
	int i = 0;
	if (line[0] == '\n')
		return (1);
	while (i < 4)
	{
		if (game->texture_path[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

char	**get_texture_path(t_game *game)
{
	char	*line;

	int i = 0;
	game->texture_path = alloc(game->texture_path, 5);
	line = get_next_line(game->mapfd);
	while (line && check_array(game, line))
	{
		if ((i = direction(line)))
			game->texture_path[i - 1] = path(line);
		free(line);
		line = get_next_line(game->mapfd);
	}
	if (line)
		game->start_line = ft_strdup(line);
	game->texture_path[4] = NULL;
	return (game->texture_path);
}

void	get_info(t_game *game)
{
	game->width = 64;
	game->height = 64;
	game->player = malloc(sizeof(t_player));
	game->texture_path = get_texture_path(game);
	game->player->dir = malloc(sizeof(t_dir));
	if (!game->player)
	{
		ft_error(MLX_ERROR);
		exit(FAILURE);
	}
	game->dis = malloc(sizeof(double) * WIDTH);
	game->is_spec = malloc(sizeof(double) * WIDTH);
	game->t_angle = malloc(sizeof(double) * WIDTH);
	game->wallx = malloc(sizeof(double) * WIDTH);
	game->wally = malloc(sizeof(double) * WIDTH);
	game->is_hor = malloc(sizeof(int) * WIDTH);
	game->player->walk_dir = 0;
	game->player->turn_dir = 0;
	game->player->side_dir = 0;
	game->player->move_speed = 4.0;
	game->player->rot_speed = 2.0 * (M_PI / 180);
	game->player->fetch = 0;
	game->off = 0;
	game->mouse_ready = 0;
	game->old_mouse_x = WIDTH / 2;
}

t_game  *init_cub(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (!valid_input(ac, av))
		return (NULL);
	if ((fd = valid_file(av)) == -1)
		return (NULL);
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mapfd = fd;
	get_info(game);
	return (game);
}