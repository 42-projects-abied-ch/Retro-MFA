#ifndef RETRO_H
# define RETRO_H

# include "mlx.h"
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
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define BUFLEN 38315514  
# define MAX_IMAGES 1024

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

typedef struct		s_surf
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	t_mfaImg	images[MAX_IMAGES];
}					t_surf;

int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
// Arthur
void	exit_failure(t_surf* data, char* msg);
int		exit_success(t_surf* data);
void	cleanup_display(t_surf* data);
void	init_mlx(t_surf* data);
void	init_window_arthur(t_surf* data);
void	display_full_screen(t_surf* data);
//Arthur
int		create_trgb(int t, int r, int g, int b);
void	pixel_put(t_imgdata *dt, int x, int y, int color);
int		pixel_get(t_imgdata *data, int x, int y);
int		check_arguments(int argc, char **argv);
int		is_file_invalid(const char *fl);
int		key_press_handler(int keycode, t_surf *surf);
int		key_release_handler(int keycode, t_surf *surf);
int		init_window(t_surf *surf, t_imgdata *data);
int		count_images(const char *file_name,	unsigned char **patterns, int num_patterns, int bcount);
int		parse_images(t_surf *surf, const char *file_name,	unsigned char **patterns, int num_patterns, int bcount);

#endif