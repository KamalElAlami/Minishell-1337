/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:28 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/14 02:37:22 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void free_array(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
void safe_clean(t_minishell *mini, t_cmd **cmds, t_tokenizer **lexer)
{
    if (mini->line)
    {
        free(mini->line);
        mini = NULL;
    }
    if (lexer && *lexer)
    {
        clear_token(lexer, free);
        *lexer = NULL;
    }
    if (cmds && *cmds)
    {
        clear_cmd(cmds);
        *cmds = NULL;
    }
}
