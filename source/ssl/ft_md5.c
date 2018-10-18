/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 14:30:17 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 05:20:07 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/string.h>
#include <ft/io.h>
#include <ft/memory.h>

uint32_t const	g_md5_steps[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

uint32_t const	g_md5_constants[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void			md5_init_ctx(t_md5ctx *ctx, char const *data)
{
	init_ctx_data(&ctx->data, data, TRUE);
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
}

void			md5_fill_chunk(uint32_t *chunk, uint64_t chunk_move,
				t_md5ctx *ctx)
{
	uint64_t	i;
	uint64_t	j;
	uint8_t		*moved;

	moved = ctx->data.ctx + chunk_move;
	i = 0;
	j = 0;
	while (i < 16)
	{
		chunk[i] = (moved[j]) + (moved[j + 1] << 8) + (moved[j + 2] << 16) +
				(moved[j + 3] << 24);
		j += 4;
		++i;
	}
}

void			md5_update_state_h(uint32_t const *ts, uint32_t *t1,
				uint32_t *t2, uint32_t i)
{
	if (i < 16)
	{
		MD5_FF(ts[1], ts[2], ts[3], *t1, *t2, i);
	}
	else if (i >= 16 && i < 32)
	{
		MD5_GG(ts[1], ts[2], ts[3], *t1, *t2, i);
	}
	else if (i >= 32 && i < 48)
	{
		MD5_HH(ts[1], ts[2], ts[3], *t1, *t2, i);
	}
	else
	{
		MD5_II(ts[1], ts[2], ts[3], *t1, *t2, i);
	}
}

void			md5_update_state(t_md5ctx *ctx, uint32_t *ts,
				uint32_t const *chunk)
{
	uint32_t	i;
	uint32_t	t1;
	uint32_t	t2;

	i = 0;
	while (i < 64)
	{
		md5_update_state_h(ts, &t1, &t2, i);
		t1 = t1 + ts[0] + g_md5_constants[i] + chunk[t2];
		ts[0] = ts[3];
		ts[3] = ts[2];
		ts[2] = ts[1];
		ts[1] += SSL_LR(t1, g_md5_steps[i]);
		++i;
	}
	i = 0;
	while (i < 4)
	{
		ctx->state[i] += ts[i];
		++i;
	}
}

char			*md5_get_digest(t_md5ctx *ctx)
{
	char		*digest;
	uint32_t	i;
	uint8_t		hash[16];

	i = 0;
	while (i < 4)
	{
		hash[i] = (uint8_t)((ctx->state[0] >> (i * 8)) & 0x000000ff);
		hash[i + 4] = (uint8_t)((ctx->state[1] >> (i * 8)) & 0x000000ff);
		hash[i + 8] = (uint8_t)((ctx->state[2] >> (i * 8)) & 0x000000ff);
		hash[i + 12] = (uint8_t)((ctx->state[3] >> (i * 8)) & 0x000000ff);
		++i;
	}
	digest = ft_strnew(32, 0);
	i = 0;
	while (i < 16)
	{
		ft_sprintf(digest + (i * 2), "%2.2x", hash[i]);
		++i;
	}
	return (digest);
}

char			*ft_md5(char const *data)
{
	uint64_t	chunk_move;
	uint32_t	chunk[16];
	t_md5ctx	ctx;
	uint32_t	ts[4];
	char		*digest;

	md5_init_ctx(&ctx, data);
	ft_memset(chunk, 0, sizeof(uint32_t) * 16);
	chunk_move = 0;
	while (chunk_move < ctx.data.len)
	{
		md5_fill_chunk(chunk, chunk_move, &ctx);
		ft_memcpy(ts, ctx.state, sizeof(uint32_t) * 4);
		md5_update_state(&ctx, ts, chunk);
		chunk_move += 64;
	}
	digest = md5_get_digest(&ctx);
	free(ctx.data.ctx);
	return (digest);
}
