/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_dollar_tilda.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 03:24:34 by dgrady            #+#    #+#             */
/*   Updated: 2019/03/18 07:56:12 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cut_string_dollar(char *str, char *temp, int i, int a)
{
	free(temp);
	MC((temp = ft_strdup(str + i)));
	MC((str = ft_strnredup(str, a)));
	MC((str = ft_strrejoin(str, temp)));
	return (str);
}

char	*ft_cut_string_dollar2(char *str, char *temp, char *key, int a)
{
	MC((str = ft_strnredup(str, a)));
	MC((str = ft_strrejoin(str, key)));
	MC((str = ft_strrejoin(str, temp)));
	return (str);
}

char	*ft_cut_string_dollar3(char *str)
{
	char *temp;

	MC((temp = ft_strdup(str + 1)));
	free(str);
	str = temp;
	return (str);
}

char	*ft_delete_dollar2(char *str, int *i, int dquote)
{
	char	*key;
	char	*temp;
	int		a;

	MC((key = ft_strnew(1)));
	if (dquote % 2 == 0 && str[*i] == '$')
	{
		a = *i;
		while (ft_isalnum(str[++(*i)]) && str[*i])
			MC((key = ft_strcrejoin(key, str[*i])));
		temp = key;
		if (!(key = ft_get_env_key(temp)) || a == *i - 1)
			str = ft_cut_string_dollar(str, temp, *i, a);
		else
		{
			free(temp);
			MC((temp = ft_strdup(str + *i)));
			str = ft_cut_string_dollar2(str, temp, key, a);
			free(temp);
		}
		*i = a;
	}
	free(key);
	return (str);
}

char	*ft_delete_dollar(char *str)
{
	int		i;
	int		dquote;

	i = -1;
	dquote = 0;
	while (str[++i])
	{
		dquote = (str[i] == '\"') ? dquote + 1 : dquote;
		if (dquote % 2 == 0 && str[i] == 92 && str[i + 1] == '$')
		{
			if (i == 0)
				str = ft_cut_string_dollar3(str);
			else
				str = ft_cut_str(str, &i);
			i++;
		}
		str = ft_delete_dollar2(str, &i, dquote);
		if (ft_strlen(str) == 0)
			return (str);
	}
	return (str);
}
