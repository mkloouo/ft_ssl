/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 16:09:58 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 06:41:26 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

int					main(int ac, char **av)
{
	t_ssl			ssl;
	size_t			i;

	init_ssl(&ssl, av[0]);
	if (ac == 1)
		return (ssl_print_usage(ssl.program));
	if (!ssl_get_hash_fn_name(&ssl.fn_name, av[1]))
		return (ssl_print_invalid_fn(ssl.program, av[1]));
	i = ssl_parse_flags(&ssl.flags, av);
	if (ac == (2 + ssl.flags.p_flag + ssl.flags.q_flag + ssl.flags.r_flag)
		|| ssl.flags.p_flag)
		ssl_run_stdin(&ssl.fn_name, &ssl.flags);
	ssl_run_args(&ssl, i, av);
	return (0);
}
