/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 16:09:58 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/14 21:16:55 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/string.h>
#include <ft/memory.h>

t_bool			parse_ch_algo(char *algo, t_ssl_algo *res)
{
	if (ft_strequ_ic(algo, "md5"))
		res->fn = ft_md5;
	else if (ft_strequ_ic(algo, "sha256"))
		res->fn = ft_sha256;
	else
		return (FALSE);
	res->name = ft_toupper_s(algo);
	return (TRUE);
}

int				helper(t_ssl_algo *algo, char **choice, char **av)
{
	ft_printf("enter command (md5, sha256, ...): ");
	if (ft_get_string(IO_STDIN, choice, LINE_BREAK) <= 0)
		return (ft_dprintf(IO_STDERR, "%s: invalid stdin read\n", av[0]));
	if (!parse_ch_algo(*choice, algo))
	{
		ft_dprintf(IO_STDERR, "%s: invalid cmd: \"%s\"\n", av[0], *choice);
		free(*choice);
		return (1);
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_ssl_algo	algo;
	char		*choice;
	char		*data;
	char		*hashed;

	if (ac > 1)
		return (ft_print_ssl_usage());
	if (helper(&algo, &choice, av))
		return (1);
	ft_printf("message: ");
	if (ft_get_string(IO_STDIN, &data, LINE_BREAK) <= 0)
		return (ft_dprintf(IO_STDERR, "%s: invalid stdin read\n", av[0]));
	hashed = algo.fn(data, 0);
	ft_printf("%s (\"%s\") = %s\n", algo.name, data, hashed);
	free(choice);
	free(data);
	free(hashed);
	return (0);
}
