/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:29:46 by modnosum          #+#    #+#             */
/*   Updated: 2018/10/14 22:55:14 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include <sys/types.h>
# include <stdint.h>

char			*ft_sha256(char const *data, void *extra);
char			*ft_md5(char const *data, void *extra);

#endif
