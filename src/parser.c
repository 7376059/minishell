/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:31:46 by dgrady            #+#    #+#             */
/*   Updated: 2019/03/18 03:06:26 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_key(char *name)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (g_env[++i])
	{
		j = -1;
		while (g_env[i][++j])
			if (g_env[i][j] == '=')
				break ;
		MC((temp = ft_strndup(g_env[i], j)));
		if (ft_strcmp(temp, name) == 0)
		{
			free(temp);
			return (ft_strdup(g_env[i] + j + 1));
		}
		free(temp);
	}
	return (NULL);
}

void	ft_write_begining(int i)
{
	char	*str;

	if (i == 0)
		write(1, "minishell: ", 11);
	else
	{
		if ((str = ft_get_env_key("PS2")))
			write(1, str, ft_strlen(str));
		else if (i == 1)
			write(1, "dquote> ", 8);
		else
			write(1, "> ", 2);
	}
}

void	ft_for_norminette_v1(void)
{
	if (ft_strlen(g_str) != 0)
		if (g_str[ft_strlen(g_str) - 1] == 92)
		{
			MC((g_str = ft_strnredup(g_str, ft_strlen(g_str) - 1)));
			ft_input_string(2);
		}
	if (g_str)
		if (g_str[0] == '\0')
		{
			ft_strdel(&g_str);
			ft_input_string(0);
		}
}

void	ft_input_string(int i)
{
	char	b;
	int		dquote;

	dquote = i;
	if (!(g_str))
		MC((g_str = ft_strnew(1)));
	if (g_flag)
		ft_write_begining(i);
	g_flag = 1;
	while (read(0, &b, 1))
	{
		dquote = (b == '\"') ? dquote + 1 : dquote;
		if (b == '\n')
			break ;
		MC((g_str = ft_strcrejoin(g_str, b)));
	}
	if (dquote % 2 != 0)
	{
		MC((g_str = ft_strcrejoin(g_str, '\n')));
		ft_input_string(1);
	}
	ft_for_norminette_v1();
}
