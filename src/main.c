 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:21:47 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/20 17:47:18 by kael-ala         ###   ########.fr       */
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

void	hardcode_env(t_env **env)
{
	append_env(env, new_env(ft_strdup("PATH"), \
		ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin")));
	append_env(env, new_env(ft_strdup("PWD"), \
		ft_strdup("/Users/omghazi/Desktop/minishell"))); // ?????
	append_env(env, new_env(ft_strdup("SHLVL"), ft_strdup("1")));
	append_env(env, new_env(ft_strdup("_"), ft_strdup("/usr/bin/env")));
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

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_env		*envr;
	t_tokenizer	*lexer;
	t_cmd		*cmds;
	int			status;	

	if (argc != 1)
		return (printf("minishell: %s: No such file or directory\n", argv[1]), 127);
	if (isatty(0) == 0)
		return (ft_putstr_fd("minishell only reads from tty\n", 2), 1);
	minishell = o_malloc(sizeof(t_minishell), END);
	minishell->envirement = env;
	init_minishell(&minishell, &envr, &lexer, &cmds);
	while (1)
	{
		set_sigs();
		g_exit_stts = 0;
		minishell->line = readline("minishell$ : ");
		if (g_exit_stts == 1)
			minishell->ret_value = 1;
		if (!minishell->line)
			break ;
		process_line(minishell, &lexer, &cmds);
	}
	status = minishell->ret_value;
	o_malloc(0, CLEAR_END);
	clear_history();
	return (status);
}
