/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:29:46 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/17 04:07:52 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include <sys/types.h>
# include <stdint.h>

typedef char			*(*t_hash_fn)(char const*);

typedef struct			s_hash_fn_name
{
	t_hash_fn			fn;
	char const			*lc_name;
	char const			*uc_name;
}						t_hash_fn_name;

typedef struct			s_ssl_flags
{
	unsigned			is_p:1;
	unsigned			is_q:1;
	unsigned			is_r:1;
}						t_ssl_flags;

typedef struct			s_ssl
{
	t_hash_fn_name		fn_name;
	t_ssl_flags			flags;
	char const			*program;
}						t_ssl;

char					*ft_sha256(char const *ctx);
char					*ft_md5(char const *ctx);

extern t_hash_fn_name	g_hash_fn_name_arr[];

#endif
