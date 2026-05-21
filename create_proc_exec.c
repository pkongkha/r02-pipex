/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:51 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 14:00:31 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <libft.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	is_command_found(char *filename, char *paths[])
{
	char		*buf;
	char		*buf_path;

	while (*paths)
	{
		buf_path = ft_strjoin(*paths, "/");
		if (!buf_path)
			return (-1);
		buf = ft_strjoin(buf_path, filename);
		free(buf_path);
		if (!buf)
			return (-1);
		if (access(buf, F_OK) == 0)
		{
			access(buf, X_OK);
			free(buf);
			return (1);
		}
		free(buf);
		++paths;
	}
	return (0);
}

static int	create_proc_exec_path_err(char *pathname)
{
	perror(pathname);
	if (access(pathname, F_OK) != 0)
		return (127);
	else if (access(pathname, X_OK) != 0)
		return (126);
	else
		return (1);
}

static int	is_all_spc(char *str)
{
	while (ft_isspace(*str))
		++str;
	return (*str == '\0');
}

static int	create_proc_exec_cmd_err(char *cmdname, char *paths[])
{
	const int	exists = is_command_found(cmdname, paths);

	if (exists && !is_all_spc(cmdname))
	{
		perror(cmdname);
		return (126);
	}
	else
	{
		err_cmdnotfound(cmdname);
		return (127);
	}
}

int	create_proc_exec(struct s_create_proc_info *i, char *args[], char *paths[])
{
	int	exstatus;

	dup2(i->fdin, STDIN_FILENO);
	close(i->fdin);
	dup2(i->fdout, STDOUT_FILENO);
	close(i->fdout);
	ft_execvpe(args[0], args, i->env, paths);
	if (ft_strchr(args[0], '/') && *paths)
		exstatus = create_proc_exec_path_err(args[0]);
	else
		exstatus = create_proc_exec_cmd_err(args[0], paths);
	ft_split_destroy(args);
	ft_split_destroy(paths);
	exit(exstatus);
}
