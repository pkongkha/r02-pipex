/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:49:47 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/06 22:51:20 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_execvp(const char *file, char *const argv[])
{
	const char	**paths = (const char *[]){"/bin/", "/usr/bin/", NULL};
	char		*buf;

	if (is_path(file))
		return (execve(file, argv, NULL));
	else
	{
		while (*paths)
		{
			buf = ft_strjoin(*paths, file);
			execve(buf, argv, NULL);
			free(buf);
			++paths;
		}
	}
	return (-1);
}
