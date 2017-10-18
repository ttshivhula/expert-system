/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 10:28:44 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/10/18 09:17:07 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert.h"

static void     init_list(t_expert **list, char *facts, char *queries)
{
    while (*facts)
    {
        add_item(list, *facts, 1, 1);
        facts++;
    }
    while (*queries)
    {
        add_item(list, *queries, 0, 0);
        queries++;
    }
}

static int      check_error_in_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] <= 'Z' && line[i] >= 'A')
            i++;
        else if ((line[i] == '+') && ((line[i + 1] <= 'Z'
						&& line[i + 1] >= 'A') || (line[i + 1] == '!')))
            i++;
        else if ((line[i] == '|') && ((line[i + 1] <= 'Z'
						&& line[i + 1] >= 'A') || (line[i + 1] == '!')))
            i++;
        else if ((line[i] == '^') && ((line[i + 1] <= 'Z'
						&& line[i + 1] >= 'A') || (line[i + 1] == '!')))
            i++;
        else if (ft_strncmp(line + i, "=>", 2) == 0)
            i+=2;
        else if (ft_strncmp(line + i, "<=>", 3) == 0)
            i+=3;
        else if ((line[i] == '!') && (line[i + 1] <= 'Z' && line[i + 1] >= 'A'))
            i++;
        else
            return (-1);
    }
    return (1);
}

static int     check_error_n_solve(t_expert **list, char **rules, char **error)
{
    int     i;

    (void)list;
    i = -1;
    while (rules[++i])
    {
        if (check_error_in_line(rules[i]) == -1)
        {
            *error = ft_strdup(rules[i]);
            return (-1);
        }
    }
    return (1);
}

void            solver(char **rules, char *facts, char *queries)
{
    t_expert    *list;
    char        *error;

    list = NULL;
    init_list(&list, facts, queries);
    if (check_error_n_solve(&list, rules, &error) == -1)
    {
        printf("Error in line: %s\n", error);
        free(error);
        return ;
    }
    print_results(list, queries);
}
