/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 19:29:35 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/10/16 19:29:37 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert.h"

int     is_alpha(char c)
{
	if (c <= 'Z' && c >= 'A')
		return (1);
	return (0);
}

int        alpha_amb(t_expert *head, char alpha)
{
	t_expert *current = head;

	while (current != NULL)
	{
		if (current->alpha == alpha)
			return (current->f_facts);
		current = current->next;
	}
	return (0);
}

int		rule_validate(char *rules)
{
	int i;

	i = 0;
	if (!rules)
		return (0);
	while (rules[i])
	{
		if (rules[i] <= 'Z' && rules[i] >= 'A')
			i++;
		else
			return (0);
	}
	return (1);
}

int		main(int c, char **v)
{
	char 	*facts;
	char	**rules;
	char	*queries;

	if (c == 2 || (c == 3 && !strcmp(v[1], "-e")))
    {
		if (c == 3)
		{
			rules = get_instructions(v[2], &queries, &facts);
			g_view = 1;
		}
		else
		{
			g_view = 0;
			rules = get_instructions(v[1], &queries, &facts);
		}
	    if (rules && rule_validate(facts) && rule_validate(queries))
		    solver(rules, facts, queries);
        else
            printf("Error\n");
    }
	else
		printf("Error.\n");
	return (0);
}