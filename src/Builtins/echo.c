/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/17 22:44:55 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     echo(t_tokenizer *token)
{
       if (token && ft_strcmp(token->token, "-n") == 0)
       {
              if (token->next)
                     token = token->next;
              while (token)
              {
                     printf("%s", token->token);
                     token = token->next;
                     if (token)
                            printf(" ");
              }
       }
       else
       {
              while (token)
              {
                     printf("%s", token->token);
                     token = token->next;
                     if (token)
                            printf(" ");
              }
              printf("\n");
       }
       return (0);
}
