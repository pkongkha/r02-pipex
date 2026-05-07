/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_hdoc_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:52:48 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/07 15:20:33 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int	stdin_hdoc_pipe_writeto(int fdout, char *lim)
{
	char	*gnl_buf;

	gnl_buf = get_next_line(STDIN_FILENO);
	if (!gnl_buf)
		return (-1);
	if (!strncmp(gnl_buf, lim, strlen(lim)))
	{
		free(gnl_buf);
		return (0);
	}
	ft_putstr_fd(gnl_buf, fdout);
	free(gnl_buf);
	return (EAGAIN);
}

static int	stdin_hdoc_pipe_nonl(char *lim)
{
	int	fdpipe[2];
	int	pid;

	if (pipe(fdpipe) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid > 0)
	{
		close(fdpipe[1]);
		wait(NULL);
		return (fdpipe[0]);
	}
	close(fdpipe[0]);
	while (stdin_hdoc_pipe_writeto(fdpipe[1], lim) == EAGAIN)
		;
	free(lim);
	close(fdpipe[1]);
	fake_eof(STDIN_FILENO);
	get_next_line(STDIN_FILENO);
	exit(0);
}

int	stdin_hdoc_pipe(char *lim)
{
	int			fdout;
	char *const	nllim = ft_strjoin(lim, "\n");

	if (!nllim)
		return (-1);
	fdout = stdin_hdoc_pipe_nonl(nllim);
	free(nllim);
	return (fdout);
}
