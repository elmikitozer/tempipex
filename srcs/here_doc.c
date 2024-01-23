/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myevou <myevou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:11:56 by myevou            #+#    #+#             */
/*   Updated: 2024/01/23 03:16:56 by myevou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	here_doc(t_args *args, char *delim)
{
	int		fd;
	char	*line;

	args->nbcmds -= 1;
	args->in = ".tmp";
	args->cmds += 1;
	args->flag = O_APPEND;
	fd = open(".tmp", O_TRUNC | O_CREAT | O_RDWR, 0666);
	// if (fd < 0)
	// fils de pute
	while (1)
	{
		line = get_next_line(0, 0);
		if (!line || !ft_strcmp(line, delim))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}
