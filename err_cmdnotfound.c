/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmdnotfound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 22:51:38 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/06 23:10:12 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>

void	err_cmdnotfound(char *name)
{
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}
