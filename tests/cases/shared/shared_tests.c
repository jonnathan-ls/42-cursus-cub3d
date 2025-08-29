/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/28 21:26:09 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	shared_tests_cases(void)
{
	describe("Shared > Memory Manager", memory_manager_tests);
}
