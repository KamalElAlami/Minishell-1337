/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:28:16 by kael-ala          #+#    #+#             */
/*   Updated: 2024/07/25 23:23:45 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char **get_path(t_env *env)
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
    char **path;
    char *command;
    int len;

    len = node_len(cmd);
    path = get_path(info->env);
    while (cmd)
    {
        printf("cmd => %s\n", cmd->cmd[0]);
        t_cmd *tmp = cmd;
        while (tmp)
        {
            int i = 0;
            while (tmp->red[i])
                printf("%s ", tmp->red[i++]);
            tmp = tmp->next;
        }
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
                dup2(cmd->fdp[1], 1);
            }
            if (cmd->prev)
            {
                close(cmd->prev->fdp[1]);
                dup2(cmd->prev->fdp[0], 0);
            }
           
            command = check_cmd(ft_strjoin("/", cmd->cmd[0]), path);
            if (command)
            {
                cmd->cmd[0] = command;
                if (execve(cmd->cmd[0], cmd->cmd, NULL) == -1)
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
        }
        cmd = cmd->next;
    }
    while (len--)
    {
        wait(NULL);
    }
    return (0);
}

int exec(t_minishell *info, t_cmd *cmd)
{
    if (pipes(info, cmd) == -1)
        perror("Error has occured");
    return 0;
}
