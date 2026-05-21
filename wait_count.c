/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:53:29 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 12:10:37 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <sys/wait.h>

/**
 * wait_count() - Wait for children
 * Return: status of last child defined by lastpid
 */
int	wait_count(int cnt, pid_t lastpid)
{
	int	wstatus;
	int	exstatus;

	exstatus = 1;
	if (lastpid > 0)
	{
		waitpid(lastpid, &wstatus, 0);
		exstatus = wexitstatus(wstatus);
		--cnt;
	}
	while (cnt)
	{
		wait(&wstatus);
		--cnt;
	}
	return (exstatus);
}
