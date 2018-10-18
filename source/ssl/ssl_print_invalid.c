/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_print_invalid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 06:28:23 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 06:29:15 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>

int		ssl_print_invalid_fn(char const *program, char const *invalid_fn)
{
	ft_printf("%s: Error: '%s' is an invalid command.\n\n", program,
			invalid_fn);
	ft_printf("Standard commands:\n\n");
	ssl_print_md_cmds();
	ssl_print_c_cmds();
	return (2);
}

void	ssl_print_invalid_s_param(char const *program)
{
	ft_printf("%s: Error: option requires an argument -- s\n",
			program);
}

void	ssl_print_file_error(t_ssl *ssl, char const *file, char const *error)
{
	ft_printf("%s: %s: %s: %s\n", ssl->program, ssl->fn_name.lc_name,
			file, error);
}
