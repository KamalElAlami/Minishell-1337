/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:31:45 by kael-ala          #+#    #+#             */
/*   Updated: 2024/07/26 22:24:30 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


 char **get_path(t_env *env)
{
    while (env)
    {
        if (!ft_strcmp(env->key, "PATH"))
            return (ft_split(env->value, ':'));
        env = env->next;
    }
    return (NULL);
}

 char *check_cmd(char *cmd, char **path)
{
    int i;
    char *buffer;

    i = 0;
    if (!cmd || !path || !*path)
        return (NULL);
    while (path[i])
    {
        buffer = ft_strjoin(path[i], cmd);
        if (access(buffer, X_OK) == 0)
            return (buffer);
        i++;
    }
    return (NULL);
}

int pipes(t_minishell *info, t_cmd *cmd)
{
    int pid;
    int len;
    char **path;
    char *command;
    char **env;

    len = node_len(cmd);
    path = get_path(info->env);

    env = get_env(info->env);
    while (cmd)
    {
        if (cmd->next)
        {
            if (pipe(cmd->fdp) == -1)
                return (-1);
        }
        pid = fork();
        if (pid == -1)
            return (-1);
        if (pid == 0)
        {
            if (cmd->next)
            {
                close(cmd->fdp[0]);
                dup2(cmd->fdp[1], STDOUT_FILENO);
            }
            if (cmd->prev)
            {
                close(cmd->prev->fdp[1]);
                dup2(cmd->prev->fdp[0], STDIN_FILENO);
            }

            if (cmd->red_fd[1] != STDOUT_FILENO)
            {
                dup2(cmd->red_fd[1], STDOUT_FILENO);
                close(cmd->red_fd[1]);
            }
            if (cmd->red_fd[0] != STDIN_FILENO)
            {
                dup2(cmd->red_fd[0], STDIN_FILENO);
                close(cmd->red_fd[0]);
            }
            command = check_cmd(ft_strjoin("/", cmd->cmd[0]), path);
            if (command)
            {
                cmd->cmd[0] = command;
                if (execve(cmd->cmd[0], cmd->cmd, env) == -1)
                    return (-1);
            }
            else
                perror("command not found");
        }
        else
        {
            if (cmd->prev)
            {
                close(cmd->prev->fdp[0]);
                close(cmd->prev->fdp[1]);
            }
            if (cmd->red_fd[1] != STDOUT_FILENO)
                close(cmd->red_fd[1]);
            if (cmd->red_fd[0] != STDIN_FILENO)
                close(cmd->red_fd[0]);
        }
        cmd = cmd->next;
    }
    while (len--)
        wait(NULL);
    return (0);
}