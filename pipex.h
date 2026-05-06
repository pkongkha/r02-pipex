/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 23:12:08 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/06 23:13:32 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

struct	s_main_info
{
	int	fdpipe[2];
	int	cmd_count;
	int	cmd_status;
	int	cmd_succ;
};

int		create_proc(int fdout, char *cmdargs, int fdin);
int		create_proc_close(int fdout, char *cmdargs, int fdin, int fdclose);
void	err_cmdnotfound(char *name);
void	fake_eof(int fd);
int		ft_execvp(const char *file, char *const argv[]);
int		is_path(const char *path);
int		stdin_hdoc_pipe(char *lim);
#endif
