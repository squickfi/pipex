/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multipipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:55 by squickfi          #+#    #+#             */
/*   Updated: 2022/03/17 21:52:08 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *filename, int file_num)
{
	int	id;

	if (file_num == 1)
	{
		id = open(filename, O_RDONLY);
		if (id < 0)
			perror(filename);
	}
	else
	{
		id = open(filename, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (id < 0)
			perror(filename);
	}
	return (id);
}

int	last_file(t_pipex_args info, int i, int **fd)
{
	int		id;
	char	**cmd;

	cmd = get_exec_arguments(info.argv, info.envp, i + 2);
	id = open_file(info.argv[info.argc - 1], 2);
	if (id > 0)
	{
		dup2(fd[i - 1][0], 0);
		dup2(id, 1);
		close_fds(info, fd);
		execve(cmd[0], cmd, info.envp);
	}
	close_fds(info, fd);
	exit(EXIT_FAILURE);
}

int	child_process(t_pipex_args info, int i, int **fd)
{
	int		id;
	char	**cmd;

	if (i == 0)
	{
		cmd = get_exec_arguments(info.argv, info.envp, i + 2);
		id = open_file(info.argv[1], 1);
		if (id < 0)
			exit(EXIT_FAILURE);
		dup2(id, 0), dup2(fd[i][1], 1);
		close_fds(info, fd);
		execve(cmd[0], cmd, info.envp);
	}
	else if (i == info.argc - 4)
		last_file(info, i, fd);
	else
	{
		cmd = get_exec_arguments(info.argv, info.envp, i + 2);
		dup2(fd[i - 1][0], 0), dup2(fd[i][1], 1);
		close_fds(info, fd);
		execve(cmd[0], cmd, info.envp);
	}
	return (1);
}

int	pipex(t_pipex_args info, int **fd, int *pid)
{
	int	i;

	i = 0;
	while (i < info.argc - 3)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(info, i, fd);
		else if (pid[i] < 0)
			exit(EXIT_FAILURE);
		i++;
	}
	return (0);
}
