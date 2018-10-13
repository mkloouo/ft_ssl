/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:29:46 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/14 16:12:56 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include <sys/types.h>
# include <stdint.h>

typedef char	*(*t_ch_func)(char const*, void*);

typedef struct	s_ssl_algo
{
	char		*name;
	t_ch_func	fn;
}				t_ssl_algo;

typedef struct	s_md5_v
{
	uint8_t		data[64];
	uint32_t	len;
	uint64_t	blen;
	uint32_t	state[4];
}				t_md5_v;

typedef struct	s_sha256_v
{
	uint8_t		data[64];
	uint32_t	len;
	uint64_t	blen;
	uint32_t	state[8];
}				t_sha256_v;

extern uint16_t const g_per_round_shifts[64];
extern uint64_t const g_int_part_of_sines_of_ints[64];

int				ft_print_ssl_usage(void);

char			*ft_sha256(char const *data, void *extra);
char			*ft_md5(char const *data, void *extra);

#endif
