/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/04 12:45:21 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int    ft_isnumber(char *str)
{
        int i;

        i = 0;
        while (str && str[i])
        {
                if (!ft_isdigit(str[i]))
                        return (0);
                i++;
        }
        return (1);
}

int     ft_exit(t_tokenizer *token)
{
       if (!token)
                 exit(0);
        if (ft_isnumber(token->token))
        {
                if (token->next)
                {
                        printf("exit\n");
                        printf("%sminishell: exit: too many arguments\n%s", RED_COLOR, RESET);
                        return (1);
                }
                else
                {
                        printf("exit\n");
                        exit(ft_atoi(token->token));
                }
        }
        else
        {
                printf("exit\n");
                printf("%sminishell: exit: %s: numeric argument required\n%s",RED_COLOR, token->token, RESET);
                exit(255);
        }
}
