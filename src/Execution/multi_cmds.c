/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:11 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/06 22:45:26 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	first_commande(t_minishell *mini, t_cmd *cmd)
{
	pid_t	pid;

	mini->pipe[0] = (int *)malloc(sizeof(int) * 2);
	if (pipe(mini->pipe[0]) == -1)
		return (perror("pipe"), ERROR);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ERROR);
	if (!pid)
	{
		close(mini->pipe[0][0]);
		process(mini, cmd, STDIN_FILENO, mini->pipe[0][1]);
	}
	else
		if (close(mini->pipe[0][1]) == -1)
			return (perror("close"), ERROR);
	return (0);
}

int	other_cmds(t_minishell *mini, t_cmd *cmd, int i)
{
	pid_t	pid;

	mini->pipe[i] = (int *)malloc(sizeof(int) * 2);	
	if (pipe(mini->pipe[i]) == -1)
		return (perror("pipe"), ERROR);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ERROR);
	if (!pid)
	{
		close(mini->pipe[i][0]);
		process(mini, cmd, mini->pipe[i - 1][0], mini->pipe[i][1]);
	}
	else
	{	
		if (close(mini->pipe[i][1]) == -1)
			return (perror("close"), ERROR);
		if (close(mini->pipe[i - 1][0]) == -1)
			return (perror("close"), ERROR);
	}
	return (0);
}

int	last_cmd(t_minishell *mini, t_cmd *cmd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)	
		return (perror("fork"), ERROR);
	if (!pid)
		process(mini, cmd, mini->pipe[i - 2][0], STDOUT_FILENO);
	if (close(mini->pipe[i - 2][0]))
		return (perror("close"), ERROR);
	waitpid(pid, &mini->ret_value, 0);
	return (0);
}

int     multi_process(t_minishell *mini, t_cmd *cmds)
{
	int  i;
	t_cmd *tmp;
	
	tmp = cmds;
	first_commande(mini, tmp);
	tmp = tmp->next;
	i = 1;
	while (tmp->next)
	{
		other_cmds(mini, tmp, i);
		tmp = tmp->next;
		i++;
	}
	i++;
	last_cmd(mini, tmp, i);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(mini->ret_value))
		mini->ret_value = WEXITSTATUS(mini->ret_value);
	else if (WIFSIGNALED(mini->ret_value))
		mini->ret_value = WTERMSIG(mini->ret_value);
	return (mini->ret_value);
}
