/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 07:27:39 by mal-guna          #+#    #+#             */
/*   Updated: 2021/12/28 18:47:46 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen_moa(const char *str);
char	*ft_strjoin_moa(const char	*s1, const	char	*s2);
char	*ft_strchr_moa(const char *s, int c);
char	*ft_substr_moa(const	char	*s, unsigned int start, size_t len);
char	*ft_strdup_moa(const char *s);

#endif