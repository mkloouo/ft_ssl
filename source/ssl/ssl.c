/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 01:57:48 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/17 02:00:00 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

t_hash_fn_name g_hash_fn_name_arr[] = {
	{ft_md5, "md5", "MD5"},
	{ft_sha256, "sha256", "SHA256"},
	{0, 0, 0}
};

void				init_ssl(t_ssl *ssl, char const *program)
{
	ssl->flags = (t_ssl_flags){0, 0, 0};
	ssl->fn_name = (t_hash_fn_name){0, 0, 0};
	ssl->program = program;
}
