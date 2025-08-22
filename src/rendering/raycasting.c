#include "../../includes/cub3d.h"

void	cast_dda_ray(t_game *game, double rayDirX, double rayDirY, int x)
{
    //which box of the map we're in
    int mapX = (int)(game->player.pos_x / TILE_SIZE);
    int mapY = (int)(game->player.pos_y / TILE_SIZE);

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    //calculate step and initial sideDist
    double posX = game->player.pos_x / TILE_SIZE;
    double posY = game->player.pos_y / TILE_SIZE;

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    //perform DDA
    while (hit == 0)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        //Check if ray has hit a wall
        if (mapX < 0 || mapY < 0 || !game->map[mapY] || !game->map[mapY][mapX] || game->map[mapY][mapX] == '1')
            hit = 1;
    }

    //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if(side == 0)
        perpWallDist = (sideDistX - deltaDistX);
    else
        perpWallDist = (sideDistY - deltaDistY);

    //Calculate height of line to draw on screen
    int lineHeight = (int)(HEIGHT / perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if(drawStart < 0)
		drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if(drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;

    //choose wall color (comme le tutoriel)
    int color = 255; // blanc par défaut

    //give x and y sides different brightness
    if (side == 1) color = color / 2;

    //draw the pixels of the stripe as a vertical line
    for(int y = drawStart; y < drawEnd; y++)
        put_pixel(game, x, y, color);
}
