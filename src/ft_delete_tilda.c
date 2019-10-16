/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_tilda.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 04:11:05 by dgrady            #+#    #+#             */
/*   Updated: 2019/04/29 16:31:33 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_path_massage1(char *str)
{
	write(1, "minishell: permission denied: ", 30);
	ft_putendl(str);
	g_flag = 0;
}

void	ft_delete_doublemas(char **mas)
{
	int i;

	i = -1;
	if (!(mas))
		return ;
	while (mas[++i])
		free(mas[i]);
	free(mas);
}

char	*ft_delete_tilda2(char *str, int *i, char *key)
{
	char *temp;
	char *temp2;

	temp = ft_strndup(str, *i);
	temp = ft_strrejoin(temp, key);
	temp2 = ft_strdup(str + *i + 1);
	free(str);
	str = ft_strrejoin(temp, temp2);
	free(temp2);
	return (str);
}

char	*ft_delete_tilda(char *str)
{
	int		i;
	char	*key;
	int		dquote;

	i = -1;
	dquote = 0;
	if (ft_strlen(str) == 1 && str[0] == '~')
	{
		if (!(key = ft_get_env_key("HOME")))
			return (str);
		free(str);
		return (key);
	}
	while (str[++i])
	{
		if (!(key = ft_get_env_key("HOME")))
			return (str);
		dquote = (str[i] == '\"') ? dquote + 1 : dquote;
		if (dquote % 2 == 0)
			if (str[i] == '~')
				str = ft_delete_tilda2(str, &i, key);
		free(key);
	}
	return (str);
}
