/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:29:46 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 06:42:50 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include <sys/types.h>
# include <stdint.h>
# include <ft/bool.h>

# define SSL_LR(A,B) (((A) << (B)) | ((A) >> (32 - (B))))
# define SSL_RR(A, B) (((A) >> (B)) | ((A) << (32 - (B))))

# define SHA256_S0(A) (SSL_RR((A), 2) ^ SSL_RR((A), 13) ^ SSL_RR((A), 22))
# define SHA256_S1(E) (SSL_RR((E), 6) ^ SSL_RR((E), 11) ^ SSL_RR((E), 25))
# define SHA256_CH(E, F, G) (((E) & (F)) ^ ((~(E)) & (G)))
# define SHA256_MAJ(A, B, C) (((A) & (B)) ^ ((A) & (C)) ^ ((B) & (C)))

# define MD5_F(B, C, D) ((B & C) | ((~B) & D))
# define MD5_FF(B, C, D, F, G, I) F = MD5_F(B, C, D); G = I
# define MD5_G(B, C, D) ((D & B) | ((~D) & C))
# define MD5_GG(B, C, D, F, G, I) F = MD5_G(B, C, D); G = (5 * I + 1) % 16
# define MD5_H(B, C, D) (B ^ C ^ D)
# define MD5_HH(B, C, D, F, G, I) F = MD5_H(B, C, D); G = (3 * I + 5) % 16
# define MD5_I(B, C, D) (C ^ (B | (~D)))
# define MD5_II(B, C, D, F, G, I) F = MD5_I(B, C, D); G = (7 * I) % 16

typedef char			*(*t_hash_fn)(char const*);

typedef struct			s_hash_fn_name
{
	t_hash_fn			fn;
	char const			*lc_name;
	char const			*uc_name;
}						t_hash_fn_name;

typedef struct			s_ssl_flags
{
	unsigned			p_flag:1;
	unsigned			q_flag:1;
	unsigned			r_flag:1;
}						t_ssl_flags;

typedef struct			s_ssl
{
	t_hash_fn_name		fn_name;
	t_ssl_flags			flags;
	char const			*program;
}						t_ssl;

typedef struct			s_ctx_data
{
	uint8_t				*ctx;
	uint64_t			len;
	uint64_t			bitlen;
}						t_ctx_data;

typedef struct			s_sha256ctx
{
	t_ctx_data			data;
	uint32_t			state[8];
}						t_sha256ctx;

typedef struct			s_md5ctx
{
	t_ctx_data			data;
	uint32_t			state[4];
}						t_md5ctx;

extern t_hash_fn_name	g_hash_fn_name_arr[];
extern uint32_t const	g_sha256_constants[];
extern uint32_t const	g_md5_steps[];
extern uint32_t const	g_md5_constants[];

/*
** ssl.c
*/

void					init_ssl(t_ssl *ssl, char const *program);

/*
** ssl_run.c
*/

void					ssl_run_stdin(t_hash_fn_name *fn_name,
						t_ssl_flags *flags);
void					ssl_run_string(t_hash_fn_name *fn_name,
						t_ssl_flags *flags, char const *string);
void					ssl_run_file(t_ssl *ssl, char const *file);
void					ssl_run_args(t_ssl *ssl, size_t i, char **av);

/*
** ssl_print.c
*/

int						ssl_print_usage(char const *program);
void					ssl_print_md_cmds(void);
void					ssl_print_c_cmds(void);

/*
** ssl_print_invalid.c
*/

int						ssl_print_invalid_fn(char const *program,
						char const *invalid_fn);
void					ssl_print_invalid_s_param(char const *program);
void					ssl_print_file_error(t_ssl *ssl, char const *file,
						char const *error);

/*
** ssl_parse.c
*/

int						ssl_get_hash_fn_name(t_hash_fn_name *fn_name,
						char const *arg);
size_t					ssl_parse_flags(t_ssl_flags *flags, char **av);

/*
** ctx_data.c
*/

void					init_ctx_data(t_ctx_data *ctx_data, char const *data,
						t_bool little_endian);

/*
** ft_sha256.c
** ft_sha256_update_state.c
*/

char					*ft_sha256(char const *ctx);
void					sha256_init_ctx(t_sha256ctx *ctx, char const *data);
void					sha256_update_state(t_sha256ctx *ctx, uint32_t *ts,
						uint32_t const *chunk);
void					sha256_fill_chunk(uint32_t *chunk, uint64_t chunk_move,
						t_sha256ctx *ctx);
char					*sha256_get_digest(t_sha256ctx *ctx);

/*
** ft_md5.c
** ft_md5_update_state.c
*/

char					*ft_md5(char const *ctx);
void					ft_md5_init_ctx(t_md5ctx *ctx, char const *data);
void					ft_md5_fill_chunk(uint32_t *chunk, uint64_t chunk_move,
						t_md5ctx *ctx);
void					ft_md5_update_state(t_md5ctx *ctx,
						uint32_t *ts, uint32_t const *chunk);
char					*ft_md5_get_digest(t_md5ctx *ctx);

#endif
