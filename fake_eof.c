/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_eof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:52:24 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/06 23:10:21 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	fake_eof(int fd)
{
	int	fdpipe[2];

	pipe(fdpipe);
	dup2(fdpipe[0], fd);
	close(fdpipe[1]);
	close(fdpipe[0]);
}
