/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:22:05 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/19 18:34:39 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		line_copy(char **line, char *content, char c)
{
	size_t	i;
	char	*tmp;
	size_t	n;
	char	*s2;

	i = 0;
	n = 0;
	tmp = *line;
	while (content[n] && content[n] != c)
		n++;
	i = 0;
	if (!(s2 = ft_strnew(n)))
		return (0);
	while (content[i] && i < n)
	{
		s2[i] = content[i];
		i++;
	}
	*line = s2;
	if (!line)
		return (0);
	return ((int)n);
}

t_list	*ft_check_and_create_lst(int fd, t_list **head)
{
	t_list	*tmp;

	if (!head)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(head, tmp);
	return (tmp);
}

int		read_line(const int fd, char **content, char *buf)
{
	int		pos;
	char	*tmp;

	while ((pos = read(fd, buf, BUFF_SIZE)))
	{
		buf[pos] = '\0';
		tmp = *content;
		if (!(*content = ft_strjoin(*content, buf)))
			return (-1);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (pos);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	size_t			new_pos;
	static t_list	*head;
	t_list			*acc;
	char			*tmp;

	if (fd < 0 || !line || (read(fd, buf, 0)) < 0 ||
			(!(acc = ft_check_and_create_lst(fd, &head))))
		return (-1);
	tmp = acc->content;
	if ((new_pos = read_line(fd, &tmp, buf)) == -1)
		return (-1);
	acc->content = tmp;
	if (!new_pos && !*tmp)
		return (0);
	new_pos = line_copy(line, acc->content, '\n');
	tmp = acc->content;
	if (tmp[new_pos] != '\0')
	{
		acc->content = ft_strdup(&((acc->content)[new_pos + 1]));
		free(tmp);
	}
	else
		tmp[0] = '\0';
	return (1);
}
