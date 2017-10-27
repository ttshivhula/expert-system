/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 10:28:40 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/10/27 10:35:13 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert.h"

static int		in_list(t_expert *head, char alpha)
{
	t_expert *current;

	current = head;
	while (current != NULL)
	{
		if (current->alpha == alpha)
			return (1);
		current = current->next;
	}
	return (0);
}

static int		new_item(t_expert **head, char alpha, int f_facts, int status)
{
	*head = malloc(sizeof(t_expert));
	if (*head == NULL)
		return (1);
	(*head)->alpha = alpha;
	(*head)->status = status;
	(*head)->f_facts = f_facts;
	(*head)->next = NULL;
	return (1);
}

int				add_item(t_expert **head, char alpha, int f_facts, int status)
{
	t_expert	*new_node;

	if (*head == NULL)
		return (new_item(head, alpha, f_facts, status));
	else
	{
		if (!in_list(*head, alpha))
		{
			new_node = malloc(sizeof(t_expert));
			new_node->alpha = alpha;
			new_node->status = status;
			new_node->f_facts = f_facts;
			new_node->next = *head;
			*head = new_node;
			return (1);
		}
	}
	return (0);
}
