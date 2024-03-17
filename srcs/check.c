#include "retro.h"

int		is_file_invalid(const char *fl)
{
	int fd;
	size_t len;
	char buf[5];
	int	sz;

	if (!fl)
		return (1);
	len = strlen(fl);
	if (len < 4 || strcmp(fl + len - 4, ".mfa") != 0)
	{
		printf("\033[1;31mError.\033[0m Invalid file. Must be a .mfa file.\n");	
		return (1);
	}
	fd = open(fl, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[1;31mError.\033[0m Can't open file\n");
		return (1);
	}
	memset(buf, 0, 5);
	sz = read(fd, buf, 4);
	if (sz < 0 || strcmp(buf, "MMF2") != 0)
	{
		close(fd);
		printf("\033[1;31mError.\033[0m Wrong file type. Must be an MFA file.\n");
		return (1);
	}
	close(fd);
	return (0);
}


int	check_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("\033[1;31mError.\033[0m: Wrong number of arguments\n");
		printf("Usage: %s <path_to_image_file_name.mfa>", argv[1]);
		return (1);
	}
	return (0);
}