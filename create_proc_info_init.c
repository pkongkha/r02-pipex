/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc_info_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:45:17 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/19 10:48:25 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void	connect_fdin(struct s_main_info *i,
		struct s_create_proc_info *cpinf)
{
	if (i->cmd_remaining == i->cmd_total)
	{
		if (i->pipex_mode == HERE_DOC)
			cpinf->fdin = stdin_hdoc_pipe(i->argv[2]);
		else
			cpinf->fdin = open(i->argv[1], O_RDONLY);
		if (cpinf->fdin < 0)
		{
			perror(i->argv[1]);
		}
	}
	else
		cpinf->fdin = i->fdpipe[0];
}

static void	connect_fdout(struct s_main_info *i,
		struct s_create_proc_info *cpinf)
{
	if (i->cmd_remaining == 1)
	{
		if (i->pipex_mode == HERE_DOC)
			cpinf->fdout = open(i->argv[i->argc - 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cpinf->fdout = open(i->argv[i->argc - 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cpinf->fdout < 0)
			perror(i->argv[i->argc - 1]);
	}
	else
	{
		pipe(i->fdpipe);
		cpinf->fdout = i->fdpipe[1];
		cpinf->fdcloexec = i->fdpipe[0];
	}
}

void	create_proc_info_init(struct s_main_info *i,
		struct s_create_proc_info *cpinf)
{
	*cpinf = (struct s_create_proc_info){
		.fdcloexec = -1,
		.cmd = i->argv[i->argc - 1 - i->cmd_remaining],
		.env = i->envp};
	connect_fdin(i, cpinf);
	connect_fdout(i, cpinf);
}
