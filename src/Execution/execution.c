/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:28:16 by kael-ala          #+#    #+#             */
/*   Updated: 2024/07/26 18:13:38 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int exec(t_minishell *info, t_cmd *cmd)
{
    create_file(cmd, info);
    if (pipes(info, cmd) == -1)
        perror("Error has occured");
    return 0;
}
