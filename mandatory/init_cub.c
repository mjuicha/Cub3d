#include "cub3d.h"

void	ft_error(char *error)
{
	if (!error)
		return ;
	ft_putendl_fd(error, STDERR_FILENO);
}

void	auto_free(t_game *game)
{
	if (game->alloc_bool->m_dir)
		free(game->player->dir);
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
	free(game->alloc_bool);
	free(game);
}

void	leaks(void)
{
	system("leaks cub3D");
}
void	auto_exit(t_game *game, char *error)
{
	ft_error(error);
	auto_free(game);
	// atexit(leaks);
	if (!error)
		exit(SUCCESS);
	exit(FAILURE);
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
		if (!(game->map[i][j - 1]) || !(game->map[i][j + 1]) || !(game->map[i - 1][j]) || !(game->map[i + 1][j]))
			return (FAILURE);
		if (game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' ' || game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ')
			return (SUCCESS);
	}
	else
		return (SUCCESS);
	return (FAILURE);
}

int check_open_spaces(t_game *game)
{
	int i = 1;
	int j = 1;

	char *line = game->map[i];
	while (i < game->mapcounter - 1)
	{
		j = 1;
		while (line[j])
		{
			if (find_open_space(line[j], i , j, game))
				return (FAILURE);
			j++;
		}
		i++;
		line = game->map[i];
	}
	return (SUCCESS);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->mapcounter || y >= (int)ft_strlen(game->map[x]))
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

void	free_map(t_game *game)
{
	int i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	game_free(t_game *game, char *error)
{
	free_map(game);
	free_imgs(game);
	mlx_free(game, error);
}

int	valid_format(t_game *game)
{
	if (!check_edges(game) || !check_valid_char(game) ||!check_open_spaces(game))
	{
		game_free(game, MAP_ERROR);
		return (FAILURE);
	}
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

void	free_path(t_game *game)
{
	int i = 0;
	while (i < 4)
	{
		if (game->texture_path[i])
			free(game->texture_path[i]);
		i++;
	}
	free(game->texture_path);
	if (game->start_line)
    	free(game->start_line);
}

void	get_color(char *line, t_game *game, int c)
{
	int i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && (line[i] == 'F' || line[i] == 'C'))
		i += 2;
	int r = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	int g = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	int b = ft_atoi(line + i);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(line);
		free_path(game);
		auto_exit(game, COLOR_ERROR);
	}
	int color = (r << 16) + (g << 8) + b;
	if (c == 'F')
		game->floor = color;
	else
		game->ceiling = color;
}

int	direction(char *line, t_game *game)
{
	if (ft_strchr2(line, "NO"))
		return (1);
	if (ft_strchr2(line, "SO"))
		return (2);
	if (ft_strchr2(line, "WE"))
		return (3);
	if (ft_strchr2(line, "EA"))
		return (4);
	if (ft_strchr2(line, "F "))
		get_color(line, game, 'F');
	if (ft_strchr2(line, "C "))
		get_color(line, game, 'C');
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
	while (line[i] == ' ')
		i++;
	if (direction(line + i, NULL))
		i += 2;
	while (line[i] == ' ')
		i++;
	return (i);
}


char	*path(t_game *game, char *line)
{
	int i = 0;
	i = skip(line);
	int alloc = 0;
	while (line[i + alloc] && !(line[i + alloc] == ' '))
		alloc++;
	char *path = malloc(sizeof(char) * (alloc));
	if (!path)
	{
		free_path(game);
		auto_exit(game, MALLOC_ERROR);
	}
	int j = 0;
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
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		auto_exit(NULL, MALLOC_ERROR);
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
	if (line[0] == '\n' || ft_strchr2(line, "F ") || ft_strchr2(line, "C "))
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
		if ((i = direction(line, game)))
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

void	set_alloc()
{}

void	alloc_vars(t_game *game)
{
	if (!(game->player = malloc(sizeof(t_player))))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_player = 1;
	if (!(game->player->dir = malloc(sizeof(t_dir))))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_dir = 1;
	if (!(game->dis = malloc(sizeof(double) * WIDTH)))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_dis = 1;
	if (!(game->is_spec = malloc(sizeof(double) * WIDTH)))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_is_spec = 1;
	if (!(game->t_angle = malloc(sizeof(double) * WIDTH)))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_t_angle = 1;
	if (!(game->wallx = malloc(sizeof(double) * WIDTH)))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_wallx = 1;
	if (!(game->wally = malloc(sizeof(double) * WIDTH)))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_wally = 1;
	if (!(game->is_hor = malloc(sizeof(int) * WIDTH)))
		return (auto_exit(game, MALLOC_ERROR));
	game->alloc_bool->m_is_hor = 1;
}

void	get_info(t_game *game)
{
	game->width = TILE_SIZE;
	game->height = TILE_SIZE;
	alloc_vars(game);
	game->texture_path = get_texture_path(game);
	game->player->walk_dir = 0;
	game->player->turn_dir = 0;
	game->player->side_dir = 0;
	game->player->move_speed = 4.0;
	game->player->rot_speed = 2.0 * (M_PI / 180);
	game->off = 0;
}

void	init_bool(t_game *game)
{
	game->alloc_bool->m_player = 0;
	game->alloc_bool->m_dir = 0;
	game->alloc_bool->m_dis = 0;
	game->alloc_bool->m_is_spec = 0;
	game->alloc_bool->m_t_angle = 0;
	game->alloc_bool->m_wallx = 0;
	game->alloc_bool->m_wally = 0;
	game->alloc_bool->m_is_hor = 0;
	game->alloc_bool->m_fd = 1;
	game->alloc_bool->n = 0;
	game->alloc_bool->s = 0;
	game->alloc_bool->e = 0;
	game->alloc_bool->w = 0;
}

t_game	*init_cub(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (!valid_input(ac, av))
		return (FAILURE);
	if ((fd = valid_file(av)) == -1)
		return (FAILURE);
	game = malloc(sizeof(t_game));
	if (!game)
	{
		close(fd);
		return (NULL);
	}
	game->mapfd = fd;
	game->alloc_bool = malloc(sizeof(t_alloc));
	if (!game->alloc_bool)
	{
		close(fd);
		free(game);
		return (NULL);
	}
	init_bool(game);
	get_info(game);
	return (game);
}