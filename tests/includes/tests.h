/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/13 00:59:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "cub3d.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>
# include "cases.h"

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define CYAN    "\033[36m"
# define BOLD    "\033[1m"

# define EMOJI_IT "🧪"
# define EMOJI_PASS "✅"
# define EMOJI_LEAK "💧"
# define EMOJI_FAIL "❌"
# define EMOJI_FILE "📄"
# define EMOJI_DESCRIBE "📦"

typedef struct s_test_result
{
	int		passed;
	char	expected[128];
	char	fail_reason[256];
}	t_test_result;

void	check_leaks(const char *leak_log_path);
void	describe(const char *module, void (*function)(void));
void	it(const char *module_name,
			const char *case_name, void (*function)(t_test_result *));
void	print_result(const char *module,
			const char *case_name, t_test_result *result);

void	expect_int(int received, int expected,
			t_test_result *result, const char *fail_reason);
void	expect_ptr(void *received, void *expected,
			t_test_result *result, const char *fail_reason);
void	expect_str(const char *received, const char *expected,
			t_test_result *result, const char *fail_reason);

#endif