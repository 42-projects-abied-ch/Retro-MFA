#include "retro.h"

static int	find_match(char *buffer, int szb, unsigned char *pattern, int szp) 
{
	int i;
	int j;
	int match;
	int count;

	i = 0;
	match = 0;
	count = 0;
	while (i < szb)
	{
		j = 0;
		if (buffer[i] == pattern[j]) 
		{
			match = 1;
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
				count++;
		}
		i++;
	}
	return (count);
}

//usage: count the images in a MFA file
//it users knows header pattern to recognise a part of an image 
//
//arg filename -> name of the file to look
//arg patterns -> a list of byte strings to use for comparing
//arg num_pattern -> how many patterns there are
//arg bcount -> byte count of pattern

int	count_images(const char *file_name,	unsigned char **patterns, int num_patterns, int bcount)
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
				count += find_match(buffer, BUFLEN, patterns[i], bcount);
			}
		}
		memset(&buffer, 0, BUFLEN);
	}
	return (count);
}
