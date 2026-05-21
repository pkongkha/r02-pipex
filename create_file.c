/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:01:08 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 12:08:42 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <fcntl.h>
#include <unistd.h>

// This is hotfix, and not permanent solution, please be caution before
// importing in another project!
void	create_file(char *filename, enum e_input_mode mode)
{
	int	fd;

	if (mode == FILENAME)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == HERE_DOC)
		fd = open(filename, O_CREAT, 0644);
	else
		return ;
	if (fd >= 3)
		close(fd);
}
