/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:51:14 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/04 00:51:17 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	process(t_minishell *mini, t_cmd *cmds, int input, int output)
{
	if (red_process(mini, cmds, input, output) == -1)
		exit(1);
	if (input != STDIN_FILENO && dup2(input, 0) < 0)
		exit (1);
	if (output != STDOUT_FILENO && dup2(output, 1) < 0)
		exit (1);
	if (is_builtins(cmds))
		(execute_builtin(mini, cmds), exit(mini->ret_value));
	return (my_execve(mini, cmds));
}
