/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_print_usage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:55:21 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/16 18:55:42 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/memory.h>

void		ft_ssl_print_md_commands(void)
{
	size_t	i;

	ft_printf("Message Digest commands:\n");
	i = 0;
	while (g_md_commands[i].f)
	{
		ft_printf("%s\n", g_md_commands[i].lc_name);
		++i;
	}
	ft_printf("\n");
}

void		ft_ssl_print_c_commands(void)
{
	ft_printf("Cipher commands:\n");
}

void		ft_ssl_print_usage(t_ssl *ssl)
{
	if (ssl->parse_error_msg)
	{
		ft_dprintf(IO_STDERR, "%s: %s\n", ssl->program, ssl->parse_error_msg);
		free(ssl->parse_error_msg);
	}
	ft_printf("Usage: %s command [command options] [command args]\n",
			ssl->program);
	ft_printf("Standard commands:\n\n");
	ft_ssl_print_md_commands();
	ft_ssl_print_c_commands();
}
