/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:37:27 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/09 17:48:41 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_sigint(int sig)
{
        (void)sig;
        // rl_catch_signals = 0;
        // write(1, "\n", 1);
        // rl_on_new_line();
        // rl_replace_line("", 0);
        // rl_redisplay();
}
