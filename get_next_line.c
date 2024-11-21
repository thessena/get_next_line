/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:25:59 by thessena          #+#    #+#             */
/*   Updated: 2024/11/21 11:58:28 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **remainder)
{
	char	*line;
	char	*new_remainder;
	size_t	line_len;
	size_t	extra_char;

	if (!*remainder || **remainder == '\0')
		return (free(*remainder), *remainder = NULL, NULL);
	line_len = 0;
	while ((*remainder)[line_len] && (*remainder)[line_len] != '\n')
		line_len++;
	extra_char = ((*remainder)[line_len] == '\n');
	line = (char *)malloc((line_len + 1 + extra_char));
	if (!line)
		return (NULL);
	ft_memcpy(line, *remainder, line_len + extra_char);
	line[line_len + extra_char] = '\0';
	new_remainder = ft_strdup(*remainder + line_len + extra_char);
	if (!new_remainder)
		return (free(line), free(*remainder), *remainder = NULL, NULL);
	free(*remainder);
	*remainder = new_remainder;
	return (line);
}

int	read_buffer(int fd, char **remainder, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free(*remainder), *remainder = NULL, bytes_read);
	buffer[bytes_read] = '\0';
	if (!*remainder)
	{
		*remainder = ft_strdup("");
		if (!*remainder)
		{
			free(*remainder);
			*remainder = NULL;
			return (-1);
		}
	}
	temp = ft_strjoin(*remainder, buffer);
	if (!temp)
		return (free(*remainder), *remainder = NULL, -1);
	free(*remainder);
	*remainder = temp;
	return (bytes_read);
}

char	*process_buffer(int fd, char **remainder, char *buffer)
{
	int		bytes_read;
	char	*line;

	bytes_read = read_buffer(fd, remainder, buffer);
	if (bytes_read == -1)
		return (NULL);
	if (bytes_read == 0 && (!remainder || **remainder == '\0'))
		return (NULL);
	if (bytes_read == 0 || ft_strchr(*remainder, '\n'))
	{
		line = extract_line(remainder);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remainder), remainder = NULL, NULL);
	line = NULL;
	while (!line)
	{
		line = process_buffer(fd, &remainder, buffer);
		if (!line && (!remainder || *remainder == '\0'))
		{
			free(buffer);
			free(remainder);
			remainder = NULL;
			return (NULL);
		}
	}
	return (free(buffer), line);
}
