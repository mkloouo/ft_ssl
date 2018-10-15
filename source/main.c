/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 16:09:58 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/15 16:44:07 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/memory.h>

int			main(int ac, char **av)
{
	char	*context;
	char	*digest;

	if (ac > 1)
	{
		return (ft_dprintf(IO_STDERR,
				"%s: command-line args not supported yet.\n", av[0]));
	}
	ft_printf("my version: ");
	ft_get_string(IO_STDIN, &context, LINE_BREAK);
	digest = ft_md5(context);
	ft_printf("MD5 (\"%s\") = %s\n", context, digest);
	free(digest);
	digest = ft_sha256(context, 0);
	ft_printf("SHA256 (\"%s\") = %s\n", context, digest);
	free(digest);
	free(context);
	return (0);
}
