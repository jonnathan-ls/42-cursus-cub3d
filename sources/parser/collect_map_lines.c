/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:13 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/30 08:46:24 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

/**
 * @brief Grows the lines array to accommodate one more element.
 *
 * Allocates a new array with space for one additional line, copies
 * existing pointers, and frees the old array.
 *
 * @param old Current lines array.
 * @param old_count Number of lines in the current array.
 * @return New array on success, NULL on failure.
 */
static char	**grow_lines(char **old, int old_count)
{
	char	**new_arr;
	int		i;

	new_arr = (char **)ft_calloc(old_count + 2, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_arr[i] = old[i];
		i = i + 1;
	}
	free(old);
	return (new_arr);
}

/**
 * @brief Removes trailing newline character from a string.
 *
 * Checks if the last character of the string is a newline and replaces
 * it with a null terminator.
 *
 * @param line String to strip.
 */
static void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/**
 * @brief Appends a line to the lines array.
 *
 * Strips the trailing newline from the line, grows the array to
 * accommodate the new line, and appends it to the array.
 *
 * @param lines Pointer to the lines array.
 * @param count Pointer to the line count.
 * @param line Line to append.
 * @return 0 on success, -1 on failure.
 */
static int	append_line(char ***lines, int *count, char *line)
{
	char	**tmp;

	strip_newline(line);
	tmp = grow_lines(*lines, *count);
	if (!tmp)
	{
		free(line);
		return (parser_error("malloc failure"));
	}
	*lines = tmp;
	(*lines)[(*count)++] = line;
	return (0);
}

/**
 * @brief Reads additional map lines from file until blank line.
 *
 * Continuously reads lines from the file descriptor, appending each
 * non-empty line to the lines array. Stops on blank line or EOF.
 *
 * @param fd File descriptor to read from.
 * @param lines Pointer to the lines array.
 * @param count Pointer to the line count.
 * @return 0 on success, -1 on failure.
 */
static int	read_more(int fd, char ***lines, int *count)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		if (line[0] == '\n')
		{
			free(line);
			return (0);
		}
		if (append_line(lines, count, line) < 0)
			return (-1);
	}
	return (0);
}

/**
 * @brief Collects all map lines into a raw map structure.
 *
 * Initializes the lines array, appends the first map line, then reads
 * additional lines from the file. Populates the map structure with the
 * collected grid and dimensions.
 *
 * @param fd File descriptor to read from.
 * @param first_map_line First line of the map.
 * @param map_raw Map structure to populate.
 * @return 0 on success, -1 on failure.
 */
int	collect_map(int fd, char *first_map_line, t_map *map_raw)
{
	char	**lines;
	int		count;

	count = 0;
	lines = grow_lines(NULL, 0);
	if (!lines)
		return (parser_error("malloc failure"));
	strip_newline(first_map_line);
	lines[count++] = first_map_line;
	if (read_more(fd, &lines, &count) < 0)
		return (-1);
	if (count == 0)
	{
		free(lines);
		return (parser_error("empty map"));
	}
	map_raw->grid = lines;
	map_raw->height = count;
	map_raw->width = 0;
	return (0);
}
