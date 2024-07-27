/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:44:36 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/26 14:05:34 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void append_to_exec(t_cmd **cmds, t_cmd *cmd)
{
    t_cmd *head;

    if (!cmds || !cmd)
        return;
    if (!*cmds)
    {
        *cmds = cmd;
        return;
    }
    head = *cmds;
    while (head->next)
        head = head->next;
    head->next = cmd;
	cmd->prev = head; // i added this line need to check
}

t_cmd	*new_cmd(int cmd, int red)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		NULL;
	new->cmd = malloc(sizeof(char *) * (cmd + 1));
	new->red = malloc(sizeof(char *) * (red + 1));
	new->cmd[cmd] = NULL;
	new->red[red] = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->fdp[0] = 0;
	new->fdp[1] = 0;
	new->red_fd[0] = 0;
	new->red_fd[1] = 1;
	return (new);
}

void	del_one_cmd(t_cmd *cmds, void (*del)(void *))
{
	if (!cmds)
		return ;
	del(cmds->red);
	del(cmds->cmd);
	free(cmds);
}

void	clear_cmd(t_cmd **cmd, void (*del)(void *))
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		del_one_cmd(*cmd, del);
		*cmd = tmp;
	}
}
