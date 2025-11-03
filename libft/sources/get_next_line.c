/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:36:20 by melwong           #+#    #+#             */
/*   Updated: 2025/06/16 11:56:29 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static char	*extract_and_trim(char **result, char *storage)
{
	size_t	line_len;
	char	*trimmed;

	if (!storage || storage[0] == '\0')
		return (NULL);
	line_len = 0;
	while (storage[line_len] != '\n' && storage[line_len] != '\0')
		line_len++;
	if (storage[line_len] != '\n')
	{
		*result = ft_substr(storage, 0, line_len);
		free(storage);
		return (NULL);
	}
	line_len += 1;
	*result = ft_substr(storage, 0, line_len);
	trimmed = ft_strdup(storage + line_len);
	free(storage);
	return (trimmed);
}

static char	*read_loop(int fd, char *storage)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	if (!storage)
	{
		storage = ft_strdup("");
		if (!storage)
			return (NULL);
	}
	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(storage);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		storage = ft_strjoin_free(storage, buffer, 0);
		if (!storage)
			return (NULL);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	storage[MAX_FD][BUFFER_SIZE];
	char		*result;
	char		*temp;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	temp = ft_strdup(storage[fd]);
	if (!temp)
		return (NULL);
	temp = read_loop(fd, temp);
	if (!temp || *temp == '\0')
	{
		free(temp);
		return (NULL);
	}
	temp = extract_and_trim(&result, temp);
	ft_strlcpy(storage[fd], temp, BUFFER_SIZE);
	free(temp);
	return (result);
}
