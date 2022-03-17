/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:28:13 by squickfi          #+#    #+#             */
/*   Updated: 2022/03/17 21:34:46 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex_args
{
	int		argc;
	char	**argv;
	char	**envp;
}			t_pipex_args;

typedef struct s_parser_info
{
	int	start;
	int	end;
	int	temp;
	int	quote;
}		t_parser_info;

// libft_funcs.c

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);

// libft_funcs2.c

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// ft_strjoin.c

char	*ft_strjoin(char const *s1, char const *s2);

// ft_split.c

char	**fillarr(const char *s, char **strs, char c);
char	**ft_split(const char *s, char c);

// get_exec_arguments.c

void	free_array(char **arr);
char	**find_pathes(char *envp[]);
char	*get_path_str(char *cmd, char **pathes);
char	*get_path(char **cmd_args, char *envp[]);
char	**get_exec_arguments(char *argv[], char *envp[], int num1);

// parse_cmd_args.c

char	**free_split(int temp, char **strs);
char	**free_args_and_return_null(int temp, char **strs);
int		quote_case(char *s, char c);
int		count_words(char *s, t_parser_info info);

// parse_cmd_args2.c

char	**fill_args2(char *s, char **strs, t_parser_info info);
char	**fill_args(char *s, char **strs);
char	**split_args(char *s);

// check_input.c

int		non_bonus_check(t_pipex_args info);
int		check_here_doc(t_pipex_args info);
int		check_input(t_pipex_args info);

// funcs_for_pipe_fds.c

int		**make_fds(t_pipex_args info);
void	close_fds(t_pipex_args info, int **fd);
void	free_fds(t_pipex_args info, int **fd);

// handle_here_doc.c

int		make_here_doc_file(t_pipex_args info);
int		here_doc_open_file(char *filename, int file_num);
int		here_doc_last_file(t_pipex_args info, int i, int **fd);
int		here_doc_child_process(t_pipex_args info, int i, int **fd);
int		here_doc_pipex(t_pipex_args info, int **fd, int *pid);

// handle_multipipes.c

int		open_file(char *filename, int file_num);
int		last_file(t_pipex_args info, int i, int **fd);
int		child_process(t_pipex_args info, int i, int **fd);
int		pipex(t_pipex_args info, int **fd, int *pid);

#endif
