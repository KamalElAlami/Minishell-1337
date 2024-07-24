/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:38 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/06 19:22:37 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    *get_values(t_env **env, char *key)
{
        t_env   *tmp;

        tmp = *env;
        while (tmp)
        {
                if (!ft_strcmp(tmp->key, key))
                        return (tmp->value);
                tmp = tmp->next;
        }
        return (NULL);
}

int    set_env(t_env **env, char *key, char *value)
{
        t_env   *tmp;

        tmp = *env;
        while (tmp)
        {
                if (!ft_strcmp(tmp->key, key))
                {
                        free(tmp->value);
                        tmp->value = ft_strdup(value);
                        return (1);
                }
                tmp = tmp->next;
        }
        return (0);
}

int     cd(t_tokenizer *token, t_env *env)
{
        char    *path;
        char    *oldpwd;
        char    *pwd;
        
        path = NULL;
        oldpwd = getcwd(NULL, 0);
        if (!token)
        {
                path = get_values(&env, "HOME");
                if (chdir(path) == -1)
                {
                printf("cd: %s: No such file or directory\n", path);
                return (1);
                }
        }
        else
        {
                path = token->token;
                if (chdir(path) == -1)
                {
                printf("cd: %s: No such file or directory\n", path);
                return (1);
                }
        }
        pwd = getcwd(NULL, 0);
        if (!set_env(&env, "OLDPWD", oldpwd))
                append_env(&env, new_env("OLDPWD", ft_strdup("")));
        if (!set_env(&env, "PWD", pwd))
                append_env(&env, new_env("PWD", pwd));
        return (0);
}
