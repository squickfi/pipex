/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:52 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/13 18:27:53 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	make_here_doc_file(t_pipex_args info)
{
	int		id;
	char	*limiter;
	char	*line;

	id = open("here_doc", O_RDWR | O_CREAT | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (id < 0)
		perror("open_error"), exit(EXIT_FAILURE);
	limiter = info.argv[2];
	if (get_next_line(0, &line) == -1)
		exit(EXIT_FAILURE);
	while (ft_strcmp(line, limiter) != 0)
	{
		write(id, line, ft_strlen(line)), write(id, "\n", 1);
		free(line);
		if (get_next_line(0, &line) == -1)
			exit(EXIT_FAILURE);
	}
	close(id);
	free(line);
	return (0);
}

int	here_doc_open_file(char *filename, int file_num)
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
		id = open(filename, O_WRONLY | O_CREAT | O_APPEND, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (id < 0)
			perror(filename);
	}
	return (id);
}

int	here_doc_last_file(t_pipex_args info, int i, int **fd)
{
	int		id;
	char	**cmd;

	cmd = get_exec_arguments(info.argv, info.envp, i + 2);
	id = here_doc_open_file(info.argv[info.argc - 1], 2);
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

int	here_doc_child_process(t_pipex_args info, int i, int **fd)
{
	int		id;
	char	**cmd;

	if (i == 1)
	{
		cmd = get_exec_arguments(info.argv, info.envp, i + 2);
		id = here_doc_open_file("here_doc", 1);
		if (id < 0)
			exit(EXIT_FAILURE);
		dup2(id, 0), dup2(fd[i][1], 1), close_fds(info, fd);
		execve(cmd[0], cmd, info.envp), exit(EXIT_FAILURE);
	}
	else if (i == info.argc - 4)
		here_doc_last_file(info, i, fd);
	else
	{
		cmd = get_exec_arguments(info.argv, info.envp, i + 2);
		dup2(fd[i - 1][0], 0), dup2(fd[i][1], 1);
		close_fds(info, fd), execve(cmd[0], cmd, info.envp);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	here_doc_pipex(t_pipex_args info, int **fd, int *pid)
{
	int		i;

	i = 1;
	while (i < info.argc - 3)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			here_doc_child_process(info, i, fd);
		else if (pid[i] < 0)
			exit(EXIT_FAILURE);
		i++;
	}
	return (0);
}
