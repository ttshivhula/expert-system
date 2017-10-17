/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 10:56:35 by qmanamel          #+#    #+#             */
/*   Updated: 2017/06/24 08:51:30 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	copy_contents(const int fd, char **container)
{
	int		chars_read;
	char	*buff;
	char	*tmp;

	buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (buff == NULL)
		return (-1);
	chars_read = read(fd, buff, BUFF_SIZE);
	{
		buff[chars_read] = '\0';
		tmp = ft_strjoin(*container, buff);
		free(*container);
		*container = tmp;
	}
	free(buff);
	return (chars_read);
}

static int	holder_and_pre_check(char **h, const int fd, char **eol, int *cr)
{
	int		rtn_val;

	if (*h == NULL)
		*h = (char*)malloc(sizeof(char));
	if (*h == NULL || fd < 0 || BUFF_SIZE < 0)
		rtn_val = -1;
	else
		rtn_val = 1;
	*eol = ft_strchr(*h, '\n');
	if (*eol != NULL)
		*cr = 2;
	return (rtn_val);
}

static void	pro_strjoin(char **holder, char *str1, char *str2)
{
	char	*tmp;

	tmp = *holder;
	*holder = ft_strjoin(str1, str2);
	free(tmp);
}

static void	pro_strdup(char **holder, char *str1)
{
	char	*tmp;

	tmp = *holder;
	*holder = ft_strdup(str1);
	free(tmp);
}

int			get_next_line(const int fd, char **line)
{
	static char	*holder = NULL;
	char		*end_of_line;
	int			chars_read;

	if (holder_and_pre_check(&holder, fd, &end_of_line, &chars_read) == -1)
		return (-1);
	while (end_of_line == NULL)
	{
		chars_read = copy_contents(fd, &holder);
		if (chars_read == 0)
		{
			if (ft_strlen(holder) == 0)
				return (0);
			pro_strjoin(&holder, holder, "\n");
			end_of_line = ft_strchr(holder, '\n');
		}
		else if (chars_read < 0)
			return (-1);
		else
			end_of_line = ft_strchr(holder, '\n');
	}
	*line = ft_strsub(holder, 0, ft_strlen(holder) - ft_strlen(end_of_line));
	pro_strdup(&holder, &(end_of_line[1]));
	return (1);
}
