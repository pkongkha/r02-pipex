/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:06:04 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 10:15:49 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	create_proc_and_closefd(struct s_main_info *i,
		struct s_create_proc_info *cpinf)
{
	pid_t	pid;

	i->last_pid = -1;
	if (cpinf->fdin >= 0 && cpinf->fdout >= 0)
	{
		pid = create_proc(cpinf);
		if (pid > 0)
		{
			++i->need_wait;
			i->last_pid = pid;
		}
	}
	if (cpinf->fdin >= 3)
		close(cpinf->fdin);
	if (cpinf->fdout >= 3)
		close(cpinf->fdout);
}

/**
 * wait_count() - Wait for children
 * Return: status of last child defined by lastpid
 */
static int	wait_count(int cnt, pid_t lastpid)
{
	int	wstatus;
	int	exstatus;

	exstatus = 1;
	if (lastpid > 0)
	{
		waitpid(lastpid, &wstatus, 0);
		exstatus = wexitstatus(wstatus);
		--cnt;
	}
	while (cnt)
	{
		wait(&wstatus);
		--cnt;
	}
	return (exstatus);
}

static void	main_info_init(struct s_main_info *inf, int argc, char *argv[],
		char *envp[])
{
	*inf = (struct s_main_info){
		.last_pid = 0,
		.need_wait = 0,
		.argc = argc,
		.argv = argv,
		.envp = envp
	};
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		inf->pipex_mode = HERE_DOC;
	else
		inf->pipex_mode = FILENAME;
	inf->cmd_total = argc - 3 - (inf->pipex_mode == HERE_DOC);
	inf->cmd_remaining = inf->cmd_total;
}

int	main(int argc, char *argv[], char *envp[])
{
	struct s_main_info			in;
	struct s_create_proc_info	cpinf;

	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0))
		return (1);
	main_info_init(&in, argc, argv, envp);
	while (in.cmd_remaining)
	{
		create_proc_info_init(&in, &cpinf);
		create_proc_and_closefd(&in, &cpinf);
		--in.cmd_remaining;
	}
	return (wait_count(in.need_wait, in.last_pid));
}
