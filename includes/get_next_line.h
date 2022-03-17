/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:34 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/13 18:27:35 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

int		util_foo(ssize_t ret, char **buf, char **remain, int var);
int		where_is_c(char *s, char c);
char	*ft_strrchr(char *s, int c);
int		ft_strdup_till_c(char **s1, char **s2, char c, char **buf);
int		ft_gnl_strjoin(char **s1, char **s2);

int		first_check(int fd, char **line, char **buf, ssize_t *ret);
int		first_call(char **remain, char **buf);
int		if_there_is_n_in_remain(char **remain, char **line, char **buf);
int		foo_for_return(char **remain, char **line, ssize_t ret, char **buf);
int		get_next_line(int fd, char **line);

#endif