/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 18:14:00 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/10/27 10:36:21 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert.h"

void				print_false(t_expert *head, char *queries)
{
	t_expert	*current;

	while (*queries)
	{
		current = head;
		while (current != NULL)
		{
			if (current->alpha == *queries)
			{
				if (!current->status)
				{
					sleep(1);
					printf("Sadly \x1b[31m%c\x1b[0m remains false\n", *queries);
				}
			}
			current = current->next;
		}
		queries++;
	}
}

int					edit_value(t_expert **head, char alpha, int status, int amb)
{
	t_expert	*current;

	current = *head;
	if (*head == NULL)
		return (0);
	while (current != NULL)
	{
		if (current->alpha == alpha)
		{
			if (current->status == status)
				return (0);
			else
			{
				current->f_facts = amb;
				current->status = status;
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

void				print_results(t_expert *head, char *queries)
{
	t_expert	*current;

	while (*queries)
	{
		current = head;
		while (current != NULL)
		{
			if (current->alpha == *queries)
			{
				printf("\x1b[34m%c\x1b[0m is ", *queries);
				if (current->status && !current->f_facts)
					printf("\x1b[32mtrue\x1b[0m\n");
				else if (current->status && current->f_facts)
					printf("\x1b[33mambiguous\x1b[0m\n");
				else
					printf("\x1b[31mfalse\x1b[0m\n");
			}
			current = current->next;
		}
		queries++;
	}
}

int					alpha_status(t_expert *head, char alpha)
{
	t_expert	*current;

	current = head;
	while (current != NULL)
	{
		if (current->alpha == alpha)
			return (current->status);
		current = current->next;
	}
	return (0);
}

void				free_list(t_expert *head)
{
	t_expert	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
