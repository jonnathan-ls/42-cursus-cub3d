/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 19:09:52 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"

static int	fail(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

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
	eng.fullscreen = ft_strncmp(argv[2], "-w", 2);
	if (ft_engine_init(&eng, &cfg) < 0)
	{
		free_config(&cfg);
		return (fail("engine init failed"));
	}
	ft_engine_loop(&eng);
	ft_engine_destroy(&eng);
	free_config(&cfg);
	return (0);
}
