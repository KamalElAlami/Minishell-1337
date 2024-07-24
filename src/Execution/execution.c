/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:28:16 by kael-ala          #+#    #+#             */
/*   Updated: 2024/07/24 23:59:50 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int size_list(t_cmd *cmd)
{
    int count;

    count = 0
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count - 1);
}

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
    int fdp[2];
    char **path;
    char *command;
    int len;

    len = size_list(cmd);
    path = get_path(info->env);
    while (cmd)
    {
        pid = fork();
        if (pid == -1)
            return (-1);
        if (pid == 0)
        {
            if (cmd->next)
            {
                if (pipe(fdp) == -1)
                    return (-1);
            }
            if (cmd->next)
            {
                dup2(fdp[1], 1);
                close(fdp[0]);
            }
            dup2(fdp[0], 0);
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
        cmd = cmd->next;
    }
    whi
    // return (0);
}
int exec(t_minishell *info, t_cmd *cmd)
{
    if (pipes(info, cmd) == -1)
        perror("Error has occured");
    // while (cmd)
    // {
    //     int i = 0;
    //     while (cmd->cmd[i])
    //         printf("%s\n", cmd->cmd[i++]);
    //     cmd = cmd->next;
    // }
    // t_env *siko;

    // siko = info->env;

    // while (siko)
    // {
    //     printf("key => %s\nvalue => %s\n", siko->key, siko->value);
    //     siko = siko->next;
    // }
    return 0;
}
