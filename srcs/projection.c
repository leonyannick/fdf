/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:36:26 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/02 18:06:40 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * matrix multiplication: the number of columns in the first matrix must
 * be equal to the number of rows in the second matrix
 * m(rows) x n(columns)
*/
static t_pointd	*vec_mat_mul(t_pointd *p, const double m[3][3])
{
	t_pointd	*res;

	res = malloc(sizeof(t_pointd));
	if (!res)
		return (NULL);
	res->x = m[0][0] * p->x + m[0][1] * p->y + m[0][2] * p->z;
	res->y = m[1][0] * p->x + m[1][1] * p->y + m[1][2] * p->z;
	res->z = m[2][0] * p->x + m[2][1] * p->y + m[2][2] * p->z;
	return (res);
}

static t_pointd	*rotate_xaxis(t_pointd *point, double rad)
{
	const double	rot_x[3][3] = {
	{1,			0,		0},
	{0, cos(rad), sin(rad)},
	{0, -sin(rad), cos(rad)}};

	return (vec_mat_mul(point, rot_x));
}

static t_pointd	*rotate_yaxis(t_pointd *point, double rad)
{
	const double	rot_y[3][3] = {
	{cos(rad), 0, -sin(rad)},
	{0,		1,			0},
	{sin(rad), 0, cos(rad)}};

	return (vec_mat_mul(point, rot_y));
}

static t_pointd	*projection_to_2d(t_pointd *point)
{
	const double	proj[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 0}};

	return (vec_mat_mul(point, proj));
}

t_point	*isometric_proj(t_point *point)
{
	t_pointd	*temp;

	temp = malloc(sizeof(t_pointd));
	if (!temp)
		return (NULL);
	temp->x = (double)point->x;
	temp->y = (double)point->y;
	temp->z = (double)point->z;
	temp = rotate_xaxis(temp, asin(tan(DEG2RAD * 30)));
	temp = rotate_yaxis(temp, DEG2RAD * 45);
	temp = projection_to_2d(temp);
	point->x = (int)round(temp->x);
	point->y = (int)round(temp->y);
	point->z = 0;
	free(temp);
	return (point);
}
