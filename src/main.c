/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:09:55 by dgrady            #+#    #+#             */
/*   Updated: 2019/10/16 19:52:26 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_shlvl(void)
{
	char	*lvl;
	char	*delete;
	int		temp;

	lvl = ft_get_env_key("SHLVL");
	if (!(lvl))
		return ;
	temp = ft_atoi(lvl);
	temp++;
	free(lvl);
	MC((delete = ft_itoa(temp)));
	MC((lvl = ft_strjoin("SHLVL=", delete)));
	temp = -1;
	while (g_env[++temp])
		if (ft_strncmp("SHLVL=", g_env[temp], 6) == 0)
		{
			free(g_env[temp]);
			g_env[temp] = lvl;
			break ;
		}
	free(delete);
}

void	ft_clear_lst(void)
{
	t_list	*start;
	t_list	*temp;

	start = g_lst;
	while (start)
	{
		temp = start;
		ft_delete_doublemas(start->comand);
		start = start->next;
		free(temp);
	}
	g_lst = NULL;
}

void	ft_signal_ctrlc(int i)
{
	signal(2, ft_signal_ctrlc);
	g_flag = 0;
	if (i == 2)
	{
		write(1, "\n", 1);
		write(1, "minishell: ", 11);
	}
}

int		ft_checkfor_spaces(void)
{
	int i;

	i = -1;
	while (g_str[++i])
	{
		if (g_str[i] != 32 && g_str[i] != '\t')
			return (0);
	}
	free(g_str);
	g_str = NULL;
	return (1);
}

int		main(int ac, char **av, char **env)
{
	signal(2, ft_signal_ctrlc);
	ac = 0;
	av = NULL;
	g_flag = 1;
	if (!(env[0]))
	{
		write(1, "geniy\n", 6);
		return (0);
	}
	ft_copy_env(env);
	ft_change_shlvl();
	while (1)
	{
		ft_input_string(0);
		if (ft_checkfor_spaces())
			continue;
		ft_flexer_start();
		ft_strdel(&g_str);
		if (g_lst->comand)
			ft_command_executor();
		ft_clear_lst();
	}
	return (0);
}
