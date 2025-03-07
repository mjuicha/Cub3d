#include "cub3d.h"

void get_img(t_game *game);
void get_img2(t_game *game);

void	get_img3(t_game *game)
{
	game->red_wall = mlx_xpm_file_to_image(game->mlx, game->texture_path[2], &game->width, &game->height);

	game->endian3 = malloc(sizeof(int));
	game->addr3 = mlx_get_data_addr(game->red_wall, &game->bpp3, &game->line_length3, game->endian3);
}

void	get_img4(t_game *game)
{
	game->grey_wall = mlx_xpm_file_to_image(game->mlx, game->texture_path[3], &game->width, &game->height);
	game->endian4 = malloc(sizeof(int));
	game->addr4 = mlx_get_data_addr(game->grey_wall, &game->bpp4, &game->line_length4, game->endian4);
}

void	get_door(t_game *game)
{
	game->door = mlx_xpm_file_to_image(game->mlx, game->texture_path[4], &game->width, &game->height);
	game->endian5 = malloc(sizeof(int));
	game->addr5 = mlx_get_data_addr(game->door, &game->bpp5, &game->line_length5, game->endian5);
}

void	sprites_img(t_game *game)
{
	int width = 250;
	int height = 222;
	game->sprite = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/Sgun.xpm", &width, &height);
	game->endian00 = malloc(sizeof(int));
	game->addr00 = mlx_get_data_addr(game->sprite, &game->bpp00, &game->line_length00, game->endian00);
	game->sprite1 = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/c1.xpm", &width, &height);
	game->endian01 = malloc(sizeof(int));
	game->addr01 = mlx_get_data_addr(game->sprite, &game->bpp01, &game->line_length01, game->endian01);
	game->sprite2 = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/c2.xpm", &width, &height);
	game->endian02 = malloc(sizeof(int));
	game->addr02 = mlx_get_data_addr(game->sprite, &game->bpp02, &game->line_length02, game->endian02);
	game->sprite3 = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/c3.xpm", &width, &height);
	game->endian03 = malloc(sizeof(int));
	game->addr03 = mlx_get_data_addr(game->sprite, &game->bpp03, &game->line_length03, game->endian03);
	game->sprite4 = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/c4.xpm", &width, &height);
	game->endian04 = malloc(sizeof(int));
	game->addr04 = mlx_get_data_addr(game->sprite, &game->bpp04, &game->line_length04, game->endian04);
	game->sprite5 = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/c5.xpm", &width, &height);
	game->endian05 = malloc(sizeof(int));
	game->addr05 = mlx_get_data_addr(game->sprite, &game->bpp05, &game->line_length05, game->endian05);
	game->sprite6 = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/c6.xpm", &width, &height);
	game->endian06 = malloc(sizeof(int));
	game->addr06 = mlx_get_data_addr(game->sprite, &game->bpp06, &game->line_length06, game->endian06);
	game->warning = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/warning.xpm", &width, &height);
	game->endian07 = malloc(sizeof(int));
	game->addr07 = mlx_get_data_addr(game->sprite, &game->bpp07, &game->line_length07, game->endian07);
	game->aim = mlx_xpm_file_to_image(game->mlx, "xpm_files/gun/aim.xpm", &width, &height);
	game->endian08 = malloc(sizeof(int));
	game->addr08 = mlx_get_data_addr(game->sprite, &game->bpp08, &game->line_length08, game->endian08);
	game->sky = mlx_xpm_file_to_image(game->mlx, "xpm_files/sky.xpm", &width, &height);
	game->endian09 = malloc(sizeof(int));
	game->addr09 = mlx_get_data_addr(game->sky, &game->bpp09, &game->line_length09, game->endian09);
	game->red = mlx_xpm_file_to_image(game->mlx, "xpm_files/red.xpm", &width, &height);
	game->endian6 = malloc(sizeof(int));
	game->addr6 = mlx_get_data_addr(game->red, &game->bpp6, &game->line_length6, game->endian6);
	game->brown = mlx_xpm_file_to_image(game->mlx, "xpm_files/brown.xpm", &width, &height);
	game->endianm3 = malloc(sizeof(int));
	game->addrm3 = mlx_get_data_addr(game->brown, &game->bppm3, &game->line_lengthm3, game->endianm3);
	game->green = mlx_xpm_file_to_image(game->mlx, "xpm_files/green.xpm", &width, &height);
	game->endianm2 = malloc(sizeof(int));
	game->addrm2 = mlx_get_data_addr(game->green, &game->bppm2, &game->line_lengthm2, game->endianm2);
	game->blue = mlx_xpm_file_to_image(game->mlx, "xpm_files/blue.xpm", &width, &height);
	game->endianm1 = malloc(sizeof(int));
	game->addrm1 = mlx_get_data_addr(game->red, &game->bppm1, &game->line_lengthm1, game->endianm1);
	game->ground = mlx_xpm_file_to_image(game->mlx, "xpm_files/floor.xpm", &width, &height);
	game->endiang0 = malloc(sizeof(int));
	game->addrg0 = mlx_get_data_addr(game->ground, &game->bppg0, &game->line_lengthg0, game->endiang0);
}

int	main(int ac, char **av)
{
	t_game  *game;

	game = init_cub(ac, av);
    start_game(game);
	get_img(game);
	get_img2(game);
	get_img3(game);
	get_img4(game);
	get_door(game);
	game->set = 0;
	sprites_img(game);
	events_hook(game);
	mlx_loop_hook(game->mlx, render_game, game);
    mlx_loop(game->mlx);
	return (0);
}
  