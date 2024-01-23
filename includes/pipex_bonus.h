/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myevou <myevou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:45:48 by myevou            #+#    #+#             */
/*   Updated: 2024/01/23 03:15:43 by myevou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// # include "get_next_line_bonus.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <sys/fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	// int		ac;
	// char	**av;
	char	*in;
	char	*out;
	int		nbcmds;
	int		old_pipes;
	int		fd[2];
	// int		heredoc;
	// int		heredocfd;
	// char	*delim;
	int		flag;
	char	**cmds;
	char	**env;
	pid_t	*pid;
}	t_args;

char	**ft_split(char const *s, char c);
// 	MAIN.C
#endif
