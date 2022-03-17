/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:28:00 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/13 18:28:01 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	if (!dst || !src)
		return (0);
	count = 0;
	if (dstsize)
	{
		while (src[count] && dstsize - 1)
		{
			dst[count] = src[count];
			count++;
			dstsize--;
		}
		dst[count] = 0;
	}
	while (src[count])
		count++;
	return (count);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	count;

	count = 0;
	if (s)
	{
		while (s[count])
		{
			ft_putchar_fd(s[count], fd);
			count++;
		}
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	new_len;
	char	*str;

	if (!s)
		return (NULL);
	s1 = (char *)s;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	new_len = ft_strlen(s + start);
	if (new_len < len)
		len = new_len;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, len + 1);
	return (str);
}
