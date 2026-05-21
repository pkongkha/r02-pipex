/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 02:27:29 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 17:19:36 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	ft_split_destroy(char **strs)
{
	char	**strs_o;

	if (!strs)
		return ;
	strs_o = strs;
	while (*strs)
		free(*strs++);
	free(strs_o);
}
