/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 00:03:28 by callen            #+#    #+#             */
/*   Updated: 2019/04/05 23:05:27 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <sys/stat.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>

/*
** Allowed functions:[open, close, read, write, malloc, free]
** md5 && sha256:
**    -p echo stdin to stdout and append hash to stdout
**    -q quiet mode
**    -r reverse output
**    -s hash args as strings
**    -c verify checksum input
**    if none then openssl-esque cli-interface
*/

# ifdef FT_SSL_VERSION
#  undef FT_SSL_VERSION
# endif
# define FT_SSL_VERSION "0.0042"

typedef unsigned long	t_ul;
typedef uint64_t	t_u64;
typedef uint32_t	t_u32;
typedef uint16_t	t_u16;
typedef uint8_t	t_u8;
typedef struct s_i32v	t_i32v;
typedef struct s_hash	t_hash;
typedef enum e_dgsts	t_dgsts;

struct	s_i32v
{
	int	x;
	int	y;
};

struct	s_hash
{
	void		(*f)(t_hash*);
	void		(*init)();
	void		(*update)();
	void		(*final)();
	void		(*print)(t_hash*);
	void		*ctx;
	char		*path;
	char		*cpth;
	char		**av;
	char		*strarg;
	char		**t;
	struct stat	st;
	int			cfd;
	int			err;
	int			dgst_len;
	int			ac;
	int			c;
	t_i32v		id;
	int			hc2dgst;
	int			digest;
	int			bsd;
	int			echo;
	int			quiet;
	int			string;
	int			check;
	int			shell;
	int			help;
};

enum
{
	INVAL_DIGEST_SIZE = (0),
	MD5_DIGEST_SIZE = (128 / 8),
	SHA1_DIGEST_SIZE = (160 / 8),
	SHA224_DIGEST_SIZE = (224 / 8),
	SHA256_DIGEST_SIZE = (256 / 8),
	SHA384_DIGEST_SIZE = (384 / 8),
	SHA512_DIGEST_SIZE = (512 / 8),
};

enum	e_stdcmd
{
	DGST,
	HELP,
	VER
};

static char	*g_s[] = {
	"dgst",
	"help",
	"version",
	NULL
};

enum	e_dgsts
{
	INVAL,
	MD5,
	SHA1,
	SHA224,
	SHA256,
	SHA384,
	SHA512,
	SHA512224,
	SHA512256
};

static char	*g_h[] = {
	"md5",
	"sha1",
	"sha224",
	"sha256",
	"sha384",
	"sha512",
	"sha512-224",
	"sha512-256",
	NULL
};

static char	*g_c[] = {
	NULL
};

void	ft_ssl_command_usage(t_hash *h);
void	ft_ssl_command_help(t_hash *h);

#endif
