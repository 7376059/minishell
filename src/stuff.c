/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 03:19:16 by dgrady            #+#    #+#             */
/*   Updated: 2019/04/28 20:14:17 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		;
	MC((g_env = (char **)malloc(sizeof(char*) * (i + 1))));
	g_env[i] = 0;
	i = -1;
	while (env[++i])
		MC((g_env[i] = ft_strdup(env[i])));
}

t_list	*ft_create_lst(char **temp)
{
	t_list *elem;

	elem = (t_list*)malloc(sizeof(t_list));
	elem->next = 0;
	elem->comand = temp;
	return (elem);
}

char	*ft_cut_str(char *str, int *i)
{
	char *temp;

	MC((temp = ft_strdup(str + *i)));
	MC((str = ft_strnredup(str, *i - 1)));
	MC((str = ft_strrejoin(str, temp)));
	(*i)--;
	free(temp);
	return (str);
}

void	ft_put2str(char *a, char *b)
{
	write(1, a, ft_strlen(a));
	write(1, b, ft_strlen(b));
	write(1, "\n", 1);
}

int		ft_buildins(char **str)
{
	if (ft_strcmp(str[0], "exit") == 0)
		ft_exit();
	else if (ft_strcmp(str[0], "cd") == 0)
	{
		ft_cd(str);
		return (1);
	}
	else if (ft_strcmp(str[0], "setenv") == 0)
	{
		ft_setenv(str);
		return (1);
	}
	else if (ft_strcmp(str[0], "env") == 0)
		return (ft_env());
	else if (ft_strcmp(str[0], "unsetenv") == 0)
	{
		ft_unsetenv(str);
		return (1);
	}
	else if (ft_strcmp(str[0], "echo") == 0)
		return (ft_echo(str));
	return (0);
}
