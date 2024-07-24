/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/09 22:38:05 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     check_unset(char c)
{
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

int     check_token(char *token)
{
        int i;

        i = 0;
        if (!token)
                return (0);
        while (token[i])
        {
                if (!check_unset(token[i]) || !ft_isalnum(token[i]))
                        return (0);
                i++;
        }
        return (1);
}

int     unset(t_tokenizer *token, t_env **env)
{
        t_env *tmp;
        t_env *prev;
        int flag;

        if (!token || !env || !*env)
                return (0);
        tmp = *env;
        prev = *env;
        while (token)
        {
                tmp = *env;
                prev = *env;
                flag = 0;
                if (!check_unset(token->token[0]) || !check_token(token->token))
                {
                        printf("minishell: unset: `%s': not a valid identifier\n", token->token);
                        if (token->next)                
                                token = token->next;
                }
                if (!ft_strcmp(token->token, tmp->key))
                {
                        *env = tmp->next;
                        if (token->next)
                                token = token->next;
                        continue;
                }
                while (tmp)
                {
                        if (!ft_strcmp(token->token, tmp->key))
                        {
                                if (tmp == *env)
                                        (*env) = (*env)->next;
                                else
                                        prev->next = tmp->next;
                                flag = 1;
                                break ;
                        }
                        prev = tmp;
                        tmp = tmp->next;
                }
                if (!flag)
                        return (0);
                token = token->next;
        }
        return (0);
}
