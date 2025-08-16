/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/14 01:00:09 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	expect_int(int received,
	int expected, t_test_result *result, const char *fail_reason)
{
	if (received == expected)
		result->passed = true;
	else
	{
		result->passed = false;
		snprintf(result->fail_reason,
			sizeof(result->fail_reason), "%s", fail_reason);
		snprintf(result->received, sizeof(result->received), "%d", received);
		snprintf(result->expected, sizeof(result->expected), "%d", expected);
	}
}

void	expect_ptr(void *received,
	void *expected, t_test_result *result, const char *fail_reason)
{
	if (received == expected)
		result->passed = true;
	else
	{
		result->passed = false;
		snprintf(result->fail_reason,
			sizeof(result->fail_reason), "%s", fail_reason);
		snprintf(result->received, sizeof(result->received), "%p", received);
		snprintf(result->expected, sizeof(result->expected), "%p", expected);
	}
}

void	expect_str(const char *received,
	const char *expected, t_test_result *result, const char *fail_reason)
{
	if (received == NULL && expected == NULL)
		result->passed = true;
	else if (received == NULL || expected == NULL)
	{
		result->passed = false;
		snprintf(result->fail_reason,
			sizeof(result->fail_reason), "%s", fail_reason);
		if (!received)
			received = "(null)";
		snprintf(result->received, sizeof(result->received), "%s", received);
		if (!expected)
			expected = "(null)";
		snprintf(result->expected, sizeof(result->expected), "%s", expected);
	}
	else if (!strcmp(received, expected))
		result->passed = true;
}
