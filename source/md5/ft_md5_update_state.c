/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_update_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 06:20:50 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 06:20:50 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

static void		md5_update_state_h(uint32_t const *ts, uint32_t *t1,
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

void			ft_md5_update_state(t_md5ctx *ctx, uint32_t *ts,
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
