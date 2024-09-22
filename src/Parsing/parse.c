/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/21 21:25:03 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_validation(t_tokenizer *token, t_minishell *mini)
{
	if (token && *token->type == PIPE)
		return (printf("syntax error near unexpected token `%s'\n", \
			token->token), 258);
	while (token)
	{
		if (g_exit_stts == 6)
			return (-1);
		if (token && *token->type != WORD && !token->next)
			return (printf("syntax error near unexpected token `%s'\n", \
				token->token), 258);
		if (*token->type == LESSLESS && *token->next->type == WORD)
			if (!here_doc(token->next, mini))
		if (*token->type == PIPE && *token->type == PIPE)
			return (printf("syntax error near unexpected token `%s'\n", \
				token->token), 258);
		if (*token->type == LESS || *token->type == GREAT || *token->type == GREATGREAT)
		{
			if (token->next)
				if (*token->next->type == LESS || *token->next->type == GREAT || *token->next->type == GREATGREAT)
					return (printf("syntax error near unexpected token `%s'\n", \
						token->token), 258);
		}
		if (ft_strchr(token->token, '$') && *token->stat != INQUOTES)
			token->token = expansion(token->token, mini);
		token = token->next;
	}
	return (1);
}

void	remove_quotes(t_tokenizer *token)
{
	t_tokenizer	*tmp;
	int			i;
	char		*str;
	char		*old_token;

	tmp = token;
	while (tmp)
	{
		i = 0;
		if (*tmp->stat == INDQUOTES || *tmp->stat == INQUOTES)
		{
			if (*tmp->stat == INDQUOTES)
				str = remove_dquotes(tmp, &i);
			else
				str = remove_squotes(tmp, &i);
			if (str)
			{
				old_token = tmp->token;
				tmp->token = str;
			}
		}
		tmp = tmp->next;
	}
}

void	join_tokens(t_tokenizer *token)
{
	t_tokenizer	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->joinable == 1 || (tmp->prev && tmp->prev->joinable == 1))
		{
			if (tmp->next && *tmp->next->stat == INQUOTES)
			{
				*tmp->stat = INQUOTES;
				tmp->token = ft_freq_strjoin(tmp->token, tmp->next->token);
				tmp->next = tmp->next->next;
			}
			else if (tmp->next && *tmp->next->stat == INDQUOTES)
			{
				*tmp->stat = INDQUOTES;
				tmp->token = ft_freq_strjoin(tmp->token, tmp->next->token);
				tmp->next = tmp->next->next;
			}
			else
			{
					if (tmp->next)
					{
						tmp->token = ft_freq_strjoin(tmp->token, tmp->next->token);
						tmp->next = tmp->next->next;
					}
					else
						tmp = tmp->next;
			}
		}
		else
			tmp = tmp->next;
	}
}

void	parse_input(t_minishell *mini, t_cmd **cmds)
{
	int	checker;

	checker = check_validation(mini->start, mini);
	if (checker == 258)
	{
		mini->ret_value = 258;
		return ;
	}
	if (checker == -1)
	{
		mini->ret_value = 1;
		return ;
	}
	join_tokens(mini->start);
	if (mini->start)
	{
		send_to_execution(mini->start, cmds);
		mini->cmd = *cmds;
		mini->ret_value = execution(mini, *cmds);
	}
}
