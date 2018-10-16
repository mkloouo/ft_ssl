/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 16:09:58 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/16 19:43:40 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/io.h>
#include <ft/string.h>
#include <ft/memory.h>
#include <ft/list.h>

char				*get_file_contents(int fd)
{
	char 			*total;
	char 			buff[BUFF_SIZE + 1];
	size_t			t_size;
	ssize_t			rd;

	total = 0;
	t_size = 0;
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = 0;
		total = ft_resize_str(total, t_size, t_size + rd);
		ft_strncpy(&total[t_size], buff, (size_t)rd);
		t_size += rd;
	}
	if (rd == 0 && total == 0)
		total = ft_strnew(0, 0);
	return (total);
}

int					main(int ac, char **av)
{
	char 			*stdin_fd;
	t_ssl			ssl;

	ft_ssl_parse_flags(&ssl, ac, av);
	if (ssl.parse_error)
	{
		ft_ssl_print_usage(&ssl);
		return (1);
	}
	if (ssl.read_stdin)
	{
		stdin_fd = get_file_contents(IO_STDIN);
		ssl.command.run(&ssl.command,
				(t_ssl_data){stdin_fd, SSL_STRING_DATA_TYPE});
	}
	while (ssl.args)
	{
		ssl.command.run(&ssl.command, *(t_ssl_data*)ssl.args->data);
		ssl.args = ssl.args->next;
	}
	return (0);
}
