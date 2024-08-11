/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/07 09:52:11 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     check_unset(char c)
{
        return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || c == '>' || c == '<');
}

int     unset(t_cmd *cmd, t_env **env)
{
        int     i;
        int     j;
        t_env   *tmp;

        i = 1;
        while (cmd->cmd[i])
        {
                j = 0;
                while (cmd->cmd[i][j])
                {
                        if (!check_unset(cmd->cmd[i][j]))
                        {
                                ft_putstr_fd("minishell: unset: `", 2);
                                ft_putchar_fd(cmd->cmd[i][j], 2);
                                ft_putendl_fd("': not a valid identifier", 2);
                                return (1);
                        }
                        j++;
                }
                tmp = *env;
                while (tmp)
                {
                        if (!ft_strcmp(tmp->key, cmd->cmd[i]))
                        {
                                free(tmp->key);
                                free(tmp->value);
                                tmp->key = NULL;
                                tmp->value = NULL;
                                *env = tmp->next;
                                return (0);
                        }
                        tmp = tmp->next;
                }
                i++;
        }
        return (0);
}
