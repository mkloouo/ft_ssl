/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 06:31:10 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 07:05:55 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/string.h>

int			ssl_get_hash_fn_name(t_hash_fn_name *fn_name,
			char const *arg)
{
	size_t	i;

	i = 0;
	while (g_hash_fn_name_arr[i].fn)
	{
		if (ft_strequ(g_hash_fn_name_arr[i].lc_name, arg))
		{
			*fn_name = g_hash_fn_name_arr[i];
			return (1);
		}
		++i;
	}
	return (0);
}

size_t		ssl_parse_flags(t_ssl_flags *flags, char **av)
{
	size_t	i;

	i = 2;
	while (av[i])
	{
		if (ft_strequ(av[i], "-p"))
			flags->p_flag += 1;
		else if (ft_strequ(av[i], "-q"))
			flags->q_flag += 1;
		else if (ft_strequ(av[i], "-r"))
			flags->r_flag += 1;
		else
			break ;
		++i;
	}
	return (i);
}
