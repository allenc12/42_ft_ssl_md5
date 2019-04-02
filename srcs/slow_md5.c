/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slow_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 22:10:52 by callen            #+#    #+#             */
/*   Updated: 2019/03/29 22:10:53 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_md5.h>
#include <libft.h>

/*
** Constant integer part of the sines of integers in radians * 2^32
*/

static const t_u32 k[64] = {
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

static const t_u32 r[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

void	ft_md5(const uint8_t *in, size_t ilen, uint8_t *dgst)
{
	uint32_t	h[4];
	uint8_t		*msg;
	uint32_t	w[16];
	uint32_t	a, b, c, d, i, f, g, tmp;
	size_t		nlen, offs;

	h[0] = 0x67452301;
	h[1] = 0xefcdab89;
	h[2] = 0x98badcfe;
	h[3] = 0x10325476;
	nlen = ilen;
	while (++nlen % 64 != 56)
		;
	msg = (uint8_t*)malloc(nlen + 8);
	ft_memcpy(msg, in, ilen);
	msg[ilen] = 0x80;
	offs = ilen;
	while (++offs < nlen)
		;
	ft_tobytes(ilen * 8, msg + nlen);
	ft_tobytes(ilen >> 29, msg + nlen + 4);
	offs = 0;
	while (offs < nlen)
	{
		for (i = 0; i < 16; i++) {
			w[i] = ft_toint(msg + offs + i * 4);
		}
		a = h[0];
		b = h[1];
		c = h[2];
		d = h[3];
		for (i = 0; i < 64; i++)
		{
			if (i < 16)
			{
				f = (b & c) | ((~b) & d);
				g = i;
			}
			else if (i < 32)
			{
				f = (d & b) | ((~d) & c);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			}
			else
			{
				f = c ^ (b | (~d));
				g = (7 * i) % 16;
			}
			tmp = d;
			d = c;
			c = b;
			b = b + RL((a + f + k[i] + w[g]), r[i]);
			a = tmp;
			offs += 64;
		}
		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
	}
	free(msg);
	ft_tobytes(h[0], dgst);
	ft_tobytes(h[1], dgst + 4);
	ft_tobytes(h[2], dgst + 8);
	ft_tobytes(h[3], dgst + 12);
}

void	ft_slow_md5(char const *msg, size_t len)
{
	size_t	i;
	t_u8		res[16];

	for (i = 0; i < 100000; i++)
		ft_md5((uint8_t*)msg, len, res);
	for (i = 0; i < 16; i++)
		ft_printf("%2.2x", res[i]);
	ft_putchar('\n');
}