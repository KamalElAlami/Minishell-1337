/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/05 19:35:32 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     here_doc(t_tokenizer *delimiter, t_minishell *mini)
{
        char    *input;

        unlink("/tmp/ana_machi_heredoc");
        mini->fdin = open("/tmp/ana_machi_heredoc", O_CREAT | O_WRONLY , 0644);
        if (mini->fdin == -1)
                return (perror("open"), 0);
        while (1)
        {
                input = readline("> ");
                if (!input || (!ft_strncmp(input, delimiter->token, ft_strlen(delimiter->token)) && ft_strlen(input) == ft_strlen(delimiter->token)))
                {
                        free(input);
                        break ;
                }
                if (*delimiter->stat == GENERAL)
                        input = expansion(input, mini);
                write(mini->fdin, input, ft_strlen(input));
                write(mini->fdin, "\n", 1);
        }
	mini->infile = open("/tmp/ana_machi_heredoc", O_RDONLY, 0777);
        if (!mini->infile)
                return (perror("open"), 0);
        close(mini->fdin);
        return (1);
}
