/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:37:27 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/12 18:14:38 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void quit_hundler(int sig)
{
        (void)sig;
        printf("Quit: 3\n");
}

void disable_echo(void)
{
        struct termios ign;
        tcgetattr(0, &ign);
        ign.c_lflag &= ~ECHOCTL;
        tcsetattr(0, TCSANOW, &ign);
}

void handle_sigint(int sig)
{
        if (sig == SIGINT)
        {
                disable_echo();
                write(1, "\n", 1);
                rl_on_new_line();
                rl_replace_line("", 0);
                rl_redisplay();
        }
}
