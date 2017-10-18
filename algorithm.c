/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:39:04 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/10/18 12:39:15 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert.h"

static  char    *work_with(char *line, int after)
{
    int     i;

    if (after)
    {
        while (*line)
        {
            if (*line == '>')
                return (ft_strdup(line + 1));
            line++;
        }
    }
    else
    {
        i = -1;
        while (line[++i])
        {
            if (line[i] == '=' || line[i] == '<')
            {
                return (ft_strsub(line, 0, i));
            }
        }
    }
    return (NULL);
}

/*static  int     half_solve(t_expert **head, char *half)
{
    int     i;

    i = -1;
    while (half[++i])
    {

    }
}*/

static int      after_or_before(t_expert **head, char *line, int after)
{
    int     i;
    char    *curr;
    int     ret;

    i = -1;
    ret = 0;
    curr = work_with(line, after);
    while (curr[++i])
    {
        if (is_alpha(curr[i]) && alpha_status(*head, curr[i]) && (curr[i - 1] != '!'))
            ret = 1;
    }
    return (ret);
}

static  int     alpha_pos(char *line, char alpha)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (line[++i])
    {
        if (ft_strncmp(line + i, "=>", 2) == 0)
            j = 1;
        if (line[i++] == alpha && j)
            return (1);
        if (line[i++] == alpha)
            return (0);
        i++;
    }
    return (0);
}

static void     solve_half(t_expert **head, char *line)
{
    int     i;

    i = -1;
    while (line[++i])
    {
        if (is_alpha(line[i]) && line[i - 1] != '!')
        {
            //printf("alpha: %c pos: %d\n", line[i], alpha_pos(line, line[i]));
            if (after_or_before(head, line, alpha_pos(line, line[i])))
            {
                edit_value(head, line[i], 1);
            }
        }
    }
}

void            algo(t_expert **head, char **rules)
{
    int     i;

    i = -1;
    while (rules[++i])
    {
        solve_half(head, rules[i]);
    }
}