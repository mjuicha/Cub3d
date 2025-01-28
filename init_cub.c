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

int	valid_format(t_game *game)
{
	(void)game;
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

void	get_info(t_game *game)
{
	game->width = 48;
	game->height = 48;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		ft_error(MLX_ERROR);
		exit(FAILURE);
	}
	game->player->walk_dir = 0;
	game->player->turn_dir = 0;
	game->player->side_dir = 0;
	game->player->move_speed = 2.0;
	game->player->rot_speed = 10.0 * (M_PI / 180);
	game->player->angle = -M_PI / 2;
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
	if (!valid_format(game))
		return (NULL);
	get_info(game);
	return (game);
}