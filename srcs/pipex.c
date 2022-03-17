/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:20 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/13 18:32:48 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_multipipes(t_pipex_args info)
{
	int		**fd;
	pid_t	*pid;
	int		i;

	fd = make_fds(info);
	pid = malloc((info.argc - 3) * sizeof(pid_t *));
	if (!pid)
		exit(EXIT_FAILURE);
	pipex(info, fd, pid);
	close_fds(info, fd);
	i = 0;
	while (i < info.argc - 3)
		waitpid(pid[i++], NULL, 0);
	free_fds(info, fd);
	free(pid);
	return (0);
}

int	handle_here_doc(t_pipex_args info)
{
	int		**fd;
	pid_t	*pid;
	int		i;

	fd = make_fds(info);
	pid = malloc((info.argc - 3) * sizeof(pid_t *));
	if (!pid)
		exit(EXIT_FAILURE);
	make_here_doc_file(info);
	here_doc_pipex(info, fd, pid);
	close_fds(info, fd);
	i = 0;
	while (i < info.argc - 3)
		waitpid(pid[i++], NULL, 0);
	if (unlink("here_doc") == -1)
		perror("Unlink error"), exit(EXIT_FAILURE);
	free_fds(info, fd);
	free(pid);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_args	info;
	int				here_doc;

	info.argc = argc;
	info.argv = argv;
	info.envp = envp;
	here_doc = check_input(info);
	if (here_doc == 0)
		handle_multipipes(info);
	else
		handle_here_doc(info);
	return (0);
}
