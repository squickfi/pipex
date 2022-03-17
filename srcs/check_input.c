/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:37 by squickfi          #+#    #+#             */
/*   Updated: 2022/03/17 21:29:34 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// "Usage: ./pipex [input file] [cmd] [cmd] ... [cmd] [output file]\nor\n./pipex [\"here_doc\"] [LIMITER] [cmd] [cmd] ... [cmd] [output file]\n"

int	non_bonus_check(t_pipex_args info)
{
	if (info.argc != 5)
	{
		ft_putstr_fd("Usage:\n./pipex [input file] [cmd] [cmd] ... [cmd] [output file]\nor\n./pipex [\"here_doc\"] [LIMITER] [cmd] [cmd] ... [cmd] [output file]\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	check_here_doc(t_pipex_args info)
{
	int	here_doc;

	here_doc = 0;
	if (ft_strncmp(info.argv[1], "here_doc", 8) == 0)
	{
		if (info.argc < 5)
		{
			ft_putstr_fd("Usage:\n./pipex [input file] [cmd] [cmd] ... [cmd] [output file]\nor\n./pipex [\"here_doc\"] [LIMITER] [cmd] [cmd] ... [cmd] [output file]\n", 2);
			exit(EXIT_FAILURE);
		}
		here_doc = 1;
	}
	return (here_doc);
}

int	check_input(t_pipex_args info)
{
	int		here_doc;

	if (info.argc < 5)
	{
		ft_putstr_fd("Usage:\n./pipex [input file] [cmd] [cmd] ... [cmd] [output file]\nor\n./pipex [\"here_doc\"] [LIMITER] [cmd] [cmd] ... [cmd] [output file]\n", 2);
		exit(EXIT_FAILURE);
	}
	here_doc = check_here_doc(info);
	return (here_doc);
}
