/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:40 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/01 15:15:02 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# define NEW_LINE '\n'
# define NULL_CHAR '\0'
# define EMPTY_STRING ""

void	gnl_clear_storage(void);
char	*get_next_line(int fd);
char	**ft_get_storage(void);
char	*ft_get_line(char *content, int *index);
char	*ft_extract_remaining(char **content, int index);
char	*ft_get_content(int fd, char *content, char *buffer);

#endif
