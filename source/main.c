/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 16:09:58 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/17 04:07:15 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/string.h>
#include <ft/memory.h>

#include <string.h>
#include <errno.h>

static int			ssl_print_usage(char const *program)
{
	ft_printf("Usage: %s command [command opts] [command args]\n", program);
	return (1);
}

static void			ssl_print_md_cmds(void)
{
	size_t			i;

	ft_printf("Message Digest commands:\n");
	i = 0;
	while (g_hash_fn_name_arr[i].fn)
	{
		ft_printf("%s\n", g_hash_fn_name_arr[i].lc_name);
		++i;
	}
	ft_printf("\n");
}

static void			ssl_print_c_cmds(void)
{
	ft_printf("Cipher commands:\n");
}

static int			ssl_print_invalid_fn(char const *program, char const *invalid_fn)
{
	ft_printf("%s: Error: '%s' is an invalid command.\n\n", program, invalid_fn);
	ft_printf("Standard commands:\n\n");
	ssl_print_md_cmds();
	ssl_print_c_cmds();
	return (2);
}

static int			ssl_get_hash_fn_name(t_hash_fn_name *fn_name, char const *arg)
{
	size_t			i;

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

static size_t		ssl_parse_flags(t_ssl_flags *flags, char **av)
{
	size_t			i;

	i = 2;
	while (av[i])
	{
		if (ft_strequ(av[i], "-p"))
			flags->is_p = 1;
		else if (ft_strequ(av[i], "-q"))
			flags->is_q = 1;
		else if (ft_strequ(av[i], "-r"))
			flags->is_r = 1;
		else
			break ;
		++i;
	}
	return (i);
}

static void			ssl_run_stdin(t_hash_fn_name *fn_name, t_ssl_flags *flags)
{
	char			*stdin_contents;
	char			*digest;

	stdin_contents = ft_readfd(IO_STDIN);
	if (flags->is_p)
		ft_printf("%s", stdin_contents);
	digest = fn_name->fn(stdin_contents);
	ft_printf("%s\n", digest);
	free(stdin_contents);
	free(digest);
}

static void			ssl_print_invalid_s_param(char const *program)
{
	ft_printf("%s: Error: option requires an argument -- s\n",
		program);
}

static void			ssl_run_string(t_hash_fn_name *fn_name, t_ssl_flags *flags,
					char const *string)
{
	char			*digest;

	digest = fn_name->fn(string);
	if (!flags->is_q)
	{
		if (flags->is_r)
			ft_printf("%s \"%s\"\n", digest, string);
		else
			ft_printf("%s (\"%s\") = %s\n", fn_name->uc_name, string, digest);
	}
	else
		ft_printf("%s\n", digest);
	free(digest);
}

static void			ssl_print_file_error(t_ssl *ssl, char const *file,
					char const *error)
{
	ft_printf("%s: %s: %s: %s\n", ssl->program, ssl->fn_name.lc_name,
		file, error);
}

static char			*ssl_handle_context_from_file(t_ssl *ssl, char const *file, int *fd)
{
	char			*context;

	*fd = ft_open_file(file, FILE_READ);
	if (*fd == -1)
	{
		ssl_print_file_error(ssl, file, strerror(errno));
		return (0);
	}
	context = ft_readfd(*fd);
	if (context == 0)
	{
		ssl_print_file_error(ssl, file, strerror(errno));
		ft_close_file(*fd);
	}
	return (context);
}

static void			ssl_run_file(t_ssl *ssl, char const *file)
{
	char			*context;
	char			*digest;
	int				fd;

	context = ssl_handle_context_from_file(ssl, file, &fd);
	if (!context)
		return ;
	digest = ssl->fn_name.fn(context);
	if (!ssl->flags.is_q)
	{
		if (ssl->flags.is_r)
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

static void			ssl_run_args(t_ssl *ssl, size_t i, char **av)
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

int					main(int ac, char **av)
{
	t_ssl			ssl;
	size_t			i;

	if (ac == 1)
		return (ssl_print_usage(av[0]));
	ssl.program = av[0];
	if (!ssl_get_hash_fn_name(&ssl.fn_name, av[1]))
		return (ssl_print_invalid_fn(av[0], av[1]));
	i = ssl_parse_flags(&ssl.flags, av);
	if (ac == (2 + ssl.flags.is_p + ssl.flags.is_q + ssl.flags.is_r)
		|| ssl.flags.is_p)
		ssl_run_stdin(&ssl.fn_name, &ssl.flags);
	ssl_run_args(&ssl, i, av);
	return (0);
}
