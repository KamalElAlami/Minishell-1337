/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:20:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/01 13:07:16 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokenizer	*check_signle_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat)
{
	t_tokenizer	*node;
	int			k;
	char		*s;

	if (input[*i] == '\'')
	{	
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'' && input[*i] != '\0')
		{
			*stat = INQUOTES;
			s = ft_substr(input, k, *i);
			node = new_token(s, type, stat);
			return (node);
		}
		else
			return (printf("error with single quotes\n"), NULL);
	}
	return (printf("error with single quotes\n"), NULL);
}

t_tokenizer	*check_double_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat)
{
	t_tokenizer	*node;
	int			k;
	char		*s;

	if (input[*i] == '"')
	{	
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (input[*i] == '"' && input[*i] != '\0')
		{
			*stat = INDQUOTES;
			s = ft_substr(input, k, *i);
			node = new_token(s, type, stat);
			return (node);
		}
		else
			return (printf("error with double quotes\n"), NULL);
	}
	return (printf("error with double quotes\n"), NULL);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}
