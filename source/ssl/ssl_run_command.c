/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_run_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:00:59 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/16 19:50:14 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/memory.h>

void				ft_ssl_run_md(t_ssl_command *command, t_ssl_data data)
{
	char 			*out;
	t_md_command	md_command;

	md_command = *(t_md_command*)(command->command);
	if (data.type != SSL_STRING_DATA_TYPE)
		return ;
	out = md_command.f(data.data);
	ft_printf("%s (\"%s\") = %s\n", md_command.uc_name, data.data, out);
	free(out);
}
