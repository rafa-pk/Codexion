/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:24:08 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/14 19:21:37 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

//TODO: taking cond logic
//lock and push coder to heap for both dongles
//lock global mutex
//cond wait and until coder->id == peak
//etc...

void	take_dongles(t_coder *coder)
{
	pthread
	take_left_dongle(coder);
	take_right_dongle(coder);
}
