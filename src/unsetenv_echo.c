/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 03:52:48 by dgrady            #+#    #+#             */
/*   Updated: 2019/05/14 18:57:39 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv_cycle(char *temp)
{
	char	**new;
	int		k;
	int		i;

	i = 0;
	k = -1;
	new = (char**)malloc(sizeof(char*) * ft_maslen(g_env));
	while (g_env[++k])
	{
		if (ft_strcmp(temp, g_env[k]) == 0)
			continue ;
		new[i] = ft_strdup(g_env[k]);
		i++;
	}
	new[i] = 0;
	ft_delete_doublemas(g_env);
	g_env = new;
}

void	ft_unsetenv(char **str)
{
	int		k;
	char	*key;
	char	*temp;

	k = ft_maslen(str);
	if (k == 1)
		write(1, "unsetenv: Too few arguments.\n", 29);
	else
	{
		if (!(key = ft_get_env_key(str[1])))
			return ;
		temp = ft_strjoin(str[1], "=");
		temp = ft_strrejoin(temp, key);
		free(key);
		ft_unsetenv_cycle(temp);
		free(temp);
	}
}

int		ft_echo(char **str)
{
	int i;

	i = 0;
	while (str[++i])
	{
		write(1, str[i], ft_strlen(str[i]));
		write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (1);
}

void	ft_exit(void)
{
	write(1, "bye\n", 4);
	write(1, "exit\n", 5);
	ft_delete_doublemas(g_env);
	ft_clear_lst();
	exit(0);
}
