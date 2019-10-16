/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 00:17:00 by dgrady            #+#    #+#             */
/*   Updated: 2019/03/18 03:07:15 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_delete_slashes(char *str)
{
	int		i;
	int		dquote;
	char	*temp;

	i = -1;
	dquote = 0;
	while (str[++i])
	{
		dquote = ((str[i] == '\"') ? dquote + 1 : dquote);
		if (dquote % 2 == 0 && str[i] == 92)
			if (str[i + 1] != '~' && str[i + 1] != '$')
			{
				if (i == 0)
				{
					MC((temp = ft_strdup(str + 1)));
					free(str);
					str = temp;
				}
				else
					str = ft_cut_str(str, &i);
			}
	}
	return (str);
}

char	*ft_delete_all_quots(char *str)
{
	int		i;
	char	*temp;

	i = -1;
	while (str[++i])
		if (str[i] == '\"')
		{
			if (i == 0 && str[1])
			{
				MC((temp = strdup(str + 1)));
				free(str);
				str = temp;
			}
			else
			{
				MC((temp = ft_strdup(str + i)));
				MC((str = ft_strnredup(str, i)));
				MC((str = ft_strrejoin(str, temp)));
				free(temp);
			}
		}
	if (ft_strlen(str) > 0)
		if (str[i - 1] == '\"')
			MC((str = ft_strnredup(str, i - 1)));
	return (str);
}

void	ft_lexer_cycle(void)
{
	t_list	*temp;
	int		i;

	temp = g_lst;
	while (temp)
	{
		i = -1;
		if (!(temp->comand))
			return ;
		while ((temp->comand)[++i])
		{
			(temp->comand)[i] = ft_delete_slashes((temp->comand)[i]);
			(temp->comand)[i] = ft_delete_dollar((temp->comand)[i]);
			(temp->comand)[i] = ft_delete_tilda((temp->comand)[i]);
			(temp->comand)[i] = ft_delete_all_quots((temp->comand)[i]);
		}
		temp = temp->next;
	}
}

void	ft_flexer_start(void)
{
	char	**temp;
	t_list	*start;
	int		i;

	i = -1;
	if (!(g_lst))
		g_lst = ft_create_lst(NULL);
	start = g_lst;
	temp = ft_strsplit(g_str, ';');
	while (temp[++i])
	{
		if (i == 0)
		{
			start->comand = ft_strsplit_whitespaces(temp[i]);
			if (!(start->comand))
				return ;
		}
		else
		{
			start->next = ft_create_lst(ft_strsplit(temp[i], ' '));
			start = start->next;
		}
	}
	ft_delete_doublemas(temp);
	ft_lexer_cycle();
}
