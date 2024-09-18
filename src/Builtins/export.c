/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/18 03:25:21 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key && !tmp->value)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	add_new_node(char *id, char *value, t_env **env)
{
	t_env	*new;

	new = new_env(id, value);
	append_env(env, new);
	free(id);
	free(value);
}

void	add_value(char *id, char *value, t_env **env, int flag)
{
	t_env	*tmp;
	int		found;

	tmp = *env;
	found = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, id) == 0 && !flag)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			found = 1;
			free(id);
		}
		else if (ft_strcmp(tmp->key, id) == 0 && flag)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strjoin(tmp->value, value);
			found = 1;
			free(id);
			free(value);
		}
		tmp = tmp->next;
	}
	if (!found)
		add_new_node(id, value, env);
}
int	export(t_cmd *cmd, t_env **env)
{
	int		i;
	int		flag;
	char	*id;
	char	*value;

	1 && (i = 1, flag = 0);
	if (!cmd->cmd[1] || (ft_strlen(cmd->cmd[1]) == 0 && !cmd->cmd[2]))
		print_export(*env);
	else
	{
		while (cmd->cmd[i])
		{
			if (ft_strlen(cmd->cmd[i]) == 0)
				;
			else if (isvalid(cmd->cmd[i], &flag))
			{
				split_var(cmd->cmd[i], &id, &value, flag);
				add_value(id, value, env, flag);
			}
			else
				printf("export: %s: not a valid identifier\n", cmd->cmd[i]);
			i++;
		}
	}
	return (0);
}
