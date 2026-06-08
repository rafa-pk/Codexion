/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 10:20:08 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/07 18:11:43 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// SCHEDULER
# define FIFO 1
# define EDF 0

// ERROR MESSAGES
# define TOO_MANY_ARGS "Error: Too many arguments passed (8 required)\n"
# define NOT_ENOUGH_ARGS "Error: Not enough arguments passed (8 required)\n"
# define NON_INT "Parsing Error: argument is not a valid positive integer\n"
# define INT_OVERFLOW "Parsing Error: argument exceeds INT_MAX\n"
# define INV_SCHEDULER "Parsing Error: Scheduler only accepts 'fifo' or 'edf'\n"
# define SIM_FAILED "Simulation Error: Exiting cleanly"

#endif
