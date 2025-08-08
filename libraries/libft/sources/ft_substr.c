/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:43:57 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/07 23:29:32 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_substr_len(unsigned int start, size_t len, size_t s_len)
{
	if (start > s_len)
		return (0);
	else if (start + len > s_len)
		return (s_len - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	substr_len = ft_get_substr_len(start, len, s_len);
	substr = (char *)malloc(substr_len + 1);
	if (substr)
	{
		while (i < len && start + i < s_len)
		{
			substr[i] = s[start + i];
			i++;
		}
		substr[i] = '\0';
	}
	return (substr);
}
