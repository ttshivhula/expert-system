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

static int      check_truth(t_expert **head, char *first)
{
    int i;
    int back_truth;

    i = -1;
    back_truth = 0;
    while (first[++i])
    {
        if (is_alpha(first[i]))
        {
            if (alpha_status(*head, first[i]) && first[i - 1] != '!' && first[i - 1] != '^' && first[i - 1] != '+')
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
                if (alpha_status(*head, first[i + 1]))
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
        else
        {
            if (!alpha_status(*head, first[i + 1]) && (i - 1 < 0))
                back_truth = 1;
        }
    }
    return (back_truth);
}

static void     break_into_two(char *line, char **first, char **last)
{
    int     i;

    i = -1;
    while (line[++i])
    {
        if (line[i] == '>')
            *last = ft_strdup(line + i + 1);
    }
    i = -1;
    while (line[++i])
    {
        if (line[i] == '=' || line[i] == '<')
            *first = ft_strsub(line, 0, i);
    }
}

static int     make_true(t_expert **head, char *line)
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
                ret = edit_value(head, line[i], 1);
        }
    }
    return (ret);
}

void            algo(t_expert **head, char **rules)
{
    int     i;
    char    *first;
    char    *last;
    int     t;

    t = 0;
    while (t < 100)
    {
        i = -1;
        while (rules[++i])
        {
            break_into_two(rules[i], &first, &last);
            if (check_truth(head, first))
                make_true(head, last);
        }
        t++;
    }
}