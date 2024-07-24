/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:22:53 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/21 20:47:18 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <libft.h>
#include <types.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/* FUNCTIONS */
int     multi_process(t_minishell *mini, t_cmd *cmds);
char	*env_join(char const *s1, char const *s2);
int     single_process(t_minishell *mini, t_cmd *cmds);
int     single_process(t_minishell *mini, t_cmd *cmds);
char	**env_to_array(t_env *env_list);
int	node_len(t_cmd *cmds);
int     my_execve(t_minishell *mini, t_cmd *cmds);
char    *find_cmd(t_minishell *mini, char *cmd);
int     execution(t_minishell *mini, t_cmd *cmds);
void print_linked_list(t_cmd **cmd);
int     check_token(char *token);
void	del_one_env(t_env *lst, void (*del)(void *));
void handle_sigint(int sig);
void handle_sigquit(int sig);
t_env	*new_env(char *key, char *value);
void    append_env(t_env **env, t_env *node);
char    *get_values(t_env **env, char *key);
int    set_env(t_env **env, char *key, char *value);
char		*get_value(t_minishell **mini, char *key);
int		env(t_env *env);
int		pwd(t_tokenizer *token);
int		export(t_tokenizer *token, t_env *env);
int		ft_exit(t_tokenizer *token);
int		echo(t_tokenizer *token);
int		cd(t_tokenizer *token, t_env *env);
int		unset(t_tokenizer *token, t_env **env);
void	send_to_execution(t_tokenizer *token, t_cmd **cmd);
void    count_len(t_tokenizer *lst, int *commands_len, int *redirection_len);
void	clear_cmd(t_cmd **cmd, void (*del)(void *));
void	del_one_cmd(t_cmd *cmds, void (*del)(void *));
t_cmd	*new_cmd(int cmd, int red);
void	append_to_exec(t_cmd **cmds, t_cmd *cmd);
int	between_pipe(t_tokenizer *lst);
int     ft_strcmp(char *s1, char *s2);
int 	here_doc(t_tokenizer *delimiter, t_minishell *mini);
char	*expansion(char *token, t_minishell *mini);
int     store_env(char **envr, t_env **env);
t_tokenizer	*check_signle_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat);
t_tokenizer	*check_double_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat);
t_tokenizer	*make_node(char *input, int *j, t_lexer *type, t_stat *stat);
t_tokenizer	*new_token(void *content, t_lexer *type, t_stat *stat);
void		print_token(t_tokenizer *token);
void		print_state(t_stat stat);
void		print_type(t_lexer lexer);
void		del_one_token(t_tokenizer *lst, void (*del)(void *));
void		clear_token(t_tokenizer **lst, void (*del)(void *));
int		lexer_first(t_tokenizer **token, char *input);
void		parse_input(t_minishell *mini, t_cmd **cmds);
void		append_token(t_tokenizer **tokens, t_tokenizer *token);
int			ft_isspace(char c);
int			is_special(int c);
