/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:29:46 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/16 19:17:19 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include <sys/types.h>
# include <stdint.h>
# include <ft/list.h>

# define SSL_ERROR_MSG_LEN (255)

typedef enum			e_ssl_data_type
{
	SSL_STRING_DATA_TYPE,
	SSL_FILE_DATA_TYPE
}						t_ssl_data_type;

typedef struct			s_ssl_data
{
	char const			*data;
	t_ssl_data_type		type;
}						t_ssl_data;

struct s_ssl_command;
typedef void			(*t_ssl_run_func)(struct s_ssl_command*, t_ssl_data);

typedef struct			s_ssl_command
{
	void				*command;
	t_ssl_run_func		run;
}						t_ssl_command;

typedef struct			s_ssl
{
	char				*parse_error_msg;
	unsigned			read_stdin:1;
	unsigned			parse_error:1;
	t_list				*args;
	t_ssl_command		command;
	char const			*program;
}						t_ssl;

typedef char			*(*t_ssl_hash_func)(char const*);

typedef struct			s_md_command
{
	char const			*lc_name;
	char const			*uc_name;
	t_ssl_hash_func		f;
}						t_md_command;

extern t_md_command		g_md_commands[];

char					*ft_sha256(char const *data);
char					*ft_md5(char const *ctx);

void					ssl_init(t_ssl *ssl, char const *program);

void					ft_ssl_parse_flags(t_ssl *ssl, int ac, char **av);

void					ft_ssl_print_usage(t_ssl *ssl);
void					ft_ssl_print_md_commands(void);
void					ft_ssl_print_c_commands(void);

void					ft_ssl_run_md(t_ssl_command *command, t_ssl_data data);

#endif
