/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:29:46 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/15 19:44:31 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include <sys/types.h>
# include <stdint.h>

typedef char		*(*t_md_func)(char const*);

typedef struct		s_md_pair
{
	char const		*name;
	t_md_func		f;
}					t_md_pair;

extern t_md_pair	g_md_pairs[];

char				*ft_sha256(char const *data);
char				*ft_md5(char const *ctx);

typedef struct		s_ssl_flags
{
	unsigned		p:1;
	unsigned		q:1;
	unsigned		r:1;
	unsigned		s:1;
}					t_ssl_flags;

#endif
