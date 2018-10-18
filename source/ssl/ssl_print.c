/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 06:29:43 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 06:30:24 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>

int			ssl_print_usage(char const *program)
{
	ft_printf("Usage: %s command [command opts] [command args]\n", program);
	return (1);
}

void		ssl_print_md_cmds(void)
{
	size_t	i;

	ft_printf("Message Digest commands:\n");
	i = 0;
	while (g_hash_fn_name_arr[i].fn)
	{
		ft_printf("%s\n", g_hash_fn_name_arr[i].lc_name);
		++i;
	}
	ft_printf("\n");
}

void		ssl_print_c_cmds(void)
{
	ft_printf("Cipher commands:\n");
}
