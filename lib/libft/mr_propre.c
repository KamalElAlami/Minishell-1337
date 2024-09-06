/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_propre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:15:19 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/06 15:05:14 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_propre	*create_addr(void *addr)
{
	t_propre	*new;

	new = (t_propre *)malloc(sizeof(t_propre));
	new->addr = addr;
	new->next = NULL;
	return (new);
}

void	append_address(t_propre **head, void *addr)
{
	t_propre	*new;
	t_propre	*last;

	new = create_addr(addr);
	if (!*head)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	mr_propre(t_propre *prop)
{
	t_propre	*tmp;

	while (prop)
	{
		tmp = prop;
		prop = prop->next;
		free(tmp->addr);
		free(tmp);
	}
}

void	*o_malloc(size_t size)
{
	static t_propre		*propre;
	void				*addr;

	addr = malloc(size);
	if (!addr)
	{
		ft_putstr_fd("malloc error\n", 2);
		mr_propre(propre);
		exit(1);
	}
	append_address(&propre, create_addr(addr));
	return (addr);
}
