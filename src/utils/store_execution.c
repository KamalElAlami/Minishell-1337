/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:44:36 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/21 02:43:04 by kael-ala         ###   ########.fr       */
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

	new = o_malloc(sizeof(t_cmd), FREQ);
	new->cmd = o_malloc(sizeof(char *) * (cmd + 1), FREQ);
	new->red = o_malloc(sizeof(char *) * (red + 1), FREQ);
	new->cmd[cmd] = NULL;
	new->red[red] = NULL;
	new->stat = o_malloc(sizeof(t_stat), FREQ);
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
