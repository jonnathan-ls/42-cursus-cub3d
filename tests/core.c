/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/13 00:51:24 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	print_result(const char *module, const char *case_name,
	t_test_result *result)
{
	if (result->passed)
		printf(GREEN BOLD EMOJI_PASS "  [PASS]" RESET " %s > %s\n",
			module, case_name);
	else
	{
		printf(RED BOLD EMOJI_FAIL "  [FAIL]" RESET " %s > %s\n",
			module, case_name);
		printf(YELLOW "    Reason: %s\n" RESET, result->fail_reason);
		printf(CYAN "    Expected: %s\n" RESET, result->expected);
	}
}

void	describe(const char *module, void (*function)(void))
{
	printf(BLUE BOLD EMOJI_DESCRIBE
		"  Module: %s" RESET "\n", module);
	function();
	printf("\n");
}

void	it(const char *module_name, const char *case_name,
	void (*function)(t_test_result *))
{
	t_test_result	result;

	result = (t_test_result){0};
	function(&result);
	print_result(module_name, case_name, &result);
}

void	check_leaks(const char *leak_log_path)
{
	FILE	*f;
	long	size;

	f = fopen(leak_log_path, "r");
	if (!f)
	{
		printf(RED EMOJI_LEAK
			"  [LEAK] Fail to open leak log file!" RESET "\n");
		return ;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fclose(f);
	if (size == 0)
		printf(GREEN EMOJI_LEAK
			"  No memory leak detected!" RESET "\n");
	else
	{
		printf(RED BOLD EMOJI_LEAK
			"  Memory leak detected!" RESET "\n");
		printf(YELLOW BOLD EMOJI_FILE
			"  Check 'valgrind.log' for more details." RESET "\n");
	}
}
