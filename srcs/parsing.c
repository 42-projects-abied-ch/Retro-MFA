
#include "retro.h"

void	free_images(t_surf *surf, int count)
{
	for (int i = 0; i < count; i++)
	{
		mlx_destroy_image(surf->mlx, surf->images[i].color.img);
		free(surf->images[i].color_data);
	}
}

static int	find_images(int fd,
						t_surf *surf,
						unsigned char *buffer,
						int szb, 		// size of buffer
						unsigned char *pattern, 
						int szp)		// size of pattern (character number count) 
{
	(void)fd;
	int i = 0, j, match = 0, match_pos = -1;
	static int index = 0;
	while (i < szb)
	{
		j = 0;
		if (buffer[i] == pattern[j]) 
		{
			match = 1;
			match_pos = i;
			j = 1;
			while (j < szp) 
			{
				if (buffer[i + j] != pattern[j] || (i + j > szb))
				{
					match = 0;
					break ;
				}
				j++;
			}
			if (match == 1)
			{
				surf->images[index].bpc = (buffer[i] == 4) ? 3 : 2;
				unsigned char dimensions[5] = {0};
				for (int k = 0; k < 4; k++)
					dimensions[k] = buffer[match_pos - (4 - k)];
				surf->images[index].w = dimensions[0] + (dimensions[1] << 8);
				surf->images[index].h = dimensions[2] + (dimensions[3] << 8);
				if (surf->images[index].w <= 0 || surf->images[index].h <= 0 ||
					surf->images[index].w > 400 || surf->images[index].h > 400)
				{
					i++;
					continue ;
				}
				int size;
				if (surf->images[index].bpc == 2 || (surf->images[index].w % 2 == 0))
				 	size = surf->images[index].w * surf->images[index].h * surf->images[index].bpc;
				else
					size = ((surf->images[index].w + 1) * surf->images[index].h) * 3;
				surf->images[index].color_data = malloc(size);
				if (!surf->images[index].color_data)
				{
					printf("Error allocating with malloc.\n");
					return -1;
				}
				for (int k = 0; k < size; k++)
				{
					surf->images[index].color_data[k] = buffer[match_pos + 16 + k];
				}
				i += size;
				surf->images[index].color.img = mlx_new_image(surf->mlx, 
														surf->images[index].w,
														surf->images[index].h);

				if (!surf->images[index].color.img)
				{
					printf("Error creating mlx image.\n");
					free(surf->images[index].color_data);
					free_images(surf, index);
					return -1;
				}
				surf->images[index].color.width = surf->images[index].w;
				surf->images[index].color.height = surf->images[index].h; 
				surf->images[index].color.addr = mlx_get_data_addr(surf->images[index].color.img, 
														&surf->images[index].color.bits_per_pixel,
														&surf->images[index].color.lines_length,
														&surf->images[index].color.endian);
				int col_idx = 0;
				for (int y = 0; y < surf->images[index].h; y++)
				{
					for (int x = 0; x < surf->images[index].w; x++)
					{
						if (surf->images[index].bpc == 2)
						{
							int value = surf->images[index].color_data[col_idx] + 
												(surf->images[index].color_data[col_idx + 1] << 8);
							int red = (value >> 10) & 0x1F; 
							int green = (value >> 5) & 0x1F;
							int blue = value & 0x1F; 
							int col = red << 19 | green << 11 | blue << 3;
							pixel_put(&surf->images[index].color, x, y, col);				
							col_idx += 2;
						}
						if (surf->images[index].bpc == 3)
						{
							int value = surf->images[index].color_data[col_idx ] + 
										(surf->images[index].color_data[col_idx + 1] << 8) +
										(surf->images[index].color_data[col_idx + 2] << 16);
							pixel_put(&surf->images[index].color, x, y, value);
							col_idx += 3;
							if (x == (surf->images[index].w - 1)  && (surf->images[index].w % 2 == 1))
								col_idx += 3;
						}
					}
				}
				index++;
			}
		}
		i++;
	}
	return (index) ;
}

int	parse_images(t_surf *surf,
				const char *file_name,	
				unsigned char **patterns,
				int num_patterns,
				int bcount)
{
	int 	fd;
	int		ret;
	unsigned char	*buffer;;
	int		count;

	count = 0;
	buffer = malloc(sizeof(unsigned char) * BUFLEN);
	if (!buffer)
	{
		printf("Error. Main buffer malloc error.\n");
		return -1;
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		free(buffer);
		printf("Error opening file.\n");
		return (-1);
	}
	ret = read(fd, buffer, BUFLEN);
	if (ret < 0)
	{
		free(buffer);
		close(fd);
		printf("Error reading file.\n");
		return (-1);
	}
	else if (ret == 0)
	{
		printf("Error. file empty.\n");
		free(buffer);
		close(fd);
		return (-1);
	}
	else
	{
		for (int i = 0; i < num_patterns; i++)
		{
			int n = find_images(fd, surf, buffer, ret, patterns[i], bcount);	
			if (n < 0)
			{
				free(buffer);
				close(fd);
				printf("Error finding images.\n");
				return -1;
			}
			count = n;		
		}
	}
	free(buffer);
	close(fd);
	return (count);
}