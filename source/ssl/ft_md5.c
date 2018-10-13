/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 14:30:17 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/14 20:41:52 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>
#include <ft/string.h>
#include <ft/io.h>
#include <ft/memory.h>
#include <stdio.h>

static void		print_data(size_t padded_len, const unsigned char *data_padded);

#define LEFT_ROTATE(A,B) ((A << B) | (A >> (32 - B)))

/*
#define F(B,C,D) ((B & C) | (~B & D))
#define G(B,C,D) ((B & D) | (C & ~D))
#define H(B,C,D) (B ^ C ^ D)
#define I(B,C,D) (C ^ (B | ~D))

uint16_t const g_per_round_shifts[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

uint64_t const g_int_part_of_sines_of_ints[64] = {
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

void		init_md5_values(t_md5_v *values)
{
	(*values).len = 0;
	(*values).blen = 0;
	(*values).state[0] = 0x67452301;
	(*values).state[1] = 0xefcdab89;
	(*values).state[2] = 0x98badcfe;
	(*values).state[3] = 0x10325476;
}

t_bool		is_big_endian(void)
{
	uint64_t	test_value;

	test_value = 0xff000000;
	return (*((unsigned char*)&test_value) == 0xff);
}

*/

char		*ft_md5(char const *data, void *extra)
{
	(void)extra;

	uint32_t const	s[64] = {
			7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
			5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
			6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};
	(void)s;

	uint32_t const	K[64] = {
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
	(void)K;

	size_t data_len = ft_strlen(data);
	size_t msg_len_bits = (data_len * 8) + 1;

	size_t to_fill = 448 - (msg_len_bits % 512);

	size_t padded_bits_len = msg_len_bits + to_fill + 64;
	size_t padded_len = padded_bits_len / 8;

	uint8_t *data_padded = (uint8_t*)ft_strnew(padded_len, 0);
	ft_strncpy((char*)data_padded, data, data_len);

	data_padded[data_len] |= (uint8_t)0x80;

	data_padded[padded_len - 1] = *((uint8_t*)&data_len);
	data_padded[padded_len - 2] = *((uint8_t*)&data_len + 1);
	data_padded[padded_len - 3] = *((uint8_t*)&data_len + 2);
	data_padded[padded_len - 4] = *((uint8_t*)&data_len + 3);

	print_data(data_len, data_padded);

	uint32_t a0 = 0x67452301;
	uint32_t b0 = 0xefcdab89;
	uint32_t c0 = 0x98badcfe;
	uint32_t d0 = 0x10325476;

	uint32_t M[16];
	for (size_t i = 0; i < padded_len; i += 64)
	{
		for (size_t j = 0; j < 16; ++j)
			M[j] = *((uint32_t*)(data_padded + i) + j);
		uint32_t A = a0, B = b0, C = c0, D = d0;
		for (uint32_t k = 0; k < 64; ++k)
		{
			uint32_t F, g;
			if (k < 16)
			{
				F = (B & C) | ((~B) & D);
				g = k;
			}
			else if (k >= 16 && k < 32)
			{
				F = (D & B) | ((~D) & C);
				g = (5 * k + 1) % 16;
			}
			else if (k >= 32 && k < 48)
			{
				F = B ^ C ^ D;
				g = (3 * k + 5) % 16;
			}
			else
			{
				F = C ^ (B | (~D));
				g = (7 * k) % 16;
			}

			F = F + A + K[k] + M[g];
			A = D;
			D = C;
			C = B;
			B = B + LEFT_ROTATE(F, s[k]);
		}

		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}

	uint32_t digest[4] = {a0, b0, c0, d0};
	char *ret = ft_strnew(16, 0);
	for (size_t i = 0; i < 4; ++i)
		for (size_t j = 0; j < 4; ++j)
			ret[i * 4 + j] = *((uint8_t*)(digest + i) + j);

	char *ret_12 = ft_strnew(32, 0);
	for (size_t i = 0; i < 16; ++i)
		sprintf(ret_12 + (i * 2), "%2.2x", (uint8_t) ret[i]);

	free(data_padded);
	return (ret_12);
}

void print_data(size_t padded_len, const unsigned char *data_padded)
{
	for (size_t j = 0; j < padded_len; ++j)
		ft_printf("%1.1s %3.3d %2.2x %8.8b\n", (data_padded + j),
				data_padded[j], data_padded[j], data_padded[j]);
	ft_printf("\n");
}
