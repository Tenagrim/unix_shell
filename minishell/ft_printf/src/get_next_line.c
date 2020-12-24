/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:55:26 by gshona            #+#    #+#             */
/*   Updated: 2020/12/05 22:05:05 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

static char	*malloc_protection(int *errno, char **remain)
{
	*errno = ft_free(remain);
	return (NULL);
}

static char	*get_remained_line(char **remain, char **line, int *errno)
{
	char	*end;
	char	*tmp;

	end = NULL;
	if (remain && *remain)
	{
		if ((end = ft_str_chr(*remain, '\n')))
		{
			if (!(*line = ft_strdup(*remain)))
				return (malloc_protection(errno, remain));
			tmp = *remain;
			if (!(*remain = ft_strdup(end + 1)))
				return (malloc_protection(errno, remain));
			ft_free(&tmp);
		}
		else
		{
			if (!(*line = ft_strdup(*remain)))
				return (malloc_protection(errno, remain));
			ft_free(remain);
		}
	}
	else
		*line = ft_strdup("");
	return (end);
}

int			get_next_line(int fd, char **line)
{
	char		*buff;
	size_t		readed;
	static char	*remain;
	char		*end;
	int			errno;

	errno = 1;
	if (!(buff = (char*)malloc(BUFFER_SIZE + 1)) || fd < 0 ||
				BUFFER_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (ft_free(&buff) * ft_free(&remain) * -1);
	end = get_remained_line(&remain, line, &errno);
	while (!end && errno == 1 && (readed = read(fd, buff, BUFFER_SIZE)))
	{
		buff[readed] = '\0';
		if ((end = ft_str_chr(buff, '\n')))
		{
			ft_free(&remain);
			if (!(remain = ft_strdup(end + 1)))
				return (ft_free(line) * ft_free(&remain) * ft_free(&buff));
		}
		if (!(*line = ft_str_join(*line, buff)))
			return (ft_free(line) * ft_free(&remain) * ft_free(&buff));
	}
	free(buff);
	return ((!end && !readed) ? 0 * (ft_free(&remain)) : 1 * errno);
}
