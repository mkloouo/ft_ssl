/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:18:12 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/12 18:44:23 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/memory.h>

int			main(int ac, char **av)
{
	char	*data;
	char 	*hashed;

	if (ac != 2)
		return (ft_print_ssl_usage());
	if (ft_get_string(IO_STDIN, &data, LINE_BREAK) <= 0)
	{
		ft_dprintf(IO_STDERR, "%s: invalid stdin read\n", av[0]);
		return (2);
	}
	hashed = ft_sha256(data);
	ft_printf("SHA256 (\"%s\") = %s\n", data, hashed);
	free(data);
	free(hashed);
	return (0);
}
