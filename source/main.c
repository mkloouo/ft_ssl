/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 16:09:58 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 07:26:02 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/memory.h>
#include <ft/string.h>

static void			ssl_live_mode_h(char const *line, t_bool *valid_cmd)
{
	int				i;

	i = 0;
	while (g_hash_fn_name_arr[i].fn)
	{
		if (ft_strequ(line, g_hash_fn_name_arr[i].lc_name))
		{
			ssl_run_stdin(g_hash_fn_name_arr + i, 0);
			*valid_cmd = TRUE;
			break ;
		}
		++i;
	}
}

static int			ssl_live_mode(char const *program)
{
	char			*line;
	int				rd;
	t_bool			valid_cmd;

	ft_printf("42SSL> ");
	valid_cmd = FALSE;
	while ((rd = ft_get_string(IO_STDIN, &line, LINE_BREAK)) > 0)
	{
		ssl_live_mode_h(line, &valid_cmd);
		if (!valid_cmd && *line != 0)
			ssl_print_invalid_fn(program, line);
		free(line);
		ft_printf("42SSL> ");
		valid_cmd = FALSE;
	}
	return (rd);
}

int					main(int ac, char **av)
{
	t_ssl			ssl;
	size_t			i;

	init_ssl(&ssl, av[0]);
	if (ac == 1)
		return (ssl_live_mode(av[0]));
	if (!ssl_get_hash_fn_name(&ssl.fn_name, av[1]))
		return (ssl_print_invalid_fn(ssl.program, av[1]));
	i = ssl_parse_flags(&ssl.flags, av);
	if (ac == (2 + ssl.flags.p_flag + ssl.flags.q_flag + ssl.flags.r_flag)
		|| ssl.flags.p_flag)
		ssl_run_stdin(&ssl.fn_name, &ssl.flags);
	ssl_run_args(&ssl, i, av);
	return (0);
}
