/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 01:07:14 by dgrady            #+#    #+#             */
/*   Updated: 2019/04/29 15:41:09 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(void)
{
	int i;

	i = -1;
	while (g_env[++i])
	{
		write(1, g_env[i], ft_strlen(g_env[i]));
		write(1, "\n", 1);
	}
	return (1);
}

int		ft_setenv_errors(char **str)
{
	int len;

	if (ft_maslen(str) == 1)
	{
		ft_env();
		return (0);
	}
	if (ft_maslen(str) > 3)
	{
		write(1, "setenv: Too many arguments.\n", 28);
		return (0);
	}
	if (ft_isalpha(str[1][0]) == 0)
	{
		write(1, "setenv: Variable name must begin with a letter.\n", 48);
		return (0);
	}
	len = -1;
	while (str[1][++len])
		if (ft_isalnum(str[1][len]) == 0)
		{
			write(1, "setenv: name must contain alphanumeric characters\n", 50);
			return (0);
		}
	return (1);
}

void	ft_setenv_push_back(char *str)
{
	int		len;
	char	**new;

	len = -1;
	while (g_env[++len])
		;
	MC((new = (char**)malloc(sizeof(char*) * (len + 2))));
	len = -1;
	while (g_env[++len])
		MC((new[len] = ft_strdup(g_env[len])));
	new[len] = str;
	new[len + 1] = 0;
	ft_delete_doublemas(g_env);
	g_env = new;
}

void	ft_setenv(char **str)
{
	char	*temp;
	int		i;

	i = -1;
	if (ft_setenv_errors(str) != 1)
		return ;
	if (str[2] != 0)
	{
		MC((temp = ft_strjoin(str[1], "=")));
		MC((temp = ft_strrejoin(temp, str[2])));
	}
	else
		MC((temp = ft_strjoin(str[1], "=")));
	if (ft_get_env_key(str[1]) == NULL)
		return (ft_setenv_push_back(temp));
	while (g_env[++i])
		if (ft_strncmp(g_env[i], str[1], ft_strlen(str[1])) == 0)
		{
			free(g_env[i]);
			g_env[i] = temp;
		}
}
