#include "cub3d.h"

void	nord_img(t_game *game)
{
	game->nord = malloc(sizeof(t_texture));
	game->nord->img = mlx_xpm_file_to_image(game->mlx, game->texture_path[0], &game->width, &game->height);
	game->nord->endian = malloc(sizeof(int));
	game->nord->addr = mlx_get_data_addr(game->nord->img, &game->nord->bpp, &game->nord->line_length, game->nord->endian);
}
void	south_img(t_game *game)
{
	game->south = malloc(sizeof(t_texture));
	game->south->img = mlx_xpm_file_to_image(game->mlx, game->texture_path[1], &game->width, &game->height);
	game->south->endian = malloc(sizeof(int));
	game->south->addr = mlx_get_data_addr(game->south->img, &game->south->bpp, &game->south->line_length, game->nord->endian);
}

void	east_img(t_game *game)
{
	game->east = malloc(sizeof(t_texture));
	game->east->img = mlx_xpm_file_to_image(game->mlx, game->texture_path[2], &game->width, &game->height);
	game->east->endian = malloc(sizeof(int));
	game->east->addr = mlx_get_data_addr(game->east->img, &game->east->bpp, &game->east->line_length, game->east->endian);
}

void	west_img(t_game *game)
{
	game->west = malloc(sizeof(t_texture));
	game->west->img = mlx_xpm_file_to_image(game->mlx, game->texture_path[3], &game->width, &game->height);
	game->west->endian = malloc(sizeof(int));
	game->west->addr = mlx_get_data_addr(game->west->img, &game->west->bpp, &game->west->line_length, game->west->endian);
}

void	load_textures(t_game *game)
{
	nord_img(game);
	south_img(game);
	east_img(game);
	west_img(game);
}