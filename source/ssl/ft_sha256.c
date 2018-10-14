/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:23:31 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/14 23:08:14 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/string.h>
#include <ft/io.h>
#include <ft/memory.h>

#define RIGHT_ROT(A, B) (((A) >> (B)) | ((A) << (32 - (B))))

char		*ft_sha256(char const *data, void *extra)
{
	(void)extra;
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

	uint32_t const K[64] = {
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

	uint64_t data_len = ft_strlen(data);

	uint64_t msg_len_bits = (data_len * 8);
	msg_len_bits += 1;
	uint64_t to_fill = (448 - msg_len_bits % 512);
	msg_len_bits += to_fill + 64;
	uint64_t msg_len = msg_len_bits / 8;

	uint8_t *msg = (uint8_t*)ft_strnew(msg_len, 0);
	ft_strncpy((char*)msg, data, data_len);
	msg[data_len] = (uint8_t)0x80;

	msg[msg_len - 1] = *((uint8_t*)&data_len);
	msg[msg_len - 2] = *((uint8_t*)&data_len + 1);
	msg[msg_len - 3] = *((uint8_t*)&data_len + 2);
	msg[msg_len - 4] = *((uint8_t*)&data_len + 3);
	msg[msg_len - 5] = *((uint8_t*)&data_len + 4);
	msg[msg_len - 6] = *((uint8_t*)&data_len + 5);
	msg[msg_len - 7] = *((uint8_t*)&data_len + 6);
	msg[msg_len - 8] = *((uint8_t*)&data_len + 7);

	for (size_t chunk_i = 0; chunk_i < msg_len; chunk_i += 64)
	{
		size_t i, j;
		uint32_t w[64] = {0};
		for (i = 0, j = 0; i < 16; ++i, j += 4)
			w[i] = (msg[j] << 24) | (msg[j + 1] << 16) |
					(msg[j + 2] << 8) | (msg[j + 3]);
		for (; i < 64; ++i)
		{
			uint32_t s0 = RIGHT_ROT(w[i - 15], 7) ^RIGHT_ROT(w[i - 15], 18) ^
					(w[i - 15] >> 3);
			uint32_t s1 = RIGHT_ROT(w[i - 2], 17) ^RIGHT_ROT(w[i - 2], 19) ^
					(w[i - 2] >> 10);
			w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		}

		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;
		uint32_t e = h4;
		uint32_t f = h5;
		uint32_t g = h6;
		uint32_t h = h7;

		for (j = 0; j < 64; ++j)
		{
			uint32_t S1 = RIGHT_ROT(e, 6) ^ RIGHT_ROT(e, 11) ^ RIGHT_ROT(e, 25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = h + S1 + ch + K[j] + w[j];
			uint32_t S0 = RIGHT_ROT(a, 2) ^ RIGHT_ROT(a, 13) ^ RIGHT_ROT(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = S0 + maj;

			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}

		h0 = h0 + a;
		h1 = h1 + b;
		h2 = h2 + c;
		h3 = h3 + d;
		h4 = h4 + e;
		h5 = h5 + f;
		h6 = h6 + g;
		h7 = h7 + h;
	}

	char *digest = ft_strnew(64, 0);

	ft_sprintf(digest, "%8.8x", h0);
	ft_sprintf(digest + 8, "%8.8x", h1);
	ft_sprintf(digest + 16, "%8.8x", h2);
	ft_sprintf(digest + 24, "%8.8x", h3);
	ft_sprintf(digest + 32, "%8.8x", h4);
	ft_sprintf(digest + 40, "%8.8x", h5);
	ft_sprintf(digest + 48, "%8.8x", h6);
	ft_sprintf(digest + 56, "%8.8x\n", h7);

	free(msg);
	return (digest);
}
