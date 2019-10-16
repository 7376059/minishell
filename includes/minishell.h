/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:10:36 by dgrady            #+#    #+#             */
/*   Updated: 2019/05/14 20:17:05 by dgrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/stat.h>
# include <pwd.h>
# include <signal.h>
# define MC(x) if (!x) {write(1, "malloc problem\n", 15); exit (0);}

typedef	struct		s_list
{
	char			**comand;
	struct s_list	*next;
}					t_list;

char				**g_env;
char				*g_str;
t_list				*g_lst;

void				ft_setenv(char **str);
void				ft_env(void);
void				ft_exit(void);
void				ft_echo(char **str);
void				ft_unsetenv(char **str);

void				ft_input_string(int i);
char				*ft_get_env_key(char *name);
void				ft_flexer_start();
void				ft_command_executor(void);
void				ft_cd(char **str);
void				ft_delete_doublemas(char **mas);
int					ft_maslen(char **str);
void				ft_copy_env(char **env);
char				*ft_cut_str(char *str, int *i);
t_list				*ft_create_lst(char **temp);
char				*ft_delete_tilda(char *str);
char				*ft_delete_dollar(char *str);
char				*ft_try_path2(char *command);
void				ft_put2str(char *a, char *b);
void				ft_clear_lst(void);
#endif
