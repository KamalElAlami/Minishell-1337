/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/24 11:22:48 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_pipe_error(t_tokenizer *token)
{
	return (printf("syntax error near unexpected token `%s'\n", \
		token->token), 258);
}

static int	handle_redirection_error(t_tokenizer *token)
{
	return (printf("syntax error near unexpected token `%s'\n", \
		token->token), 258);
}

static int	check_syntax_errors(t_tokenizer *token)
{
	if (*token->type == PIPE && !token->next)
		return (handle_pipe_error(token));
	if ((*token->type == LESS || *token->type == GREAT \
		|| *token->type == GREATGREAT) \
			&& token->next && (*token->next->type == LESS \
				|| *token->next->type == GREAT \
					|| *token->next->type == GREATGREAT))
		return (handle_redirection_error(token));
	return (0);
}

int	check_validation(t_tokenizer *token, t_minishell *mini)
{
	if (token && *token->type == PIPE)
		return (handle_pipe_error(token));
	while (token)
	{
		if (g_exit_stts == 6)
			return (-1);
		if (*token->type != WORD && !token->next)
			return (handle_pipe_error(token));
		if (*token->type == LESSLESS && *token->next->type == WORD)
			if (!here_doc(token->next, mini))
				return (-1);
		if (check_syntax_errors(token))
			return (258);
		if (ft_strchr(token->token, '$') && *token->stat != INQUOTES)
			token->token = expansion(token->token, mini);
		token = token->next;
	}
	return (1);
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
