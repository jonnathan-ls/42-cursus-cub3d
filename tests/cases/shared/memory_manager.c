/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/16 22:49:48 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "cub3d.h"

static void	log_fail_alloc(void *received, t_test_result *result)
{
	expect_ptr(received, &"not-null", result, "mm_alloc returned NULL");
}

static void	test_size_correctly_allocated(t_test_result *result)
{
	void	*ptr1;
	void	*ptr2;

	ptr1 = mm_alloc(1, 1);
	ptr2 = mm_alloc(1, 1);
	(void)ptr1;
	(void)ptr2;
	expect_int(mm_nodes_alloc_length(), 2, result,
		"mm_alloc did not track the correct number of allocations");
	mm_garbage_collector();
}

static void	test_memory_manager_allocation(t_test_result *result)
{
	t_test_struct	*test_struct;
	t_test_result	*temp_t_test_result;

	test_struct = mm_alloc(1, sizeof(t_test_struct));
	if (!test_struct)
		return (log_fail_alloc(test_struct, result));
	test_struct->string_property = mm_alloc(10, sizeof(char));
	test_struct->number_property = 42;
	ft_strlcpy(test_struct->string_property, "Test", 10);
	expect_int(test_struct->number_property, 42, result,
		"Incorrect value for 'number_property' field");
	result->next = &(t_test_result){0};
	temp_t_test_result = result->next;
	expect_str(test_struct->string_property, "Test", temp_t_test_result,
		"Incorrect value for 'string_property' field");
	mm_garbage_collector();
}

static void	test_memory_manager_free_allocation(t_test_result *result)
{
	t_test_struct	*test_struct1;
	t_test_struct	*test_struct2;
	t_test_struct	*test_struct3;

	test_struct1 = mm_alloc(1, sizeof(t_test_struct));
	test_struct2 = mm_alloc(10, sizeof(t_test_struct));
	test_struct3 = mm_alloc(10, sizeof(t_test_struct));
	if (!test_struct1)
		return (log_fail_alloc(test_struct1, result));
	if (!test_struct2)
		return (log_fail_alloc(test_struct2, result));
	if (!test_struct3)
		return (log_fail_alloc(test_struct3, result));
	mm_garbage_collector();
	expect_int(mm_nodes_alloc_length(), 0, result,
		"mm_garbage_collector did not free all allocated memory");
}

void	memory_manager_tests(void)
{
	it("Should allocate memory correctly",
		test_memory_manager_allocation);
	it("Should free all allocated memory",
		test_memory_manager_free_allocation);
	it("Should track the correct amount of allocations",
		test_size_correctly_allocated);
}
