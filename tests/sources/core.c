/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/16 22:25:03 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

/**
 * Print the result of a test case.
 * @param test The name of the test case.
 * @param result The result of the test case.
 */
static void	check_if_it_passed(t_test_result *result)
{
	if (!result->passed)
	{
		printf(BOLD YELLOW "    %s\n" RESET, result->fail_reason);
		printf(LIGHT_RED "    Received: %s\n" RESET, result->received);
		printf(CYAN "    Expected: %s\n" RESET, result->expected);
	}
}

/**
 * Process a test suite.
 * @param suite The name of the test suite.
 * @param function The cases to run.
 */
void	describe(const char *suite, void (*function)(void))
{
	printf(BLUE BOLD EMOJI_DESCRIBE
		"  %s" RESET "\n", suite);
	function();
	printf("\n");
}

/**
 * Process a test case.
 * @param test The name of the test case.
 * @param function The test function to run.
 */
void	it(const char *test, void (*function)(t_test_result *))
{
	bool			all_passed;
	t_test_result	result;
	t_test_result	*curr_result;

	all_passed = true;
	result = (t_test_result){0};
	function(&result);
	curr_result = &result;
	while (curr_result)
	{
		if (!curr_result->passed)
			all_passed = false;
		curr_result = curr_result->next;
	}
	if (all_passed)
		printf(GREEN BOLD EMOJI_PASS "  [PASS]" RESET " %s\n", test);
	else
		printf(RED BOLD EMOJI_FAIL "  [FAIL]" RESET " %s\n", test);
	curr_result = &result;
	while (curr_result)
	{
		check_if_it_passed(curr_result);
		curr_result = curr_result->next;
	}
}

