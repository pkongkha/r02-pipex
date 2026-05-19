/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:51 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/19 12:32:17 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <libft.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	create_proc_exec(struct s_create_proc_info *i, char *args[], char *paths[])
{
	int	exstatus;

	dup2(i->fdin, STDIN_FILENO);
	close(i->fdin);
	dup2(i->fdout, STDOUT_FILENO);
	close(i->fdout);
	ft_execvpe(args[0], args, i->env, paths);
	if (ft_strchr(args[0], '/') && *paths)
	{
		perror(args[0]);
		exstatus = 1;
	}
	else
	{
		err_cmdnotfound(args[0]);
		exstatus = 127;
	}
	ft_split_destroy(args);
	ft_split_destroy(paths);
	exit(exstatus);
}
