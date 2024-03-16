#include "retro.h"

void	pixel_put(t_imgdata *dt, int x, int y, int color)
{
	char	*pos;

	pos = dt->addr + dt->lines_length * y + ((dt->bits_per_pixel / 8) * x);
	*(unsigned int *)pos = color;
}

int		pixel_get(t_imgdata *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->lines_length + x * \
						(data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}