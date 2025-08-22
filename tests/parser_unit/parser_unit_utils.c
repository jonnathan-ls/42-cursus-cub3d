/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_unit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:40:27 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 17:40:52 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_unit.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int	write_file(const char *path, const char *content)
{
	int	fd;
	int	len;

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	len = (int)ft_strlen(content);
	if (write(fd, content, len) != len)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	ensure_dir(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)
			return (0);
		return (-1);
	}
	if (mkdir(path, 0755) < 0)
		return (-1);
	return (0);
}

char	*join_path(const char *a, const char *b, char *buf, int bufsize)
{
	int	al;
	int	bl;

	al = (int)ft_strlen(a);
	bl = (int)ft_strlen(b);
	if (al + 1 + bl + 1 > bufsize)
		return (NULL);
	ft_memcpy(buf, a, al);
	buf[al] = '/';
	ft_memcpy(buf + al + 1, b, bl);
	buf[al + 1 + bl] = '\0';
	return (buf);
}

int	create_dummy_texture(const char *dir, const char *name, char *out,
		int outsz)
{
	char	path[512];

	if (!join_path(dir, name, path, sizeof(path)))
		return (-1);
	if (write_file(path, "") < 0)
		return (-1);
	if ((int)ft_strlen(path) + 1 > outsz)
		return (-1);
	ft_strlcpy(out, path, outsz);
	return (0);
}

int	build_temp_root(char *buf, int buflen)
{
	char	pidbuf[32];
	int		len;

	ft_strlcpy(buf, "./parser_tmp_", buflen);
	len = (int)ft_strlen(buf);
	ft_strlcpy(pidbuf, "XXXXXXXX", sizeof(pidbuf));
	/* simple pseudo unique suffix */
	pidbuf[0] = '0' + (getpid() % 10);
	pidbuf[1] = '0' + ((getpid() / 10) % 10);
	pidbuf[2] = '0' + ((getpid() / 100) % 10);
	pidbuf[3] = '\0';
	if (len + (int)ft_strlen(pidbuf) + 1 > buflen)
		return (-1);
	ft_strlcpy(buf + len, pidbuf, buflen - len);
	if (ensure_dir(buf) < 0)
		return (-1);
	return (0);
}

static int	redirect_stderr(int *saved, int pipefd[2])
{
	if (pipe(pipefd) < 0)
		return (-1);
	*saved = dup(2);
	if (*saved < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (dup2(pipefd[1], 2) < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		close(*saved);
		return (-1);
	}
	return (0);
}

static void	restore_stderr(int saved, int pipefd[2])
{
	dup2(saved, 2);
	close(saved);
	close(pipefd[1]);
}

int	capture_parse(const char *path, t_config *cfg, char *errbuf, int buflen)
{
	int		pipefd[2];
	int		saved;
	int		ret;
	ssize_t	red;

	if (redirect_stderr(&saved, pipefd) < 0)
		return (-1);
	ret = parse_cub(path, cfg);
	restore_stderr(saved, pipefd);
	red = read(pipefd[0], errbuf, buflen - 1);
	if (red >= 0)
		errbuf[red] = '\0';
	close(pipefd[0]);
	return (ret);
}
