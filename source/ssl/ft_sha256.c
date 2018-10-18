/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:23:31 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 05:13:59 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/string.h>
#include <ft/io.h>
#include <ft/memory.h>

uint32_t const g_sha256_constants[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void			sha256_init_ctx(t_sha256ctx *ctx, char const *data)
{
	init_ctx_data(&ctx->data, data, FALSE);
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void			sha256_fill_chunk(uint32_t *chunk, uint64_t chunk_move,
				t_sha256ctx *ctx)
{
	uint64_t	i;
	uint64_t	j;
	uint32_t	s0;
	uint32_t	s1;
	uint8_t		*moved;

	moved = ctx->data.ctx + chunk_move;
	i = 0;
	j = 0;
	while (i < 16)
	{
		chunk[i] = (moved[j] << 24) | (moved[j + 1] << 16) |
			(moved[j + 2] << 8) | (moved[j + 3]);
		j += 4;
		++i;
	}
	while (i < 64)
	{
		s0 = SSL_RR(chunk[i - 15], 7) ^ SSL_RR(chunk[i - 15], 18) ^
				(chunk[i - 15] >> 3);
		s1 = SSL_RR(chunk[i - 2], 17) ^ SSL_RR(chunk[i - 2], 19) ^
				(chunk[i - 2] >> 10);
		chunk[i] = chunk[i - 16] + s0 + chunk[i - 7] + s1;
		++i;
	}
}

void			sha256_update_state_h(uint32_t *ts, uint32_t t1, uint32_t t2)
{
	int64_t		j;

	j = 7;
	while (j >= 0)
	{
		if (j != 4 && j != 0)
			ts[j] = ts[j - 1];
		else if (j == 4)
			ts[j] = ts[j - 1] + t1;
		else
			ts[j] = t1 + t2;
		--j;
	}
}

void			sha256_update_state(t_sha256ctx *ctx, uint32_t *ts,
				uint32_t const *chunk)
{
	int64_t		i;
	uint32_t	t1;
	uint32_t	t2;

	i = 0;
	while (i < 64)
	{
		t1 = ts[7] + SHA256_S1(ts[4]) + SHA256_CH(ts[4], ts[5], ts[6]) +
			g_sha256_constants[i] + chunk[i];
		t2 = SHA256_S0(ts[0]) + SHA256_MAJ(ts[0], ts[1], ts[2]);
		sha256_update_state_h(ts, t1, t2);
		++i;
	}
	i = 0;
	while (i < 8)
	{
		ctx->state[i] += ts[i];
		++i;
	}
}

char			*sha256_get_digest(t_sha256ctx *ctx)
{
	uint32_t	i;
	uint32_t	j;
	char		*digest;

	digest = ft_strnew(64, 0);
	i = 0;
	j = 0;
	while (i < 8)
	{
		ft_sprintf(digest + j, "%8.8x", ctx->state[i]);
		j += 8;
		++i;
	}
	return (digest);
}

char			*ft_sha256(char const *data)
{
	uint64_t	chunk_move;
	uint32_t	chunk[64];
	t_sha256ctx	ctx;
	uint32_t	ts[8];
	char		*digest;

	sha256_init_ctx(&ctx, data);
	chunk_move = 0;
	while (chunk_move < ctx.data.len)
	{
		ft_memset(chunk, 0, sizeof(uint32_t) * 64);
		sha256_fill_chunk(chunk, chunk_move, &ctx);
		ft_memcpy(ts, ctx.state, sizeof(uint32_t) * 8);
		sha256_update_state(&ctx, ts, chunk);
		chunk_move += 64;
	}
	digest = sha256_get_digest(&ctx);
	free(ctx.data.ctx);
	return (digest);
}
