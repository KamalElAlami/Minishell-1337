/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:58 by kael-ala          #+#    #+#             */
/*   Updated: 2024/08/18 17:50:11 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int getexstatus(int stts)
{
        int ret;

        if (WIFSIGNALED(stts))
        {
                ret = WTERMSIG(stts);
                if (ret == SIGINT)
                        return (130);
                else if (ret ==  SIGQUIT)
                {
                        printf("QUIT: 3\n");
                        return (131);
                }
                else
                        return (128 + ret);
        }
        return (WEXITSTATUS(stts));
}

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
        (void)sig;
        disable_echo();
        g_exit_stts = 1;
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
}
void reset_sigs(void)
{
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
}
void set_sigs(void)
{
        struct sigaction siig;

        siig.sa_handler = handle_sigint;
        sigemptyset(&siig.sa_mask);
        siig.sa_flags = SA_RESTART;

        sigaction(SIGINT, &siig, NULL);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
}