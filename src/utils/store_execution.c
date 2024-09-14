/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:44:36 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/14 00:58:35 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append_to_exec(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*head;

	if (!cmds || !cmd)
		return ;
	if (!*cmds)
	{
		*cmds = cmd;
		return ;
	}
	head = *cmds;
	while (head->next)
		head = head->next;
	head->next = cmd;
}

t_cmd	*new_cmd(int cmd, int red, t_stat *stat, int len)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->cmd = malloc(sizeof(char *) * (cmd + 1));
	new->red = malloc(sizeof(char *) * (red + 1));
	new->cmd[cmd] = NULL;
	new->red[red] = NULL;
	new->stat = o_malloc(sizeof(t_stat), 0);
	new->stat = stat;
	new->cmd_len = len;
	new->next = NULL;
	return (new);
}

void	del_one_cmd(t_cmd *cmds)
{
	if (!cmds)
		return ;
	free_array(cmds->red);
	free_array(cmds->cmd);
	free(cmds);
}

void	clear_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		del_one_cmd(*cmd);
		*cmd = tmp;
	}
}
