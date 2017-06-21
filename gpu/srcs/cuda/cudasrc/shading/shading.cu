/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include "rt.h"
	#include "gpu_rt.h"
	#include <equation.h>
}
#include <float.h>

__host__ __device__ int		get_shadow(t_world world, t_light light,
													t_intersection collision)
{
	t_intersection	collision_tmp;
	t_ray			shadow;
	double			dist_light;
	double			dist_intersection;

	collision_tmp.t = DBL_MAX;
	collision_tmp.type = '0';
	shadow.dir = vector_calculate(collision.pos, light.pos);
	shadow.origin = collision.pos;
	dist_light = vector_length(shadow.dir);
	if (get_closest_intersection(world, shadow, &collision_tmp) == 1)
	{
		dist_intersection = vector_length(vector_calculate(collision.pos,
												collision_tmp.pos));
		if (dist_intersection < dist_light)
			return (1);
	}
	return (0);
}

__host__ __device__ void	specular_light(t_color *color, t_vec3d ray,
	t_intersection intersection, t_vec3d light_vector, t_light light)
{
	t_vec3d reflected_vector;
	double	specular_angle;

	reflected_vector = vector_substract(ray, vector_scalar(
		intersection.normal_v,2 * vector_dot(ray, intersection.normal_v)));
	reflected_vector = vector_normalize(reflected_vector);
	specular_angle = pow(vector_dot(light_vector, reflected_vector), 150);
	color_scalar(&light.color, specular_angle);
	color_scalar(&light.color, intersection.reflexion_coef);
	color_scalar(&light.color, light.intensity_coef);	
	color_add(color, light.color);
}

__host__ __device__	void	get_light_at(t_world world, t_color *color,
	t_light light, t_intersection intersection, t_ray ray)
{
	t_vec3d	light_vector;
	t_color	tmp;
	double	angle;	

	tmp =  new_color(0, 0, 0);
	light_vector = vector_normalize(vector_calculate(intersection.pos,
														light.pos));
	angle = vector_dot(intersection.normal_v, light_vector);
	if (angle > 0 && get_shadow(world, light, intersection) == 0)
	{
		color_add(&tmp, *intersection.color);
		color_scalar(&tmp, angle);
		color_scalar(&tmp, light.intensity_coef);		
		color_add(color, tmp);
		specular_light(color, ray.dir, intersection,
									light_vector, light);
	}
}
