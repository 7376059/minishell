/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:32:07 by dgrady            #+#    #+#             */
/*   Updated: 2019/10/16 19:51:24 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_execute_command(char *path, char **command, int i,
				char **folders)
{
	pid_t my_pid;

	my_pid = fork();
	if (my_pid == 0)
	{
		execve(path, command, g_env);
	}
	else if (my_pid > 0)
		wait(0);
	else
	{
		write(1, "4to-to poshlo po pizde v  ", 24);
		write(1, command[0], ft_strlen(command[0]));
		write(1, "\n", 1);
	}
	if (folders)
		ft_delete_doublemas(folders);
	if (i)
		free(path);
}

void			ft_absolute_path(char **command, char **folders)
{
	if (folders)
		ft_delete_doublemas(folders);
	if (g_flag == 0)
	{
		g_flag = 1;
		return ;
	}
	if (access(command[0], F_OK) != 0)
	{
		write(1, "minishell: command not found: ", 30);
		ft_putendl(command[0]);
	}
	else if (access(command[0], X_OK) != 0)
	{
		write(1, "minishell: permission denied: ", 29);
		ft_putendl(command[0]);
	}
	else
		return (ft_execute_command(command[0], command, 0, NULL));
}

void			ft_try_path(char **command)
{
	char	**folders;
	char	*temp;
	int		i;

	i = -1;
	if (!(temp = ft_get_env_key("PATH")))
		return (ft_absolute_path(command, NULL));
	folders = ft_strsplit(temp, ':');
	free(temp);
	while (folders[++i])
	{
		temp = ft_strjoin(folders[i], "/");
		temp = ft_strrejoin(temp, command[0]);
		if (access(temp, F_OK) != 0)
			;
		else
		{
			if (access(temp, X_OK) != 0)
				ft_path_massage1(command[0]);
			else
				return (ft_execute_command(temp, command, 1, folders));
		}
		free(temp);
	}
	ft_absolute_path(command, folders);
}

void			ft_command_executor(void)
{
	t_list *temp;

	if (!(g_lst))
		return ;
	temp = g_lst;
	while (temp)
	{
		if (ft_buildins(temp->comand))
		{
			temp = temp->next;
			continue;
		}
		ft_try_path(temp->comand);
		temp = temp->next;
	}
}
