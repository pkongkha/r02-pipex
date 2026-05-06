/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:52:08 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/06 23:09:23 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	create_proc_close_exec(int fdout, char **args, int fdin,
		int fdclose)
{
	close(fdclose);
	dup2(fdin, STDIN_FILENO);
	if (fdin != STDIN_FILENO)
		close(fdin);
	dup2(fdout, STDOUT_FILENO);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	ft_execvp(args[0], args);
	if (is_path(args[0]))
		err_cmdnotfound(args[0]);
	else
		perror(args[0]);
	ft_split_destroy(args);
	exit(1);
}

int	create_proc_close(int fdout, char *cmdargs, int fdin, int fdclose)
{
	int		pid;
	char	**args;

	pid = fork();
	args = ft_split(cmdargs, ' ');
	if (pid == -1)
	{
		perror(args[0]);
		ft_split_destroy(args);
		return (-1);
	}
	else if (pid == 0)
		create_proc_close_exec(fdout, args, fdin, fdclose);
	ft_split_destroy(args);
	return (pid);
}
