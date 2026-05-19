/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:51:54 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/19 12:42:00 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	**gen_empty_substr(void)
{
	char	**substrs;

	substrs = malloc(2 * sizeof(char *));
	if (!substrs)
		return (NULL);
	substrs[0] = malloc(1);
	if (!*substrs)
	{
		free(substrs);
		return (NULL);
	}
	substrs[0][0] = '\0';
	substrs[1] = NULL;
	return (substrs);
}

static char	**get_paths(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (ft_split(&(*env)[5], ':'));
		++env;
	}
	return (gen_empty_substr());
}

static char	**get_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		args = gen_empty_substr();
	else if (!*args)
	{
		ft_split_destroy(args);
		args = gen_empty_substr();
	}
	return (args);
}

static int	init_args_paths(struct s_create_proc_info *i, char **args[],
		char **paths[])
{
	*args = get_args(i->cmd);
	if (!*args)
		return (-ENOMEM);
	*paths = get_paths(i->env);
	if (!*paths)
	{
		ft_split_destroy(*args);
		return (-ENOMEM);
	}
	return (0);
}

int	create_proc(struct s_create_proc_info *i)
{
	pid_t	pid;
	char	**args;
	char	**paths;

	if (init_args_paths(i, &args, &paths) < 0)
	{
		perror("pipex");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		perror(args[0]);
	else if (pid == 0)
	{
		if (i->fdcloexec >= 0)
			close(i->fdcloexec);
		create_proc_exec(i, args, paths);
	}
	ft_split_destroy(args);
	ft_split_destroy(paths);
	return (pid);
}
