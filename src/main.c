/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:21:47 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/23 16:15:03 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all(void)
{
	int	i;

	i = 3;
	while (++i < OPEN_MAX)
		if (close(i) == -1)
			return ;
}

static void	init_minishell(t_minishell **minishell, t_env **envr, \
	t_tokenizer **lexer, t_cmd **cmds)
{
	*envr = NULL;
	*lexer = NULL;
	*cmds = NULL;
	*envr = NULL;
	store_env((*minishell)->envirement, envr);
	if (!*envr)
		hardcode_env(envr);
	(*minishell)->ret_value = 0;
	(*minishell)->env = *envr;
	rl_catch_signals = 0;
}

static void	process_line(t_minishell *minishell, \
	t_tokenizer **lexer, t_cmd **cmds)
{
	if (!lexer_first(lexer, minishell->line))
		return ;
	minishell->start = *lexer;
	parse_input(minishell, cmds);
	if (minishell->line)
	{
		o_malloc(0, CLEAR_FREQ);
		*lexer = NULL;
		*cmds = NULL;
		add_history(minishell->line);
		free(minishell->line);
		close_all();
	}
}

void	minishell_process(t_minishell *minishell, \
	t_tokenizer **lexer, t_cmd **cmds)
{
	while (1)
	{
		set_sigs();
		g_exit_stts = 0;
		minishell->line = readline("minishell$ : ");
		if (g_exit_stts == 1)
			minishell->ret_value = 1;
		if (!minishell->line)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		process_line(minishell, lexer, cmds);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_env		*envr;
	t_tokenizer	*lexer;
	t_cmd		*cmds;
	int			status;	

	if (argc != 1)
		return (printf("minishell: %s: No such file or directory\n", \
			argv[1]), 127);
	if (isatty(0) == 0)
		return (ft_putstr_fd("minishell only reads from tty\n", 2), 1);
	minishell = o_malloc(sizeof(t_minishell), END);
	minishell->envirement = env;
	init_minishell(&minishell, &envr, &lexer, &cmds);
	minishell_process(minishell, &lexer, &cmds);
	status = minishell->ret_value;
	o_malloc(0, CLEAR_END);
	clear_history();
	return (status);
}
