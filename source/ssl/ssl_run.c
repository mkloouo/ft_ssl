/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 06:24:35 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/19 03:31:59 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/memory.h>
#include <ft/string.h>

#include <string.h>
#include <errno.h>

void			ssl_run_stdin(t_hash_fn_name *fn_name, t_ssl_flags *flags)
{
	char		*stdin_contents;
	char		*digest;
	size_t		len;

	stdin_contents = ft_readfd(IO_STDIN, &len);
	if (flags && flags->p_flag)
		ft_printf("%s", stdin_contents);
	digest = fn_name->fn(stdin_contents, len);
	ft_printf("%s\n", digest);
	free(stdin_contents);
	free(digest);
}

void			ssl_run_string(t_hash_fn_name *fn_name, t_ssl_flags *flags,
				char const *string)
{
	char		*digest;

	digest = fn_name->fn(string, ft_strlen(string));
	if (!flags->q_flag)
	{
		if (flags->r_flag)
			ft_printf("%s \"%s\"\n", digest, string);
		else
			ft_printf("%s (\"%s\") = %s\n", fn_name->uc_name, string, digest);
	}
	else
		ft_printf("%s\n", digest);
	free(digest);
}

static char		*ssl_handle_context_from_file(t_ssl *ssl,
				char const *file, int *fd, size_t *len)
{
	char		*context;

	*fd = ft_open_file(file, FILE_READ);
	if (*fd == -1)
	{
		ssl_print_file_error(ssl, file, strerror(errno));
		return (0);
	}
	context = ft_readfd(*fd, len);
	if (context == 0)
	{
		ssl_print_file_error(ssl, file, strerror(errno));
		ft_close_file(*fd);
	}
	return (context);
}

void			ssl_run_file(t_ssl *ssl, char const *file)
{
	char		*context;
	char		*digest;
	int			fd;
	size_t		len;

	context = ssl_handle_context_from_file(ssl, file, &fd, &len);
	if (!context)
		return ;
	digest = ssl->fn_name.fn(context, len);
	if (!ssl->flags.q_flag)
	{
		if (ssl->flags.r_flag)
			ft_printf("%s %s\n", digest, file);
		else
			ft_printf("%s (%s) = %s\n", ssl->fn_name.uc_name, file, digest);
	}
	else
		ft_printf("%s\n", digest);
	free(context);
	free(digest);
	ft_close_file(fd);
}

void			ssl_run_args(t_ssl *ssl, size_t i, char **av)
{
	while (av[i] && ft_strequ(av[i], "-s"))
	{
		if (!av[i + 1])
			ssl_print_invalid_s_param(ssl->program);
		else
			ssl_run_string(&ssl->fn_name, &ssl->flags, av[++i]);
		++i;
	}
	while (av[i])
	{
		ssl_run_file(ssl, av[i]);
		++i;
	}
}
