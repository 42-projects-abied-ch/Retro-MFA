#include "retro.h"

int	key_press_handler(int keycode, t_surf *surf)
{	
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(surf->mlx);
		return (0);
	}
	if (keycode == KEY_LEFT_ARROW)
	{
		if (surf->current_image->prev != NULL)
		{
			surf->current_image = surf->current_image->prev;
			display_image(surf, surf->current_image);
		}
	}
	if (keycode == KEY_RIGHT_ARROW && surf->cidx < surf->image_count - 1)
	{
		if (surf->current_image->next != NULL)
		{
			surf->current_image = surf->current_image->next;
			display_image(surf, surf->current_image);
		}
	}
	return (0);
}
