/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:25:59 by thessena          #+#    #+#             */
/*   Updated: 2024/11/20 13:46:34 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **remainder)
{
	char	*line;
	char	*new_remainder;
	size_t	line_len;
	size_t	extra_char;

	line_len = 0;
	while ((*remainder)[line_len] && (*remainder)[line_len] != '\n')
		line_len++;
	extra_char = ((*remainder)[line_len] == '\n');
	line = (char *)malloc((line_len + 1 + extra_char) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, *remainder, line_len + ((*remainder)[line_len] == '\n'));
	line[line_len + ((*remainder)[line_len] == '\n')] = '\0';
	new_remainder = ft_strdup(*remainder + line_len + extra_char);
	free(*remainder);
	*remainder = new_remainder;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = 0;
	if (remainder && ft_strchr(remainder, '\n'))
	{
		return (line);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
		{
			free(buffer);
			return (line);
		}
	}
	free (buffer);
	if (bytes_read == 0 && remainder)
		return (NULL);
	return (line);
}
