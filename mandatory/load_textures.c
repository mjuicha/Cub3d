#include "cub3d.h"

void	free_imgs(t_game *game)
{
	free_img(game->img_win);
	if (game->alloc_bool->n)
		free_img(game->nord);
	if (game->alloc_bool->s)
		free_img(game->south);
	if (game->alloc_bool->e)
		free_img(game->east);
	if (game->alloc_bool->w)
		free_img(game->west);
}

t_texture	*texture_img(t_game *game, char *path)
{
	t_texture *texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		game_free(game, MALLOC_ERROR);
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &game->width, &game->height);
	if (!texture->img)
	{
		free(texture);
		game_free(game, MALLOC_ERROR);
	}
	texture->endian = malloc(sizeof(int));
	if (!texture->endian)
	{
		free(texture);
		game_free(game, MALLOC_ERROR);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_length, texture->endian);
	if (!texture->addr)
	{
		free_img(texture);
		free_imgs(game);
		game_free(game, MALLOC_ERROR);
	}
	return (texture);
}

void	load_textures(t_game *game)
{
	game->nord = texture_img(game, game->texture_path[0]);
	game->alloc_bool->n = true;
	game->south = texture_img(game, game->texture_path[1]);
	game->alloc_bool->s = true;
	game->east = texture_img(game, game->texture_path[2]);
	game->alloc_bool->e = true;
	game->west = texture_img(game, game->texture_path[3]);
	game->alloc_bool->w = true;
}
