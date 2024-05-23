/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyago-ra <pyago-ra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 00:07:45 by pyago-ra          #+#    #+#             */
/*   Updated: 2021/07/06 07:52:11 by pyago-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*get_file(int fd, t_file **root)
{
	t_file	*aux;

	aux = *root;
	while (aux != NULL)
	{
		if (aux->fd == fd)
			return (aux);
		aux = aux->next;
	}
	return (create_file(fd, root));
}

static char	*ft_strcat(char *s1, char *s2, size_t size)
{
	size_t	index;
	char	*new_str;

	index = 0;
	size = ft_strlen(s1) + size + (size_t)1;
	new_str = (char *)ft_calloc(size, sizeof(char));
	if (s1)
	{
		while (s1[index])
		{
			new_str[index] = s1[index];
			index++;
		}
		free(s1);
	}
	if (s2 && *s2 != 10)
	{
		while (index < (size - 1))
		{
			new_str[index] = *s2;
			*(s2++) = 0;
			index++;
		}
	}
	return (new_str);
}

static int	read_buffer(t_file *file, char **str, int *to_continue)
{
	size_t	size;
	char	*start;

	*to_continue = TRUE;
	if (file->buffer[file->index] == 0)
		return (FALSE);
	size = 0;
	start = &file->buffer[file->index];
	while (file->buffer[file->index] != 0)
	{
		if (file->buffer[file->index] == 10)
		{
			file->buffer[file->index] = 0;
			file->index++;
			*to_continue = FALSE;
			break ;
		}
		size++;
		file->index++;
	}
	*str = ft_strcat(*str, start, size + 1);
	if (file->index >= BUFFER_SIZE)
		file->index = 0;
	return (TRUE);
}

static void	valid_output(int cc, char **line, t_file **file, t_file **root)
{
	if (cc < 0)
	{
		if (*line)
			free(*line);
		*line = NULL;
	}
	else if ((*file)->buffer[(*file)->index] == 0)
		if (*line == NULL)
			*line = ft_strcat(*line, NULL, 0);
	remove_file(root, file);
}

int	get_next_line(int fd, char **line)
{
	static t_file	*root;
	t_file			*file;
	int				to_continue;
	int				count_content;

	*line = NULL;
	file = get_file(fd, &root);
	to_continue = 1;
	count_content = 1;
	while (file && count_content > FALSE && to_continue)
	{
		count_content = read_buffer(file, line, &to_continue);
		if (count_content == FALSE && to_continue)
			count_content = read(fd, file->buffer, BUFFER_SIZE);
	}
	if (count_content > 0)
		return (TRUE);
	valid_output(count_content, line, &file, &root);
	return (count_content);
}
