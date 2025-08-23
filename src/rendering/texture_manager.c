#include "../../includes/cub3d.h"

int load_texture(t_game *game, char *path, int texture_index)
{
    game->textures[texture_index] = mlx_xpm_file_to_image(game->mlx, path,
        &game->tex_width[texture_index], &game->tex_height[texture_index]);

    if (!game->textures[texture_index])
    {
        printf("Error\nFailed to load texture: %s\n", path);
        return (0);
    }

    game->tex_data[texture_index] = mlx_get_data_addr(game->textures[texture_index],
        &game->tex_bpp[texture_index], &game->tex_line_len[texture_index],
        &game->tex_endian[texture_index]);

    if (!game->tex_data[texture_index])
    {
        printf("Error\nFailed to get texture data\n");
        return (0);
    }

    printf("Texture %d loaded: %dx%d from %s\n",
        texture_index, game->tex_width[texture_index],
        game->tex_height[texture_index], path);
    return (1);
}

int get_texture_pixel(t_game *game, int texture_index, int x, int y)
{
    int pixel_index;
    int color;

    if (x < 0 || x >= game->tex_width[texture_index] ||
        y < 0 || y >= game->tex_height[texture_index])
        return (0);

    pixel_index = (y * game->tex_line_len[texture_index]) +
                  (x * (game->tex_bpp[texture_index] / 8));

    color = *(int*)(game->tex_data[texture_index] + pixel_index);

    return (color & 0xFFFFFF);
}
