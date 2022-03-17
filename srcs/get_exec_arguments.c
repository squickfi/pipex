/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:48 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/14 17:02:36 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
	{
		free(arr[count]);
		count++;
	}
	free(arr);
}

char	**find_pathes(char *envp[])
{
	char	*path_str;
	char	**pathes;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
		{
			path_str = *envp;
			break ;
		}
		envp++;
	}
	if (!*envp)
		return (NULL);
	path_str = ft_strchr(path_str, '/');
	pathes = ft_split(path_str, ':');
	if (!pathes)
		return (NULL);
	return (pathes);
}

char	*get_path_str(char *cmd, char **pathes)
{
	char	*path;
	char	*temp;

	if (!cmd)
		return (NULL);
	while (*pathes)
	{
		temp = ft_strjoin(*pathes, "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, cmd);
		if (!path)
		{
			free(temp);
			return (NULL);
		}
		free(temp);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
		pathes++;
	}
	return (NULL);
}

char	*get_path(char **cmd_args, char *envp[])
{
	char	**pathes;
	char	*path;

	if (access(cmd_args[0], X_OK) != -1)
	{
		path = ft_strdup(cmd_args[0]);
		if (!path)
			exit(EXIT_FAILURE);
		return (path);
	}
	pathes = find_pathes(envp);
	if (!pathes)
	{
		ft_putstr_fd(cmd_args[0], 2), write(2, \
		": there's no such command.\n", 27), exit(EXIT_FAILURE);
	}
	path = get_path_str(cmd_args[0], pathes);
	if (!path)
	{
		ft_putstr_fd(cmd_args[0], 2), write(2, \
		": there's no such command.\n", 27), free_array(pathes);
		return (NULL);
	}
	free_array(pathes);
	return (path);
}

char	**get_exec_arguments(char *argv[], char *envp[], int num1)
{
	char	**cmd_args;
	char	*path;

	cmd_args = split_args(argv[num1]);
	if (!cmd_args)
		exit(EXIT_FAILURE);
	path = get_path(cmd_args, envp);
	if (!path)
	{
		free_array(cmd_args);
		return (NULL);
	}
	free(cmd_args[0]);
	cmd_args[0] = path;
	return (cmd_args);
}

/*
int	main(int argc, char *argv[], char *envp[])
{
	char **cmd_args = get_exec_arguments(argv, envp, 2);
	if (cmd_args)
		for (int i = 0; cmd_args[i]; i++)
			printf("%s\n", cmd_args[i]);
	return (0);
}
*/