/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 09:22:55 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/10/17 09:23:06 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert.h"

char	*ignore_comment(char *str)
{
	int		i;
	int		j;
	char 	*ret;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '#')
	{
		if (str[i] != ' ' && str[i] != '\t')
			j++;
		i++;
	}
	ret = (char *)malloc(sizeof(char) * j + 2);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '#')
	{
		if (str[i] != ' ' && str[i] != '\t')
			ret[j++] = str[i];
		i++;
	}
	if (j >= 1)
		ret[j++] = '\n';
	ret[j] = '\0';
	return (ret);
}

int		reader(char *file, char **instructions)
{
	char 	*line;
	int		fd;
	char	*tmp;
	char	*fre;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	*instructions = ft_strnew(1);
	while (get_next_line(fd, &line))
	{
		fre = *instructions;
		tmp = ignore_comment(line);
		*instructions = ft_strjoin(*instructions, tmp);
		free(tmp);
		free(fre);
		free(line);
	}
	return (1);
}

char	**get_instructions(char *file, char **queries, char **facts)
{
    char    *inst;
	char    **spl;
	char	**rules;
    int     i;
    int     j;

	i = 0;
	if (reader(file, &inst) == -1)
        return (NULL);
	if (strlen((inst = ft_strtrim(inst))))
		spl = ft_strsplit(inst, '\n');
	else
		return (NULL);
    while (spl[i])
    {
        if (spl[i][0] == '=')
            *facts = ft_strdup(spl[i] + 1);
        if (spl[i][0] == '?')
            *queries = ft_strdup(spl[i] + 1);
        i++;
    }
   	i = 0;
    j = 0;
    while (spl[i])
    {
        if (spl[i][0] != '=' && spl[i][0] != '?')
            j++;
        i++;
    }
    rules = (char **)malloc(sizeof(char *) * (j + 1));
    i = 0;
    j = 0;
    while (spl[i])
    {
        if (spl[i][0] != '=' && spl[i][0] != '?')
            rules[j++] = ft_strdup(spl[i]);
        i++;
    }
    rules[j] = NULL;
    return (rules);
}