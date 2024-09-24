/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/24 11:24:27 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtins(t_cmd *cmds)
{
	t_cmd	*tmp;

	if (!cmds)
		return (0);
	tmp = cmds;
	if (tmp)
	{
		if (ft_strncmp(tmp->cmd[0], "echo", 5) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "cd", 3) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "pwd", 4) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "export", 7) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "unset", 6) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "env", 4) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "exit", 5) == 0)
			return (1);
	}
	return (0);
}

void	ft_export_error(char *cmd)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

int	ft_split_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
