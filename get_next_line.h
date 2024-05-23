/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyago-ra <pyago-ra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 00:06:50 by pyago-ra          #+#    #+#             */
/*   Updated: 2021/07/06 07:49:33 by pyago-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define FALSE 0
# define TRUE 1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlcat		(char *dst, char *src, size_t size);
void	*ft_calloc		(size_t nmemb, size_t size);
size_t	ft_strlen		(const char *s);
typedef struct s_file
{
	int				fd;
	size_t			index;
	char			*buffer;
	struct s_file	*next;
}	t_file;
void	remove_file		(t_file **root, t_file **file);
t_file	*create_file	(int fd, t_file **root);

int		get_next_line	(int fd, char **line);
#endif