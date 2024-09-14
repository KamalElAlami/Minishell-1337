/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tax_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:26:42 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/13 23:26:47 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void collect_taxes(t_collector **taxes)
{
    t_collector *current;
    t_collector *temp;

    if (!taxes || !*taxes)
        return;

    current = *taxes;
    while (current)
    {
        temp = current;
        current = current->next;
        free(temp->ptr);
        free(temp);
    }
    *taxes = NULL;
}

static void appand_taxes(t_collector **taxes, void *ptr)
{
    t_collector *new_tax = malloc(sizeof(t_collector));
    if (!new_tax)
    {
        perror("malloc");
        collect_taxes(taxes);
        exit(1);
    }
    new_tax->ptr = ptr;
    new_tax->next = *taxes;
    *taxes = new_tax;
}

void *o_malloc(size_t size, int flag)
{
    static t_collector *taxes = NULL;
    // static int allocation_count = 0;
    
    if (flag == 0)
    {
        void *ptr = malloc(size);
        if (!ptr)
        {
            perror("malloc");
            collect_taxes(&taxes);
            exit(1);
        }
        appand_taxes(&taxes, ptr);
        // allocation_count++;
        // printf("Allocation %d: %zu bytes at %p\n", allocation_count, size, ptr);
        return ptr;
    }
    else
    {
        // printf("Freeing all allocations. Total allocations: %d\n", allocation_count);
        collect_taxes(&taxes);
        // allocation_count = 0;
    }
    return NULL;
}
