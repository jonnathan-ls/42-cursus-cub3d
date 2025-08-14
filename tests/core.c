/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/14 00:09:24 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

/**
 * Print the result of a test case.
 * @param test The name of the test case.
 * @param result The result of the test case.
 */
void	print_result(const char *test, t_test_result *result)
{
	if (result->passed)
		printf(GREEN BOLD EMOJI_PASS "  [PASS]" RESET " %s\n", test);
	else
	{
		printf(RED BOLD EMOJI_FAIL "  [FAIL]" RESET " %s\n", test);
		printf(YELLOW "    %s\n" RESET, result->fail_reason);
		printf(LIGHT_RED "    Received: %s\n" RESET, result->received);
		printf(CYAN "    Expected: %s\n" RESET, result->expected);
	}
}

/**
 * Proicess a test suite.
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
	t_test_result	result;

	result = (t_test_result){0};
	function(&result);
	print_result(test, &result);
}

