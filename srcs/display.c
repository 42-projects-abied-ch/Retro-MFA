#include "retro.h"

t_img_list	*new_node(t_imgdata img)
{
	t_img_list*	node = malloc(sizeof(t_img_list));
	if (node == NULL)
	{
		printf("error: allocation failed (display.c:5)\n");
		return NULL;
	}

	node->img = img;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void	add_back(t_img_list** head, t_img_list* new_node)
{
	if (head == NULL || new_node == NULL)
	{
		return ;
	}

	if (*head == NULL)
	{
		*head = new_node;
	}

	else 
	{
		t_img_list* last = *head;

		while (last->next != NULL)
		{
			last = last->next;
		}

		last->next = new_node;
		new_node->prev = last;
	}
}

void put_texture(t_img_list* head, t_imgdata *img, int final_x, int final_y)
{
    for (int y = final_y; y < img->height + final_y; y++) 
	{
        for (int x = final_x; x < img->width + final_x; x++)
		{
            int pixel_color = pixel_get(img, x - final_x, y - final_y);

            pixel_put(&head->img, x, y, pixel_color);
        }
    }
}

int	expand_list(t_surf* data, t_img_list** head)
{
	t_imgdata new_image;

	(void)data;
	new_image.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (new_image.img == NULL)
	{
		printf("error: allocation failed (display.c:63)\n");
		return EXIT_FAILURE;
	}
	new_image.addr = mlx_get_data_addr(new_image.img, &new_image.bits_per_pixel, &new_image.lines_length, &new_image.endian);

	t_img_list* node = new_node(new_image);
	if (node == NULL)
	{
		mlx_destroy_image(data->mlx, new_image.img);
		return EXIT_FAILURE;
	}

	add_back(head, node);

	return EXIT_SUCCESS;
}

int	draw_sprites_to_images(t_surf* data, t_img_list** head)
{
	t_img_list* current_image = *head;

	int current_image_y = 0 + PADDING;
	int	max_height_on_row = 0;
	int	right_most_pos_on_row = 0;

	for (int i = 0; i < data->image_count; i++)
	{
		int current_image_x = right_most_pos_on_row + PADDING;
		if (current_image_x + data->images[i].color.width > SCREEN_WIDTH - PADDING)
		{
			current_image_x = 0 + PADDING;
			current_image_y += max_height_on_row + PADDING;
			right_most_pos_on_row = 0;
			max_height_on_row = 0;
		}
		if (current_image_y + data->images[i].color.height > SCREEN_HEIGHT - PADDING)
		{
			if (expand_list(data, head) == EXIT_FAILURE)
			{
				return EXIT_FAILURE;
			}
			current_image = current_image->next;
			current_image_y = 0 + PADDING;
			right_most_pos_on_row = 0;
			max_height_on_row = 0;
			continue ;
		}
		put_texture(current_image, &data->images[i].color, current_image_x, current_image_y);
		max_height_on_row = fmax(max_height_on_row, data->images[i].color.height);
		right_most_pos_on_row = current_image_x + data->images[i].color.width;
	}
	return EXIT_SUCCESS;
}

int	initialize_image_list(t_surf* data)
{
	t_imgdata img;

	img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (img.img == NULL)
	{
		printf("error: image allocation failed (display.c:124)\n");
		return EXIT_FAILURE;
	}

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.lines_length, &img.endian);

	data->image_list = new_node(img);
	if (data->image_list == NULL)
	{
		mlx_destroy_image(data->mlx, img.img);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int		generate_images(t_surf* data)
{
	if (data->image_list != NULL)
	{
		return 0;
	}

	if (initialize_image_list(data) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	if (draw_sprites_to_images(data, &data->image_list) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	data->current_image = data->image_list;

	return 0;
}

void	display_image(t_surf* data, t_img_list* node)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, node->img.img, 0, 0);
}