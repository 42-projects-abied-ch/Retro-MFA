#ifndef RETRO_H
# define RETRO_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# define KEY_ESC 	65307
# define KEY_LEFT_ARROW 65361
# define KEY_RIGHT_ARROW 65363
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define BUFLEN 44315514  
# define MAX_IMAGES 1024
# define PADDING 10

typedef struct s_imgdata
{
	void			*img;
	char			*addr;
	unsigned char 	*data;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				lines_length;
	int				endian;
}					t_imgdata;

typedef struct s_mfa_image
{
	t_imgdata		color;
	unsigned char	*color_data;
	t_imgdata		alpha;
	unsigned char	*alpha_data;
	int				w;			//width
	int				h;			//height
	int				bpc;		//bytes per color 
}				t_mfaImg;

typedef struct s_img_list
{
	t_imgdata			img;
	struct s_img_list 	*next;
	struct s_img_list 	*prev;
}	t_img_list;

typedef struct		s_surf
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	int			image_count;
	t_mfaImg	images[MAX_IMAGES];
	int			cidx;
	t_img_list*	image_list;
	t_img_list*	current_image;
}					t_surf;

void	display_image(t_surf* data, t_img_list* node);
int		generate_images(t_surf* data);
void	free_images(t_surf *surf, int count);
int		create_trgb(int t, int r, int g, int b);
void	pixel_put(t_imgdata *dt, int x, int y, int color);
int		pixel_get(t_imgdata *data, int x, int y);
int		check_arguments(int argc, char **argv);
int		is_file_invalid(const char *fl);
int		key_press_handler(int keycode, t_surf *surf);
int		init_window(t_surf *surf, t_imgdata *data);
int		parse_images(t_surf *surf, const char *file_name,	unsigned char **patterns, int num_patterns, int bcount);

#endif