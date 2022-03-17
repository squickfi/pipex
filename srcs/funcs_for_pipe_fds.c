/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_for_pipe_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:45 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/13 18:27:46 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**make_fds(t_pipex_args info)
{
	int	**fd;
	int	i;

	fd = malloc((info.argc - 4) * (sizeof(int *)));
	if (!fd)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < (info.argc - 4))
	{
		fd[i] = malloc(2 * (sizeof(int)));
		if (!fd[i])
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < info.argc - 4)
	{
		if (pipe(fd[i]) == -1)
			ft_putstr_fd("Pipe error.\n", 2), exit(EXIT_FAILURE);
		i++;
	}
	return (fd);
}

void	close_fds(t_pipex_args info, int **fd)
{
	int	i;

	i = 0;
	while (i < info.argc - 4)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_fds(t_pipex_args info, int **fd)
{
	int	i;

	i = 0;
	while (i < info.argc - 4)
		free(fd[i]), i++;
	free(fd);
}
