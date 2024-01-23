/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myevou <myevou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:29:04 by myevou            #+#    #+#             */
/*   Updated: 2024/01/23 03:16:14 by myevou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	initargs(t_args *args, char **av, char **env, int ac)
{
	args->nbcmds = ac - 3;
	args->env = env;
	args->cmds = av + 2;
	args->in = av[1];
	args->out = av[ac - 1];
	args->old_pipes = -1;
	args->flag = O_TRUNC;

}
void	redirection_files(t_args *args, int index)
{
	int	fd;

	if (index == 0)
		fd = open(args->in, O_RDONLY);
	if (index == args->nbcmds - 1)
		fd = open(args->out, O_RDWR | args->flag | O_CREAT, 0666);
	if (fd < 0)
		(fprintf(stderr, "mika: %s\n", strerror(errno)), exit(1));
	dup2(fd, index == args->nbcmds - 1);
	close(fd);
}

void	redirection_pipes(t_args *args, int index)
{
	if (index != args->nbcmds - 1) // si c'est pas la derniere
		dup2(args->fd[1], STDOUT_FILENO);
	// ouvrir input
	if (index != 0) // si c'est pas la premiere
	{
		dup2(args->old_pipes, STDIN_FILENO);
		close(args->old_pipes);
	}
	close(args->fd[0]);
	close(args->fd[1]);
}

void	ft_freetab(char **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}

void	*execution(t_args *args, int i)
{
	char	**cmd;

	cmd = ft_split(args->cmds[i], ' ');
	if (!cmd || !*cmd)
		return (ft_freetab(cmd), exit(1), NULL);
	execvp(cmd[0], cmd);
	fprintf(stderr, "je suis %i et ma cmd est %s\n", i, cmd[0]);
	ft_freetab(cmd);
	return (NULL);
}

void	proccesses(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbcmds)
	{
		pipe(args->fd);
		args->pid[i] = fork();
		if (args->pid[i] == 0)
		{
			free(args->pid);
			redirection_pipes(args, i);
			if (i == 0 || i == args->nbcmds - 1)
				redirection_files(args, i);
			execution(args, i);
			exit(127);
		}
		else
		{
			close(args->fd[1]);
			if (i)
				close(args->old_pipes);
			args->old_pipes = args->fd[0];
		}
		i++;
	}
	close(args->fd[0]);
}

void	waitprocess(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbcmds)
		waitpid(args->pid[i++], NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	static t_args	args = {0};

	initargs(&args, av, env, ac);
	if (!ft_strcmp(av[1], "here_doc"))
		here_doc(&args);
	args.pid = malloc(sizeof(pid_t) * args.nbcmds);
	if (!args.pid)
		exit(1);
	proccesses(&args);
	waitprocess(&args);
	free(args.pid);
}
