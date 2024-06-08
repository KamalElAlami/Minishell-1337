/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/08 11:39:01 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     here_doc(t_tokenizer *token, t_tokenizer *delimiter, t_minishell *mini)
{
        char    *input;
        (void)token;

        mini->fdin = open("/tmp/ana_machi_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (mini->fdin == -1)
                return (perror("open"), 0);
        while (1)
        {
                input = readline("> ");
                if (!input || !ft_strcmp(input, delimiter->token))
                        break ;
                write(mini->fdin, input, ft_strlen(input));
                write(mini->fdin, "\n", 1);
                free(input);
        }
        close(mini->fdin);
        return (1);
}
