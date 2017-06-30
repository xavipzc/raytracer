/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <rt.h>
	#include <vectors.h>
	#include <gpu_rt.h>
	#include <equation.h>
}

__host__ __device__ static t_vec3d	get_normal_cone(t_cone cone, t_ray ray,
		t_intersection intersection)
{
	t_vec3d axis_v;
	t_vec3d	normal_v;
	t_vec3d	x;
	double	m;
	double	k;

	k = cone.half_angle;
	x = vector_substract(ray.origin, cone.pos);
	axis_v = vector_normalize(vector_calculate(cone.pos, cone.up));
	m = vector_dot(ray.dir, vector_scalar(axis_v, intersection.t))
		+ vector_dot(x, axis_v);
	normal_v = vector_normalize(
			vector_substract(
				vector_substract(
					intersection.pos, cone.pos),
				vector_scalar(
					vector_scalar(
						axis_v, m), 1 + (k * k))));
	return (normal_v);
}

__host__ __device__ static int		get_cone(t_cone cone, t_camera camera,
		t_ray ray, t_intersection *intersection_tmp)
{
	t_vec3d	normal;
	t_vec3d	x;
	t_eq	eq;
	double	k;

	normal = vector_normalize(vector_calculate(cone.pos, cone.up));
	x = vector_calculate(cone.pos, ray.origin);
	k = cone.half_angle;
	eq.a = vector_dot(ray.dir, ray.dir)
		- (1 + k * k) * pow(vector_dot(ray.dir, normal), 2);
	eq.b = 2 * (vector_dot(ray.dir, x)
			- (1 + k * k) * (vector_dot(ray.dir, normal) * vector_dot(x, normal)));
	eq.c = vector_dot(x, x)
		- (1 + k * k) * pow(vector_dot(x, normal), 2);
	eq.res = second_degres(eq.a, eq.b, eq.c);
	if(eq.res != NOT_A_SOLUTION)
	{
		intersection_tmp->t = eq.res;
		intersection_tmp->type = 'x';
		return(1);
	}
	intersection_tmp->t = -1.0;
	return(0);
}

__host__ __device__ static void		get_dist_cone_face(t_cone cone, t_ray ray,  t_intersection intersection)
{
	double	t;
	double	denominator;
	t_vec3d	x;
	double	n;
	double tmp;
//	angle = tan(cone.half_angle * M_PI / 180.0);
//	radius = tan(angle * M_PI / 360.0) * cone.height / 2.0;
	if(cone.height > 0.0f)
	{
		tmp = vector_dot(intersection.normal_v, ray.dir);
		if (tmp < 0.0f || tmp > cone.height)
		{
//		intersection.t = t;
			intersection.normal_v = vector_normalize(vector_calculate(cone.pos, cone.up));
			denominator = vector_dot(ray.dir, intersection.normal_v);
			if (denominator != 0)
			{
				printf("test\n");
				x = vector_scalar(vector_calculate(cone.pos, ray.origin), -1);
				n = vector_dot(x, intersection.normal_v);
				t = n / denominator;
				if (t > 0.0000001)
				{
				intersection.t = t;
				if (denominator > 0)
					intersection.normal_v = vector_scalar(intersection.normal_v, -1);
				}
			}
		}
	}
	intersection.t = -1;
}
//		intersection.pos = pos;
//		intersection.normal_v.x = 0;
//		intersection.normal_v.y = 0;
//		intersection.normal_v.z = 1;
//	if ((rot = vector_dot(ray->dir, intersection_tmp->normal_v)) > 0.0f)
//			intersection_tmp->normal_v = -rot;
	//	t = (cone.height.y - ray.origin.z) / ray.dir.z;
	//	pos.x = ray.origin.x + t * ray.dir.x;
	//	pos.z = ray.origin.z + t * ray.dir.z;
	//	pos.y = cone.height.y;
	//	if (t > 0.0 && (t < intersection->t || intersection->t < 0.0)  && pos.x * pos.x + pos.z * pos.z <= cone.half_angle * cone.half_angle)
	//	{
	//		intersection->t = t;
	//	intersection->pos = pos;
	//	intersection->normal_v.x = 0;
	//	intersection->normal_v.y = 1;
	//	intersection->normal_v.z = 0;
	//	}
//	}

__host__ __device__ void			get_closest_cone(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.cones_len)
	{
		if (get_cone(world.cones[i], world.camera, ray, intersection_tmp) == 1)
		{
	//		intersection_tmp->pos = vector_add(ray.origin,
	//					vector_scalar(ray.dir, intersection_tmp->t));
	//		if((intersection_tmp->pos.y > world.cones[i].height || intersection_tmp->pos.y < world.cones[i].pos.y)
	//				&& world.cones[i].height != 0)
	//				intersection_tmp->t = -1;
//			if(intersection_tmp->pos.x > world.cones[i].height.x)// || intersection_tmp->pos.x < 0.0)
//					intersection_tmp->t = -1;
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflexion_coef = world.cones[i].reflexion_coef;
				intersection->color = &world.cones[i].color;
				intersection->pos = vector_add(ray.origin,
						vector_scalar(ray.dir, intersection_tmp->t));
				intersection->normal_v = get_normal_cone(world.cones[i],
						ray, *intersection);
	//			get_dist_cone_face(world.cones[i], ray, *intersection);
			}
		}
		i++;
	}
}
