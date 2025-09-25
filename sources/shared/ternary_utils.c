/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/24 23:08:40 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ternary_int(int condition, int true_val, int false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}
