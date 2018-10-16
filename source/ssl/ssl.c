/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:47:04 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/16 19:01:22 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/string.h>
#include <ft/memory.h>

t_md_command g_md_commands[] = {
	{"md5", "MD5", ft_md5},
	{"sha256", "SHA256", ft_sha256}
};

void	ssl_init(t_ssl *ssl, char const *program)
{
	ssl->args = 0;
	ssl->parse_error_msg = 0;
	ssl->parse_error = 0;
	ssl->program = program;
	ssl->read_stdin = 0;
}
