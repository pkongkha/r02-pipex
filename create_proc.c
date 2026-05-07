/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:51:54 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/07 14:32:42 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	**gen_empty_substr(void)
{
	char	**substrs;

	substrs = malloc(2 * sizeof(char *));
	substrs[0] = malloc(1);
	substrs[0][0] = '\0';
	substrs[1] = NULL;
	return (substrs);
}

static void	args_mutate_empty(char ***args)
{
	if (!*args)
		*args = gen_empty_substr();
	else if (!**args)
	{
		ft_split_destroy(*args);
		*args = gen_empty_substr();
	}
}

static int	create_proc_exec(int fdout, char **args, int fdin)
{
	dup2(fdin, STDIN_FILENO);
	if (fdin != STDIN_FILENO)
		close(fdin);
	dup2(fdout, STDOUT_FILENO);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	ft_execvp(args[0], args);
	if (is_path(args[0]))
		perror(args[0]);
	else
		err_cmdnotfound(args[0]);
	ft_split_destroy(args);
	exit(1);
}

int	create_proc(int fdout, char *cmdargs, int fdin, int fdclose)
{
	int		pid;
	char	**args;

	pid = fork();
	args = ft_split(cmdargs, ' ');
	args_mutate_empty(&args);
	if (pid == -1)
	{
		perror(args[0]);
		ft_split_destroy(args);
		return (-1);
	}
	else if (pid == 0)
	{
		if (fdclose >= 0)
			close(fdclose);
		create_proc_exec(fdout, args, fdin);
	}
	ft_split_destroy(args);
	return (pid);
}
