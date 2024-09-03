/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:50:49 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/04 00:50:52 by kael-ala         ###   ########.fr       */
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
		mini->pipe = o_malloc(sizeof(int *) * node_len(cmds) - 1);
		if (!mini->pipe)
			return (1);
		return (multi_process(mini, cmds));
	}
	return (mini->ret_value);
}
