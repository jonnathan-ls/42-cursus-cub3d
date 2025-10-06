/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "engine.h"
#include "libft.h"

/**
 * Prints error message to stderr.
 * @param msg Error message to display.
 * @return Always returns 1.
 */
static int	fail(char *msg)
{
	ft_putstr_fd("Error:\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

/**
 * Entry point of the program.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, 1 on failure.
 */
int	main(int argc, char **argv)
{
	t_config	cfg;
	t_engine	eng;

	if (argc < 2 || argc > 3)
		return (fail("usage: ./cub3d <map.cub> [-w]"));
	if (validate_file_extension(argv[1]) < 0)
		return (fail("invalid extension"));
	if (parse_cub(argv[1], &cfg) < 0)
		return (fail("parse failure"));
	eng.fullscreen = ft_strncmp(argv[2], "-w", 3);
	if (configure_engine(&eng, &cfg) < 0)
	{
		free_config(&cfg);
		return (fail("engine init failed"));
	}
	engine_loop(&eng);
	destroy_engine(&eng);
	free_config(&cfg);
	return (0);
}
