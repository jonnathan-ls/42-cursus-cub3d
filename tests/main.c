/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/13 01:22:36 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "cub3d.h"

int	main(void)
{
	describe("shared/memory-manager", shared_memory_manager_tests);
	check_leaks("leak-check");
	return (0);
}
