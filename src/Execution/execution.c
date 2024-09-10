/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:42:00 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/09 22:36:04 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execution(t_minishell *mini, t_cmd *cmds)
{
	if (node_len(cmds) == 1)
	{
		return (single_process(mini, cmds));
	}
	else
	{
		mini->pipe = o_malloc(sizeof(int *) * node_len(cmds) - 1, 0);
		if (!mini->pipe)
			return (1);
		return (multi_process(mini, cmds));
	}
	return (mini->ret_value);
}
