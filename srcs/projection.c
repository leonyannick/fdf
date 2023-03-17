/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:36:26 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 12:08:42 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * mat * vec = x
 * matrix multiplication: the number of columns in the first matrix must
 * be equal to the number of rows in the second matrix
 * m(rows) x n(columns)
 * @param p point (vector) for multiplication
 * @param m 3x3 vector for multiplication
*/
static void	vec_mat_mul(t_point *p, const double m[3][3])
{
	double	x_temp;
	double	y_temp;
	double	z_temp;

	x_temp = p->x;
	y_temp = p->y;
	z_temp = p->z;
	p->x = m[0][0] * x_temp + m[0][1] * y_temp + m[0][2] * z_temp;
	p->y = m[1][0] * x_temp + m[1][1] * y_temp + m[1][2] * z_temp;
	p->z = m[2][0] * x_temp + m[2][1] * y_temp + m[2][2] * z_temp;
}

/**
 * point is rotated n radian around the x-axis
 * @param rad angle in radian
 * (multiply degree with macro DEG2RAD for radian value)
 * @param point point that is rotated
*/
void	rotate_xaxis(t_point *point, double rad)
{
	const double	rot_x[3][3] = {
	{1,			0,		0},
	{0, cos(rad), sin(rad)},
	{0, -sin(rad), cos(rad)}};

	vec_mat_mul(point, rot_x);
}

/**
 * point is rotated n radian around the y-axis
 * @param rad angle in radian
 * (multiply degree with macro DEG2RAD for radian value)
 * @param point point that is rotated
*/
void	rotate_yaxis(t_point *point, double rad)
{
	const double	rot_y[3][3] = {
	{cos(rad), 0, -sin(rad)},
	{0,		1,			0},
	{sin(rad), 0, cos(rad)}};

	vec_mat_mul(point, rot_y);
}

void	rotate_zaxis(t_point *point, double rad)
{
	const double	rot_y[3][3] = {
	{cos(rad), sin(rad),	0},
	{-sin(rad), cos(rad),	0},
	{0,			0,	1}};

	vec_mat_mul(point, rot_y);
}

/**
 * 3d point projected to 2d point (z coordinate is ommited)
 * not really necessary, as you could just not use the zcoordinate
*/
/* static t_pointd	*projection_to_2d(t_pointd *point)
{
	const double	proj[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 0}};

	return (vec_mat_mul(point, proj));
} */
