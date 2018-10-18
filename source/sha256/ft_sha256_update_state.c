/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_update_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 06:21:22 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/18 06:21:38 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/ssl.h>

static void		sha256_update_state_h(uint32_t *ts, uint32_t t1, uint32_t t2)
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
