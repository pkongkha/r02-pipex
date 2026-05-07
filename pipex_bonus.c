/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:06:04 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/07 15:25:27 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int	cpipe_1(int fdpipe[2], char **argv, int argc, int cmd_count)
{
	int	fdin;
	int	cmd_succ;

	cmd_succ = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		fdin = stdin_hdoc_pipe(argv[2]);
	else
		fdin = open(argv[1], O_RDONLY);
	if (fdin < 0)
	{
		perror(argv[1]);
		return (-1);
	}
	pipe(fdpipe);
	if (create_proc(fdpipe[1], argv[argc - 1 - cmd_count], fdin, fdpipe[0]) > 0)
		++cmd_succ;
	if (fdin >= 0)
		close(fdin);
	close(fdpipe[1]);
	return (cmd_succ);
}

static int	cpipe_2(int fdpipe[2], char **argv, int argc, int cmd_count)
{
	int	cmd_succ;
	int	fdpipe_read;

	cmd_succ = 0;
	fdpipe_read = dup(fdpipe[0]);
	close(fdpipe[0]);
	pipe(fdpipe);
	if (create_proc(fdpipe[1], argv[argc - 1 - cmd_count], fdpipe_read,
			fdpipe[0]) > 0)
		++cmd_succ;
	close(fdpipe_read);
	close(fdpipe[1]);
	return (cmd_succ);
}

static int	cpipe_3(int fdpipe[2], char **argv, int argc, int cmd_count)
{
	int	cmd_succ;
	int	fdout;

	cmd_succ = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
	else
		fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	if (fdout < 0)
		perror(argv[argc - 1]);
	else if (create_proc(fdout, argv[argc - 1 - cmd_count], fdpipe[0], -1) > 0)
		++cmd_succ;
	close(fdpipe[0]);
	if (fdout >= 0)
		close(fdout);
	return (cmd_succ);
}

static void	wait_count(int cnt)
{
	while (cnt)
	{
		wait(NULL);
		--cnt;
	}
}

int	main(int argc, char **argv)
{
	struct s_main_info	in;
	int					status;
	int					cmd_count_o;

	if (argc < 4 || (argc < 5 && ft_strncmp(argv[1], "here_doc", 9)))
		return (1);
	status = 0;
	cmd_count_o = argc - 3 - (ft_strncmp(argv[1], "here_doc", 9) == 0);
	in = (struct s_main_info){.cmd_count = cmd_count_o, .cmd_succ = 0};
	while (in.cmd_count)
	{
		if (in.cmd_count == cmd_count_o)
			in.cmd_status = cpipe_1(in.fdpipe, argv, argc, in.cmd_count);
		else if (in.cmd_count > 1)
			in.cmd_status = cpipe_2(in.fdpipe, argv, argc, in.cmd_count);
		else
			in.cmd_status = cpipe_3(in.fdpipe, argv, argc, in.cmd_count);
		if (in.cmd_status > 0)
			in.cmd_succ += in.cmd_status;
		else
			status = 1;
		--in.cmd_count;
	}
	wait_count(in.cmd_succ);
	return (status);
}
