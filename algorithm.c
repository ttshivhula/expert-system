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

static int      or_exist(char *line)
{
    int pr;
    int i;

    pr = 0;
    i = 0;
    while (*line)
    {
        if (*line == '(')
            pr++;
        if (*line == '|')
            i++;
        line++;
    }
    if (i & !pr)
        return (1);
    return (0);
}

int             check_truth(t_expert **head, char *first, int back_truth, int fuck)
{
    int i;
    int ex;
    int prev;

    i = -1;
    ex = 0;
    prev = 0;
    while (first[++i])
    {
        if (is_alpha(first[i]))
        {
            if (alpha_status(*head, first[i]) && first[i - 1] != '!' && first[i - 1] != '^' && first[i - 1] != '+')
                back_truth = 1;
            if (alpha_amb(*head, first[i]))
                back_truth = 1;
        }
        else if (first[i] == '|')
        {
            if (!back_truth)
            {
                if (is_alpha(first[i + 1]))
                {
                    if (alpha_status(*head, first[i + 1]))
                        back_truth = 1;
                }
                else
                {
                    if (!alpha_status(*head, first[i + 2]))
                        back_truth = 1;
                }
            }
            else
                ex++;
            if (ex && or_exist(first) && !fuck)
                return (1);
        }
        else if (first[i] == '+')
        {
            if (back_truth)
            {
                if (first[i + 1] == '!' && alpha_status(*head, first[i + 2]))
                    back_truth = 0;
                if (is_alpha(first[i + 1]))
                {
                    if (!alpha_status(*head, first[i + 1]))
                        back_truth = 0;
                }
            }
            else
                back_truth = 0;
        }
        else if (first[i] == '^')
        {
            if (back_truth)
            {
                if (first[i + 1] == '!' && !alpha_status(*head, first[i + 2]))
                    back_truth = 0;
                if (alpha_status(*head, first[i + 1]) && !alpha_amb(*head, first[i + 1]))
                    back_truth = 0;
            }
            else
            {
                if (first[i + 1] == '!' && !alpha_status(*head, first[i + 2]))
                    back_truth = 1;
                if (alpha_status(*head, first[i + 1]))
                    back_truth = 1;
            }
        }
        else if (first[i] == '(' || first[i] == ')')
        {
            if (first[i] == '(')
            {
                if (first[i - 1] == '!')
                    prev = 1;
                back_truth = check_truth(head, first + i + 1, back_truth, 1);
                while (first[i] && first[i] != ')')
                    i++;
                if (back_truth && prev)
                    back_truth = 0;
                else if (!back_truth && prev)
                    back_truth = 1;
            }
        }
        else
        {
            if (!alpha_status(*head, first[i + 1]) && (i - 1 < 0))
                back_truth = 1;
        }
    }
    return (back_truth);
}

static int     break_into_two(char *line, char **first, char **last)
{
    int     i;
    int     k;
    int     ret;

    i = -1;
    k = 0;
    ret = 0;
    while (line[++i])
    {
        if (line[i] == '>')
        {
            *last = ft_strdup(line + i + 1);
            k++;
        }
    }
    i = -1;
    while (line[++i])
    {
        if (line[i] == '=' || line[i] == '<')
        {
            if (line[i] == '<')
                ret = 1;
            *first = ft_strsub(line, 0, i);
            k++;
        }
    }
    if (k != 2 && k != 3)
    {
        printf("\x1b[31mThere is an error in line: \x1b[34m%s\x1b[0m\n", line);
        exit(1);
    }
    return (ret);
}

static int     make_true(t_expert **head, char *line, char *first, int prev_amb)
{
    int i;
    int ret;

    i = -1;
    ret = 0;
    while (line[++i])
    {
        if (is_alpha(line[i]))
        {
            if (line[i - 1] != '!')
            {
                if (line[i - 1] == '|' || line[i + 1] == '|' || line[i - 1] == '^' || line[i + 1] == '^' || prev_amb)
                    ret += edit_value(head, line[i], 1, 1);
                else
                    ret += edit_value(head, line[i], 1, 0);
            }
            if (line[i - 1] == '!')
            {
                if (alpha_status(*head, line[i]))
                {
                    printf("\x1b[31mThere is a contradiction with \x1b[34m%c\x1b[0m\n", line[i]);
                    exit(1);
                }
            }
        }
    }
    if (ret && g_view)
    {
        sleep(1);
        printf("\x1b[34m%s\x1b[0m is now true because \x1b[36m%s\x1b[0m is true and implies \x1b[34m%s\x1b[0m\n", line, first, line);
    }
    return (ret);
}

static int      prev_amb(char *line, t_expert *head)
{
    t_expert *current;

    while (*line)
    {
        current = head;
        while (current != NULL)
        {
            if (current->alpha == *line)
            {
                if (current->f_facts == 1)
                    return (1);
            }
            current = current->next;
        }
        line++;
    }
    return (0);
}

void            algo(t_expert **head, char **rules)
{
    int     i;
    char    *first;
    char    *last;
    int     t;

    while (1)
    {
        i = -1;
        t = 0;
        while (rules[++i])
        {
            if (!break_into_two(rules[i], &first, &last))
            {
                if (check_truth(head, first, 0, 0))
                    t = make_true(head, last, first, prev_amb(first, *head));
            }
            else
            {
                if (check_truth(head, last, 0, 0))
                    t = make_true(head, first, last, prev_amb(last, *head));
            }
            if (first)
                free(first);
            if (last)
                free(last);
        }
        if (!t)
            break ;
    }
    i = -1;
    while (rules[++i])
        free(rules[i]);
    free(rules);

}