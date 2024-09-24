/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:35:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/24 10:52:47 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_counters(int *index, int *count)
{
	index[0] = 0;
	index[1] = 0;
	count[0] = 0;
	count[1] = 0;
}

void	handle_word_token(t_tokenizer *tmp, t_cmd *new, int *i)
{
	char	**s;
	int		j;

	j = 0;
	s = NULL;
	if (ft_strchr(tmp->token, ' ') && *tmp->stat == GENERAL)
	{
		s = ft_freq_split(tmp->token, ' ');
		while (s && s[j])
			new->cmd[(*i)++] = ft_freq_strdup(s[j++]);
	}
	else
		new->cmd[(*i)++] = ft_freq_strdup(tmp->token);
}

void	handle_non_word_token(t_tokenizer **tmp, t_cmd *new, int *j)
{
	new->red[(*j)++] = ft_freq_strdup((*tmp)->token);
	new->red[(*j)++] = ft_freq_strdup((*tmp)->next->token);
	*tmp = (*tmp)->next;
}

void	fill_exec_process(t_tokenizer **tmp, int *index, t_cmd **new)
{
	while (*tmp && *(*tmp)->type != PIPE)
	{
		if (*tmp && *(*tmp)->stat == GENERAL && ft_strlen((*tmp)->token) == 0)
			*tmp = (*tmp)->next;
		else
		{
			if (*(*tmp)->type == WORD)
				handle_word_token(*tmp, *new, &index[0]);
			else
				handle_non_word_token(tmp, *new, &index[1]);
			*tmp = (*tmp)->next;
		}
	}
}

void	send_to_execution(t_tokenizer *token, t_cmd **cmd)
{
	t_cmd		*new;
	t_tokenizer	*tmp;
	int			index[2];
	int			count[2];

	tmp = token;
	while (tmp)
	{
		init_counters(index, count);
		count_len(tmp, &count[0], &count[1]);
		if (ft_strchr(tmp->token, ' ') && *tmp->stat == GENERAL)
			count[0] = ft_split_len(ft_freq_split(tmp->token, ' '));
		new = new_cmd(count[0], count[1], tmp->stat, ft_strlen(tmp->token));
		fill_exec_process(&tmp, index, &new);
		append_to_exec(cmd, new);
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}
