/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:05:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/24 11:24:02 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_dquotes(t_tokenizer *tmp, int *i)
{
	char		*str;

	str = NULL;
	while (tmp->token[*i])
	{
		if (tmp->token[*i] != '"')
			str = ft_freq_strjoin(str, ft_freq_substr(tmp->token, *i, *i + 1));
		if (tmp->token[*i])
			(*i)++;
	}
	return (str);
}

char	*remove_squotes(t_tokenizer *tmp, int *i)
{
	char		*str;

	str = NULL;
	while (tmp->token[*i])
	{
		if (tmp->token[*i] != '\'')
			str = ft_freq_strjoin(str, ft_freq_substr(tmp->token, *i, *i + 1));
		if (tmp->token[*i])
			(*i)++;
	}
	return (str);
}

static void	join_and_update(t_tokenizer **tmp)
{
	(*tmp)->token = ft_freq_strjoin((*tmp)->token, (*tmp)->next->token);
	(*tmp)->next = (*tmp)->next->next;
}

static void	process_quotes(t_tokenizer **tmp)
{
	if (*(*tmp)->next->stat == INQUOTES)
		*(*tmp)->stat = INQUOTES;
	else if (*(*tmp)->next->stat == INDQUOTES)
		*(*tmp)->stat = INDQUOTES;
	join_and_update(tmp);
}

void	join_tokens(t_tokenizer *token)
{
	t_tokenizer	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->joinable == 1 || (tmp->prev && tmp->prev->joinable == 1))
		{
			if (tmp->next && (*tmp->next->stat == INQUOTES \
			|| *tmp->next->stat == INDQUOTES))
				process_quotes(&tmp);
			else if (tmp->next)
				join_and_update(&tmp);
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
