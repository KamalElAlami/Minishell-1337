/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:19:08 by kael-ala          #+#    #+#             */
/*   Updated: 2024/07/26 22:17:09 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int env_count(t_env *env)
{
    int count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

char **get_env(t_env *env)
{
    int i;
    char **buffer;
    i = 0;
    buffer = malloc(sizeof(char *) * (env_count(env) + 1));
    while (env->next)
    {
        env->key = ft_strjoin(env->key, "=");
        buffer[i++] = ft_strjoin(env->key, env->value);
        env = env->next;
    }
    buffer[i] = NULL;
    return (buffer);
}