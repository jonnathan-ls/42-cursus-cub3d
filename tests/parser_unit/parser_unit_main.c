/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_unit_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:40:23 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 17:40:54 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_unit.h"
#include <stdio.h>
#include <string.h>

static t_test_case	*g_cases(void)
{
	static t_test_case	cases[] = {{"valid_minimal", test_valid_minimal, 1},
			{"invalid_extension", test_invalid_extension, 0},
			{"duplicate_texture", test_duplicate_texture, 0},
			{"duplicate_color", test_duplicate_color, 0}, {"missing_player",
			test_missing_player, 0}, {"multiple_players", test_multiple_players,
			0}, {"map_not_closed", test_map_not_closed, 0}, {"invalid_map_char",
			test_invalid_map_char, 0}, {"color_out_of_range",
			test_color_out_of_range, 0}, {"texture_file_missing",
			test_texture_file_missing, 0}, {"", NULL, 0}};

	return (cases);
}

static int	name_selected(const char *filter, const char *name)
{
	if (!filter || !*filter)
		return (1);
	if (ft_strnstr(name, filter, ft_strlen(name)))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	char		root[256];
	t_test_case	*cases;
	int			passed;
	int			total;
	int			i;
	int			ret;

	if (build_temp_root(root, sizeof(root)) < 0)
	{
		fprintf(stderr, "Failed to create temp root.\n");
		return (1);
	}
	cases = g_cases();
	passed = 0;
	total = 0;
	i = 0;
	while (cases[i].fn)
	{
		if (name_selected(argc > 1 ? argv[1] : NULL, cases[i].name))
		{
			total++;
			ret = cases[i].fn(NULL, root);
			if (ret == 0)
			{
				passed++;
				printf("[OK] %s\n", cases[i].name);
			}
			else
				printf("[KO] %s (ret=%d)\n", cases[i].name, ret);
		}
		i++;
	}
	printf("Summary: %d/%d passed\n", passed, total);
	return (passed == total ? 0 : 1);
}
