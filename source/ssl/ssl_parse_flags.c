/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parse_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:56:21 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/16 19:14:26 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/string.h>

t_bool		parse_md_commands(t_ssl *ssl, char const *command)
{
	size_t	i;

	i = 0;
	while (g_md_commands[i].f)
	{
		if (ft_strequ(g_md_commands[i].lc_name, command))
		{
			ssl->command.command = g_md_commands + i;
			ssl->command.run = ft_ssl_run_md;
			return (TRUE);
		}
		++i;
	}
	ssl->parse_error = 1;
	ssl->parse_error_msg = ft_strnew(SSL_ERROR_MSG_LEN, 0);
	ft_sprintf(ssl->parse_error_msg, "'%s' is an invalid command.",
			command);
	return (FALSE);
}

t_bool		parse_md_command_flags(t_ssl *ssl, int ac, char **av)
{
	if (ac == 2)
	{
		ssl->read_stdin = 1;
		return (TRUE);
	}
	(void)ssl;
	(void)ac;
	(void)av;
	return (FALSE);
}

void		ft_ssl_parse_flags(t_ssl *ssl, int ac, char **av)
{
	t_bool	parsed_command;

	ssl_init(ssl, av[0]);
	if (ac == 1)
	{
		ssl->parse_error = 1;
		return ;
	}
	if ((parsed_command = parse_md_commands(ssl, av[1])))
		parsed_command = parse_md_command_flags(ssl, ac, av);
	(void)parsed_command;
	ssl->args = 0;
}
