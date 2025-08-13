/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/13 00:51:21 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "cub3d.h"

static void	log_fail_alloc(void *result)
{
	expect_ptr(result, (void *)1, result, "mm_alloc returned NULL");
}

static void	test_memory_manager_allocation(t_test_result *result)
{
	t_test_struct	*test_struct;

	test_struct = mm_alloc(1, sizeof(t_test_struct));
	if (!test_struct)
		return (log_fail_alloc(test_struct));
	test_struct->string_property = mm_alloc(10, sizeof(char));
	test_struct->number_property = 42;
	ft_strlcpy(test_struct->string_property, "Test", 10);
	expect_int(test_struct->number_property, 42, result,
		"Incorrect value for 'number_property' field");
	mm_garbage_collector();
}

static void	test_memory_manager_free_allocation(t_test_result *result)
{
	t_test_struct	*test_struct1;
	t_test_struct	*test_struct2;

	test_struct1 = mm_alloc(1, sizeof(t_test_struct));
	test_struct2 = mm_alloc(10, sizeof(t_test_struct));
	if (!test_struct1)
		return (log_fail_alloc(test_struct1));
	if (!test_struct2)
		return (log_fail_alloc(test_struct2));
	mm_garbage_collector();
	expect_ptr(test_struct1, NULL, result,
		"mm_garbage_collector did not free memory for 'test_struct1'");
	expect_ptr(test_struct2, NULL, result,
		"mm_garbage_collector did not free memory for 'test_struct2'");
}

void	shared_memory_manager_tests(void)
{
	it("Shared", "Allocation", test_memory_manager_allocation);
	it("Shared", "Freeing", test_memory_manager_free_allocation);
}
