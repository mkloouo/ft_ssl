/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 14:30:17 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/17 02:11:17 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/string.h>
#include <ft/io.h>
#include <ft/memory.h>

#define LEFT_ROTATE(A,B) ((A << B) | (A >> (32 - B)))

char			*ft_md5(char const *ctx)
{
	uint32_t const	steps[64] = {
			7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
			5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
			6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};

	uint32_t const	constants[64] = {
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

	uint64_t ctx_len = ft_strlen(ctx);
	uint64_t ctx_len_bits = (ctx_len * 8);

	uint64_t padd_len_bits = ctx_len_bits + 1;
	while (padd_len_bits % 512 != 448)
		padd_len_bits++;

	uint64_t padd_ctx_len_bits = padd_len_bits + 64;
	uint64_t padd_ctx_len = padd_ctx_len_bits / 8;

	uint8_t *padd_ctx = (uint8_t*)ft_strnew(padd_ctx_len, 0);
	ft_strncpy((char*)padd_ctx, ctx, ctx_len);

	padd_ctx[ctx_len] = (uint8_t)0x80;

	padd_ctx[padd_ctx_len - 8] = (uint8_t)ctx_len_bits;
	padd_ctx[padd_ctx_len - 7] = (uint8_t)(ctx_len_bits >> 8);
	padd_ctx[padd_ctx_len - 6] = (uint8_t)(ctx_len_bits >> 16);
	padd_ctx[padd_ctx_len - 5] = (uint8_t)(ctx_len_bits >> 24);
	padd_ctx[padd_ctx_len - 4] = (uint8_t)(ctx_len_bits >> 32);
	padd_ctx[padd_ctx_len - 3] = (uint8_t)(ctx_len_bits >> 40);
	padd_ctx[padd_ctx_len - 2] = (uint8_t)(ctx_len_bits >> 48);
	padd_ctx[padd_ctx_len - 1] = (uint8_t)(ctx_len_bits >> 56);

	uint32_t a0 = 0x67452301;
	uint32_t b0 = 0xefcdab89;
	uint32_t c0 = 0x98badcfe;
	uint32_t d0 = 0x10325476;

	uint32_t chunk[16] = {0};
	for (size_t chunk_move = 0; chunk_move < padd_ctx_len; chunk_move += 64)
	{
		uint8_t *tmp = padd_ctx + chunk_move;
		for (size_t i = 0, j = 0; i < 16; ++i, j += 4)
			chunk[i] = (tmp[j]) + (tmp[j + 1] << 8) + (tmp[j + 2] << 16) +
					(tmp[j + 3] << 24);

		uint32_t A = a0, B = b0, C = c0, D = d0;
		for (uint32_t iter = 0; iter < 64; ++iter)
		{
			uint32_t F, g;
			if (iter < 16)
			{
				F = (B & C) | ((~B) & D);
				g = iter;
			}
			else if (iter >= 16 && iter < 32)
			{
				F = (D & B) | ((~D) & C);
				g = (5 * iter + 1) % 16;
			}
			else if (iter >= 32 && iter < 48)
			{
				F = B ^ C ^ D;
				g = (3 * iter + 5) % 16;
			}
			else
			{
				F = C ^ (B | (~D));
				g = (7 * iter) % 16;
			}

			F = F + A + constants[iter] + chunk[g];
			A = D;
			D = C;
			C = B;
			B = B + LEFT_ROTATE(F, steps[iter]);
		}

		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}

	uint8_t hash[16];
	for (size_t i = 0; i < 4; ++i) {
		hash[i] = (uint8_t)((a0 >> (i * 8)) & 0x000000ff);
		hash[i + 4] = (uint8_t)((b0 >> (i * 8)) & 0x000000ff);
		hash[i + 8] = (uint8_t)((c0 >> (i * 8)) & 0x000000ff);
		hash[i + 12] = (uint8_t)((d0 >> (i * 8)) & 0x000000ff);
	}

	char *s_hash = ft_strnew(32, 0);
	for (size_t i = 0; i < 16; ++i)
		ft_sprintf(s_hash + (i * 2), "%2.2x", hash[i]);

	free(padd_ctx);
	return (s_hash);
}
