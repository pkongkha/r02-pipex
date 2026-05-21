/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:06:04 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 12:09:39 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	main_info_init(struct s_main_info *inf, int argc, char *argv[],
		char *envp[])
{
	*inf = (struct s_main_info){
		.last_pid = 0,
		.need_wait = 0,
		.argc = argc,
		.argv = argv,
		.envp = envp
	};
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		inf->pipex_mode = HERE_DOC;
	else
		inf->pipex_mode = FILENAME;
	inf->cmd_total = argc - 3 - (inf->pipex_mode == HERE_DOC);
	inf->cmd_remaining = inf->cmd_total;
}

int	main(int argc, char *argv[], char *envp[])
{
	struct s_main_info			in;
	struct s_create_proc_info	cpinf;

	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0))
		return (1);
	main_info_init(&in, argc, argv, envp);
	create_file(argv[argc - 1], in.pipex_mode);
	while (in.cmd_remaining)
	{
		create_proc_info_init(&in, &cpinf);
		create_proc_and_closefd(&in, &cpinf);
		--in.cmd_remaining;
	}
	return (wait_count(in.need_wait, in.last_pid));
}
