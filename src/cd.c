/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 03:08:27 by dgrady            #+#    #+#             */
/*   Updated: 2019/10/16 19:50:12 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_maslen(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	ft_change_pwds(void)
{
	char	*pwd;
	int		i;
	char	*temp;
	char	*oldpwd;

	MC((pwd = ft_strnew(255)));
	pwd = getcwd(pwd, 255);
	i = -1;
	while (g_env[++i])
		if (ft_strncmp(g_env[i], "PWD", 3) == 0)
		{
			MC((oldpwd = ft_strdup(g_env[i] + 4)));
			free(g_env[i]);
			MC((g_env[i] = ft_strjoin("PWD=", pwd)));
		}
	i = -1;
	while (g_env[++i])
		if (ft_strncmp(g_env[i], "OLDPWD", 6) == 0)
		{
			free(g_env[i]);
			MC((temp = ft_strjoin("OLDPWD=", oldpwd)));
			g_env[i] = temp;
		}
	free(pwd);
	ft_strdel(&oldpwd);
}

void	ft_try_to_cd(char *path, char *name)
{
	if (chdir(path) == 0)
	{
		ft_change_pwds();
		return ;
	}
	if (access(path, F_OK) != 0)
		write(1, "cd: no such file or directory: ", 32);
	else if (access(path, R_OK) != 0)
		write(1, "cd: permission denied: ", 23);
	else
		write(1, "cd: not a directory: ", 22);
	ft_putendl(name);
}

void	ft_cd(char **str)
{
	int		i;
	char	*temp;

	i = ft_maslen(str);
	if (i == 2)
	{
		if (ft_strcmp(str[1], "-") == 0)
		{
			temp = ft_get_env_key("OLDPWD");
			ft_try_to_cd(temp, "OLDHOME");
			return ;
		}
	}
	ft_cd1(str);
}

void	ft_cd1(char **str)
{
	int		i;
	char	*path;
	char	*pwd;

	i = ft_maslen(str);
	if (i > 2)
		write(1, "cd: too many arguments\n", 23);
	else if (i == 1)
	{
		path = ft_get_env_key("HOME");
		ft_try_to_cd(path, "home");
		ft_strdel(&path);
	}
	else if (str[1][0] == '/')
		ft_try_to_cd(str[1], str[1]);
	else
	{
		MC((pwd = ft_strnew(255)));
		pwd = getcwd(pwd, 255);
		MC((path = ft_strcrejoin(pwd, '/')));
		MC((path = ft_strrejoin(path, str[1])));
		ft_try_to_cd(path, str[1]);
		ft_strdel(&path);
	}
}
