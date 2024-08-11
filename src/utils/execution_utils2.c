/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/02 15:59:18 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     is_builtins(t_cmd *cmds)
{
        t_cmd   *tmp;

        if (!cmds)
                return (0);
        tmp = cmds;
        while (tmp)
        {
                if (ft_strncmp(tmp->cmd[0], "echo", 4) == 0)
                        return (1);
                if (ft_strncmp(tmp->cmd[0], "cd", 2) == 0)
                        return (1);
                if (ft_strncmp(tmp->cmd[0], "pwd", 3) == 0)
                        return (1);
                if (ft_strncmp(tmp->cmd[0], "export", 6) == 0)
                        return (1);
                if (ft_strncmp(tmp->cmd[0], "unset", 5) == 0)
                        return (1);
                if (ft_strncmp(tmp->cmd[0], "env", 3) == 0)
                        return (1);
                if (ft_strncmp(tmp->cmd[0], "exit", 4) == 0)
                        return (1);
                tmp = tmp->next;
        }
        return (0);
}
