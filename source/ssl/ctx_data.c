/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 04:21:25 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 04:22:03 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

#include <ft/string.h>

static void		init_ctx_data_h(t_ctx_data *ctx_data, char const *data,
				uint64_t data_len)
{
	ctx_data->bitlen = (data_len * 8) + 1;
	while ((ctx_data->bitlen % 512) != 448)
		ctx_data->bitlen++;
	ctx_data->bitlen += 64;
	ctx_data->len = ctx_data->bitlen / 8;
	ctx_data->ctx = (uint8_t*)ft_strnew(ctx_data->len, 0);
	ft_strncpy((char*)ctx_data->ctx, data, data_len);
	ctx_data->ctx[data_len] = (uint8_t)0x80;
}

void			init_ctx_data(t_ctx_data *ctx_data, char const *data,
				t_bool little_endian)
{
	uint64_t	data_len;
	uint64_t	data_bitlen;
	int16_t		from;
	int16_t		to;
	int16_t		bit_step;

	data_len = ft_strlen(data);
	data_bitlen = data_len * 8;
	init_ctx_data_h(ctx_data, data, data_len);
	from = (int16_t)(little_endian ? 8 : 1);
	to = (int16_t)(little_endian ? 1 : 8);
	bit_step = 0;
	while (42)
	{
		ctx_data->ctx[ctx_data->len - from] = (uint8_t)
				(data_bitlen >> bit_step);
		from += (little_endian ? -1 : 1);
		bit_step += 8;
		if (from == to)
		{
			ctx_data->ctx[ctx_data->len - from] = (uint8_t)
					(data_bitlen >> bit_step);
			break ;
		}
	}
}
