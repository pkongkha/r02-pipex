/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkongkha <pkongkha@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 23:12:08 by pkongkha          #+#    #+#             */
/*   Updated: 2026/05/21 12:07:03 by pkongkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/types.h>

enum	e_input_mode
{
	FILENAME,
	HERE_DOC,
};

struct	s_main_info
{
	enum e_input_mode	pipex_mode;
	int					fdpipe[2];
	int					cmd_remaining;
	int					cmd_total;
	pid_t				last_pid;
	int					need_wait;
	int					argc;
	char				**argv;
	char				**envp;
};

struct	s_create_proc_info
{
	char	*cmd;
	int		fdin;
	int		fdout;
	int		fdcloexec;
	char	**env;
};

void	create_file(char *filename, enum e_input_mode mode);
int		create_proc(struct s_create_proc_info *i);
void	create_proc_and_closefd(struct s_main_info *i,
			struct s_create_proc_info *cpinf);
int		create_proc_exec(struct s_create_proc_info *i, char *args[],
			char *paths[]);
void	create_proc_info_init(struct s_main_info *i,
			struct s_create_proc_info *cpinf);
void	err_cmdnotfound(char *name);
void	fake_eof(int fd);
int		ft_execvpe(const char *file, char *const argv[], char *const envp[],
			char *const paths[]);
int		is_path(const char *path);
int		stdin_hdoc_pipe(char *lim);
int		wait_count(int cnt, pid_t lastpid);
int		wexitstatus(int status);
#endif
