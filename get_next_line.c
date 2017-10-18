/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 11:28:19 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/14 14:12:54 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		reader(const int fd, char **container)
{
	int			count;
	char		*buff;
	char		*tmp;

	if (!(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	count = read(fd, buff, BUFF_SIZE);
	buff[count] = '\0';
	tmp = ft_strjoin(*container, buff);
	free(*container);
	*container = tmp;
	free(buff);
	return (count);
}

static int		checker(char **holder, const int fd, char **end_of_line)
{
	int			ret;

	if (*holder == NULL)
		*holder = (char *)malloc(sizeof(char));
	if (*holder == NULL || fd < 0 || BUFF_SIZE < 0)
		ret = -1;
	else
		ret = 1;
	*end_of_line = ft_strchr(*holder, '\n');
	return (ret);
}

static void		free_join(char **holder, char *s1, char *s2)
{
	char		*tmp;

	tmp = *holder;
	*holder = ft_strjoin(s1, s2);
	free(tmp);
}

static	void	free_duplicate(char **holder, char *s)
{
	char		*tmp;

	tmp = *holder;
	*holder = ft_strdup(s);
	free(tmp);
}

int				get_next_line(const int fd, char **line)
{
	static char		*holder = NULL;
	char			*end_of_line;
	int				count;

	if (checker(&holder, fd, &end_of_line) == -1)
		return (-1);
	while (end_of_line == NULL)
	{
		count = reader(fd, &holder);
		if (count == 0)
		{
			if (ft_strlen(holder) == 0)
				return (0);
			free_join(&holder, holder, "\n");
			end_of_line = ft_strchr(holder, '\n');
		}
		else if (count < 0)
			return (-1);
		else
			end_of_line = ft_strchr(holder, '\n');
	}
	*line = ft_strsub(holder, 0, ft_strlen(holder) - ft_strlen(end_of_line));
	free_duplicate(&holder, &(end_of_line[1]));
	return (1);
}
