/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc_and_close_fd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:39:25 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 12:10:45 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <unistd.h>

void	create_proc_and_closefd(struct s_main_info *i,
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
