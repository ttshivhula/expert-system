/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 18:14:00 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/10/17 18:14:03 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert.h"

static int  in_list(t_expert *head, char alpha)
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

void        add_item(t_expert   **head, char alpha, int f_facts, int status)
{
    t_expert    *new_node;

    if (*head == NULL)
    {
        *head = malloc(sizeof(t_expert));
        if (*head == NULL) {
            return ;
        }
        (*head)->alpha = alpha;
        (*head)->status = status;
        (*head)->f_facts = f_facts;
        (*head)->next = NULL;
    }
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
        }
    }
}

void        print_list(t_expert *head)
{
    t_expert *current = head;

    printf("Debug\n");
    while (current != NULL)
    {
        printf("alpha: %c f_facts: %d status: %d\n", current->alpha, current->f_facts, current->status);
        current = current->next;
    }
    printf("End of Debug\n");
}

void        edit_value(t_expert **head, char alpha, int status)
{

    while (*head != NULL)
    {
        if ((*head)->alpha == alpha)
            (*head)->status = status;
        *head = (*head)->next;
    }
}

void        print_results(t_expert *head, char *queries)
{
    t_expert *current;

    while (*queries)
    {
        current = head;
        while (current != NULL)
        {
            if (current->alpha == *queries)
            {
                printf("\x1b[34m%c\x1b[0m is ", *queries);
                if (current->status)
                    printf("\x1b[32mtrue\x1b[0m\n");
                else
                    printf("\x1b[31mfalse\x1b[0m\n");
            }
            current = current->next;
        }
        queries++;
    }
}