/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/24 16:48:35 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     here_doc(t_tokenizer *delimiter, t_minishell *mini)
{
        char    *input;

        mini->fdin = open("/tmp/ana_machi_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (mini->fdin == -1)
                return (perror("open"), 0);
        while (1)
        {
                input = readline("> ");
                if (!input || !ft_strcmp(input, delimiter->token))
                {
                        free(input);
                        break ;
                }
                if (delimiter && (*delimiter->stat != INQUOTES || *delimiter->stat != INDQUOTES))
                        input = expansion(input, mini);
                write(mini->fdin, input, ft_strlen(input));
                write(mini->fdin, "\n", 1);
                free(input);
        }
        close(mini->fdin);
	mini->infile = open("/tmp/.ana_machi_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
        return (1);
}
