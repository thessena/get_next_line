/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:59:47 by thessena          #+#    #+#             */
/*   Updated: 2024/11/20 13:37:53 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("testfile.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error openeing file");
		return (1);
	}
	line = get_next_line(fd) != NULL;
	while (line)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
