#include "retro.h"
#include <mlx.h>

t_imgdata *scale_texture(t_surf* data, t_imgdata *img, int target_width, int target_height)
{
    t_imgdata *scaled_img = malloc(sizeof(t_imgdata));

    scaled_img->img = mlx_new_image(data->mlx, target_width, target_height);
    scaled_img->addr = mlx_get_data_addr(scaled_img->img, &scaled_img->bits_per_pixel, &scaled_img->lines_length, &scaled_img->endian);
    scaled_img->width = target_width;
    scaled_img->height = target_height;

	double scale_x = (double)img->width / target_width;
	double scale_y = (double)img->height / target_height;

    for (int y = 0; y < target_height; y++) 
	{
        for (int x = 0; x < target_width; x++) 
		{
            int x_origin = (int)(x * scale_x);
            int y_origin = (int)(y * scale_y);
            int pixel_color = pixel_get(img, x_origin, y_origin);

            pixel_put(scaled_img, x, y, pixel_color);
        }
    }
    return scaled_img;
}


t_imgdata create_image(t_surf *data, char *path)
{
    t_imgdata img;

    img.img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.lines_length, &img.endian);

    return img;
}

void	fill_images(t_surf* data)
{
	data->images[0].color = create_image(data, "textures/knight.xpm");
	data->images[1].color = create_image(data, "textures/barrel.xpm");
	data->images[2].color = create_image(data, "textures/cake.xpm");
	data->images[3].color = create_image(data, "textures/dead.xpm");
	data->images[4].color = create_image(data, "textures/gun.xpm");
	data->images[5].color = create_image(data, "textures/pnj.xpm");
	data->images[6].color = create_image(data, "textures/scream.xpm");
	data->images[7].color = create_image(data, "textures/skulls.xpm");
}

void	scale_and_position_image(t_surf* data, t_imgdata* img, int target_x, int target_y, int target_width, int target_height)
{
	float original_aspect_ratio = (float)img->width / img->height;
	float target_aspect_ratio = (float)target_width / target_height;
	int scaled_width, scaled_height;
	float scale_factor;

	if (original_aspect_ratio > target_aspect_ratio)
	{
		scaled_width = target_width;
		scale_factor = (float)target_width / img->width;
		scaled_height = img->height * scale_factor;
	}
	else 
	{
		scaled_height = target_height;
		scale_factor = (float)target_height / img->height;
		scaled_width = img->width * scale_factor;
	}
	int offset_x = (target_width - scaled_width) / 2;
	int offset_y = (target_height - scaled_height) / 2;

	int final_x = target_x + offset_x;
	int final_y = target_y + offset_y;
	img = scale_texture(data, img, target_width, target_height);
	mlx_put_image_to_window(data->mlx, data->win, img->img, final_x, final_y);
}

void	display_all_images(t_surf* data, int image_count, int padding)
{
	int aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;
	int columns = round(sqrt((image_count * 2) * aspect_ratio));
	int rows = ceil((float)(image_count * 2) / columns);
	int image_width = (SCREEN_WIDTH - (padding * (columns + 1))) / columns;
	int image_height = (SCREEN_WIDTH - (padding * (rows + 1))) / rows;

	for (int i = 0; i < image_count; i++)
	{
		int row = floor((float)i / columns);
		int column = i % columns;
		int x_pos = (column * (image_width + padding)) + padding;
		int y_pos = (row * (image_height + padding)) + padding;
		scale_and_position_image(data, &data->images[i].color, x_pos, y_pos, image_width, image_height);
	}
}

void	display_full_screen(t_surf* data)
{
	fill_images(data);
	display_all_images(data, 8, 0);
}