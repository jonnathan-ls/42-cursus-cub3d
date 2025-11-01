/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:40 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/01 15:15:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

void	gnl_clear_storage(void)
{
	char	**content;
	int		fd;

	fd = 0;
	content = ft_get_storage();
	while (fd < MAX_FD)
	{
		if (content[fd])
		{
			free(content[fd]);
			content[fd] = NULL;
		}
		fd++;
	}
}

char	*get_next_line(int fd)
{
	char		**content;
	char		*buffer;
	char		*line;
	int			index;

	index = 0;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	content = ft_get_storage();
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	content[fd] = ft_get_content(fd, content[fd], buffer);
	free(buffer);
	if (!content[fd] || content[fd][0] == NULL_CHAR)
		return (NULL);
	line = ft_get_line(content[fd], &index);
	if (!line)
		return (NULL);
	content[fd] = ft_extract_remaining(&content[fd], index);
	return (line);
}
