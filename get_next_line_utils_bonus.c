/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyago-ra <pyago-ra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 00:18:58 by pyago-ra          #+#    #+#             */
/*   Updated: 2021/07/05 21:46:44 by pyago-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	index;
	char	*output;

	index = 0;
	output = (char *)malloc(nmemb * size);
	if (output == NULL)
		return (NULL);
	while (index < nmemb * size)
		output[index++] = 0;
	return (output);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (s != NULL)
		while (*(s++))
			size++;
	return (size);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	count;
	size_t	s_dst;
	size_t	s_src;

	count = 0;
	s_dst = ft_strlen(dst);
	s_src = ft_strlen(src);
	if (size <= s_dst)
		return (size + s_src);
	while (dst[count])
		count++;
	while (*src && count < size - 1)
	{
		dst[count++] = *src;
		*src = 0;
		src++;
	}
	dst[count] = '\0';
	return (s_dst + s_src);
}

void	remove_file(t_file **root, t_file **file)
{
	t_file	*aux;

	if (file && *file && root)
	{
		free((*file)->buffer);
		(*file)->buffer = NULL;
		if (*root == *file)
			*root = (*file)->next;
		else
		{
			aux = *root;
			while (aux->next != *file)
				aux = aux->next;
			aux->next = (*file)->next;
		}
		free(*file);
		*file = NULL;
	}
}

t_file	*create_file(int fd, t_file **root)
{
	t_file	*aux;
	t_file	*new_file;

	new_file = (t_file *)malloc(sizeof(t_file));
	if (new_file == NULL)
		return (NULL);
	new_file->fd = fd;
	new_file->buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (new_file->buffer == NULL)
	{
		free(new_file);
		return (NULL);
	}
	new_file->index = 0;
	new_file->next = NULL;
	if (*root == NULL)
		*root = new_file;
	else
	{
		aux = *root;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new_file;
	}
	return (new_file);
}
