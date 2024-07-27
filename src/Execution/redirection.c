/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:34:53 by kael-ala          #+#    #+#             */
/*   Updated: 2024/07/26 22:04:27 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void create_file(t_cmd *cmd,t_minishell *info)
{
    int i;
    while (cmd)
    {
        i = 0;
        while (cmd->red[i])
        {
            if (!ft_strcmp(cmd->red[i], ">"))
                cmd->red_fd[1] = open(cmd->red[++i], O_CREAT | O_TRUNC | O_WRONLY, 0777);
            else if (!ft_strcmp(cmd->red[i], ">>"))
                cmd->red_fd[1] = open(cmd->red[++i], O_CREAT | O_WRONLY | O_APPEND, 0777);
            else if (!ft_strcmp(cmd->red[i], "<"))
                cmd->red_fd[0] = open(cmd->red[++i], O_RDONLY, 0777);
            else if (!ft_strcmp(cmd->red[i], "<<"))
                cmd->red_fd[0] = info->infile;
            if (cmd->red[i + 1])
                close(cmd->red_fd[1]);
            i++;
        }
        cmd = cmd->next;
    }
}
// int redirection(t_cmd *cmd)
// {
//     if (create_file(cmd) == -1)
//         return (-1);
// }