
#include "retro.h"

static int	find_images(int fd,
						t_surf *surf,
						char *buffer,
						int szb,
						unsigned char *pattern,
						int szp) 
{
	int i = 0, j, match = 0, match_pos = -1;
	static int count = 0;
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
					match_pos = -1;
					break ;
				}
				j++;
			}
			if (match == 1)
			{
				char dimensions[4];
				lseek(fd, match_pos - 4, SEEK_SET);
				if (read(fd, &dimensions, 4) < 0)
				{
					printf("Error reading file.\n");
					return -1;
				}
				surf->images[count].w = dimensions[0] + (dimensions[1] << 8);
				surf->images[count].h = dimensions[2] + (dimensions[3] << 8);
			}
		}
		i++;
	}
	return (count);
}

int	parse_images(t_surf *surf,
				const char *file_name,	
				unsigned char **patterns,
				int num_patterns,
				int bcount)
{
	int 	fd;
	int		ret;
	char	buffer[BUFLEN];
	int		count;

	count = 0;
	memset(&buffer, 0, BUFLEN);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file."), -1);
	while(1)
	{
		ret = read(fd, buffer, BUFLEN);
		if (ret < 0)
			return (perror("Error reading file."), -1);
		else if (ret == 0)
			return (close(fd), count);
		else
		{
			for (int i = 0; i < num_patterns; i++)
			{
				count += find_images(fd, surf, buffer, BUFLEN, patterns[i], bcount);	
			}
		}
		memset(&buffer, 0, BUFLEN);
	}
	close(fd);
	return (count);
}