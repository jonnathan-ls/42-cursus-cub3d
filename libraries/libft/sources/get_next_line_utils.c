/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:40 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/01 15:13:14 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char	**ft_get_storage(void)
{
	static char	*content[MAX_FD];

	return (content);
}

char	*ft_get_content(int fd, char *content, char *buffer)
{
	char	*temp;
	int		bytes_read;

	if (!content)
		content = ft_strdup(EMPTY_STRING);
	if (!content)
		return (NULL);
	while (!ft_strchr(content, NEW_LINE))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(content);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = NULL_CHAR;
		temp = content;
		content = ft_strjoin(content, buffer);
		free(temp);
		if (!content)
			return (NULL);
	}
	return (content);
}

char	*ft_get_line(char *content, int *index)
{
	char	*line;

	while (content[*index] && content[*index] != NEW_LINE)
		(*index)++;
	if (content[*index] && content[*index] == NEW_LINE)
		(*index)++;
	line = ft_substr(content, 0, *index);
	if (!line)
	{
		free(content);
		return (NULL);
	}
	return (line);
}

char	*ft_extract_remaining(char **content, int index)
{
	char	*temp;
	char	*remaining;

	temp = *content;
	remaining = ft_strdup(*content + index);
	free(temp);
	if (remaining && remaining[0] == NULL_CHAR)
	{
		free(remaining);
		remaining = NULL;
	}
	return (remaining);
}
