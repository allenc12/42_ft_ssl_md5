/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:04:42 by callen            #+#    #+#             */
/*   Updated: 2019/04/02 20:04:43 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>
#include <ft_md5.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void	ft_md5_init(t_md5_ctx *c)
{
	c->count[0] = 0;
	c->count[1] = 0;
	c->state[0] = 0x67452301;
	c->state[1] = 0xEFCDAB89;
	c->state[2] = 0x98BADCFE;
	c->state[3] = 0x10325476;
}
