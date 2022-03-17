/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:57 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/13 18:27:58 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1dup;
	unsigned char	*s2dup;
	size_t			count;

	s1dup = (unsigned char *)s1;
	s2dup = (unsigned char *)s2;
	count = 0;
	while (s1dup[count] && s1dup[count] == s2dup[count])
		count++;
	return (s1dup[count] - s2dup[count]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1dup;
	unsigned char	*s2dup;
	size_t			count;

	if (n == 0)
		return (0);
	s1dup = (unsigned char *)s1;
	s2dup = (unsigned char *)s2;
	count = 0;
	while (s1dup[count] && count < n - 1 && s1dup[count] == s2dup[count])
		count++;
	return (s1dup[count] - s2dup[count]);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		length;

	if (!s1)
		return (NULL);
	length = ft_strlen(s1);
	s2 = malloc((length + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	s2[length] = 0;
	while (length > 0)
	{
		length--;
		s2[length] = s1[length];
	}
	return (s2);
}

char	*ft_strchr(const char *s, int c)
{
	char	*sdup;
	int		count;

	sdup = (char *)s;
	count = 0;
	if (c == 0)
		return (sdup + ft_strlen(s));
	while (s[count])
	{
		if (s[count] == (char)c)
			return (sdup + count);
		count++;
	}
	return (NULL);
}
