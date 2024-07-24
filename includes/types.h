/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:22:49 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/19 20:43:35 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RED_COLOR	 "\x1b[31m"
#define YELLOW_COLOR	 "\x1b[33m"
#define GREEN_COLOR	 "\x1b[32m"
#define RESET		 "\x1b[0m"
#define EXPANSION	 -36
#define ERROR		 1
#define SUCCESS	 0
#define IS_DIRECTORY	 126
#define UNKNOWN_COMMAND 127

typedef struct s_node				t_node;
typedef struct s_minishell			t_minishell;
typedef struct s_tokenizer			t_tokenizer;
typedef struct s_signal				t_signal;
typedef struct s_env				t_env;
typedef struct s_cmd				t_cmd;
typedef struct s_expansion			t_expantion;
typedef enum e_lexer				t_lexer;
typedef enum e_stat					t_stat;

struct s_tokenizer
{
	struct s_tokenizer		*next;
	struct s_tokenizer		*prev;
	t_lexer					*type;
	t_stat					*stat;
	size_t					len;
	char					*token;
};

struct s_cmd
{
	char		**cmd;
	char		**red;
	struct s_cmd	*next;
};

struct s_minishell
{
	t_tokenizer		*start;
	t_lexer			*lexer;
	t_stat			*stat;
	t_env			*env;
	t_env			*secret_env;
	pid_t			pid;
	t_cmd			*cmd;
	char			*line;
	int				in;
	int				infile;
	int				outfile;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				charge;
	int				parent;
	int				last;
	int				ret_value;
	int				exit;
};

struct	s_signal
{
	int			sigint;
	int			sigquit;
	int			exit_status;
	pid_t		pid;
};

struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
};

enum	e_lexer
{
	GREAT,
	LESS,
	GREATGREAT,
	LESSLESS,
	PIPE,
	WORD,
	WHITESPACE,
	D_QUOTE,
	QUOTE,
} ;

enum	e_stat
{
	GENERAL,
	INDQUOTES,
	INQUOTES,
};
