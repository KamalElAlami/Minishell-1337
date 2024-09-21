/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:05:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/21 02:54:41 by kael-ala         ###   ########.fr       */
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
