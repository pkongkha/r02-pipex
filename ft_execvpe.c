/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:49:47 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/19 10:41:24 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_execvpe(const char *file, char *const argv[], char *const envp[],
		char *const paths[])
{
	char		*buf;
	char		*buf_path;

	if (ft_strchr(file, '/'))
		return (execve(file, argv, NULL));
	else
	{
		while (*paths)
		{
			buf_path = ft_strjoin(*paths, "/");
			if (!buf_path)
				return (-1);
			buf = ft_strjoin(buf_path, file);
			free(buf_path);
			if (!buf)
				return (-1);
			execve(buf, argv, envp);
			free(buf);
			++paths;
		}
	}
	return (-1);
}
