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

    // Calculate wallX (où exactement le rayon touche le mur)
    double wallX;
    if (side == 0)
        wallX = posY + perpWallDist * rayDirY;
    else
        wallX = posX + perpWallDist * rayDirX;
    wallX -= floor(wallX);  // Garde seulement la partie décimale

	// Déterminer la texture selon la direction du mur touché
	int texNum;
	if (side == 0) // Mur vertical (Nord/Sud)
	{
		if (rayDirX > 0)
			texNum = 2; // East (on regarde vers l'est, mur est à l'est)
		else
			texNum = 3; // West (on regarde vers l'ouest, mur est à l'ouest)
	}
	else // Mur horizontal (Est/Ouest)
	{
		if (rayDirY > 0)
			texNum = 1; // South (on regarde vers le sud, mur est au sud)
		else
			texNum = 0; // North (on regarde vers le nord, mur est au nord)
	}
    int texX = (int)(wallX * game->config.textures[texNum].width);

    // Ajuster texX selon direction pour éviter les miroirs
    if (side == 0 && rayDirX > 0)
        texX = game->config.textures[texNum].width - texX - 1;
    if (side == 1 && rayDirY < 0)
        texX = game->config.textures[texNum].width - texX - 1;

    //Calculate height of line to draw on screen
    int lineHeight = (int)(HEIGHT / perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if(drawStart < 0)
		drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if(drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;

	// Calcul du pas de texture (step) et position de départ
	double step = 1.0 * game->config.textures[texNum].height / lineHeight;
	double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

	for(int y = drawStart; y < drawEnd; y++)
	{
		// Cast de la coordonnée de texture en entier
		int texY = (int)texPos;
		if (texY >= game->config.textures[texNum].height)
			texY = game->config.textures[texNum].height - 1;
		if (texY < 0)
			texY = 0;
		texPos += step;

		// Récupérer la couleur du pixel de texture
		int color = get_texture_pixel(game, texNum ,texX, texY);

		// Assombrir les côtés Y pour l'effet d'éclairage
		if(side == 1)
			color = (color >> 1) & 8355711; // Divise RGB par 2

		put_pixel(game, x, y, color);
	}
	for (int y = 0; y < drawStart; y++)
		put_pixel(game, x, y, game->config.ceiling_color);
	for (int y = drawEnd; y < HEIGHT; y++)
		put_pixel(game, x, y, game->config.floor_color);
}
