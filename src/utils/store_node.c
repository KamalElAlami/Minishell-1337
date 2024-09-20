/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 06:08:52 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/19 17:48:21 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append_token(t_tokenizer **tokens, t_tokenizer *token)
{
	t_tokenizer	*head;

	if (!tokens)
		return ;
	if (!*tokens)
	{
		*tokens = token;
		return ;
	}
	head = *tokens;
	while (head->next)
		head = head->next;
	head->next = token;
	token->prev = head;
}

t_tokenizer	*new_token(void *content, t_lexer *type, \
	t_stat *stat, bool joinable)
{
	t_tokenizer	*head;

	head = o_malloc(sizeof(t_tokenizer), 0);
	if (!head)
		return (NULL);
	head->token = content;
	head->type = type;
	head->stat = stat;
	head->len = ft_strlen((char *)content);
	head->joinable = joinable;
	head->prev = NULL;
	head->next = NULL;
	return (head);
}

void	del_one_token(t_tokenizer *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->token);
	free(lst);
}

void	clear_token(t_tokenizer **lst, void (*del)(void *))
{
	t_tokenizer	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del_one_token(*lst, del);
		*lst = tmp;
	}
}
