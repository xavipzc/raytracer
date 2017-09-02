/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/27 18:05:20 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <effects.h>

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8 *pixel;

	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

/*
** Not fonctionnel
**	else if(world->keys.pad_8 == 1)
**		exposure_color(world->a_h);
*/

void	effect_application(t_world *world)
{
	printf("keyspad = %d\n", world->keys.pad_0);
	if (world->keys.pad_0 == 1)
		sepia_effect(world->a_h);
	else if (world->keys.pad_0 == 2)
		bayer_color(world->a_h);
	else if (world->keys.pad_0 == 3)
		eight_bit_effect(world->a_h);
	
	else if (world->keys.pad_0 == 4)
		pastel_effect(world->a_h, world->viewplane.y_res,
								world->viewplane.x_res);
	else if (world->keys.pad_0 == 5)
		black_and_white_effect(world->a_h);	
	// else if (world->keys.pad_0 == 1)
	// 	solarized_effect(world->a_h);

	// else if (world->keys.pad_0 == 1)
	// 	filter_color(world->a_h);
	else if (world->keys.pad_0 == 6)
		shell_shading_effect(world->a_h);
	else if (world->keys.pad_0 == 7)
		negative_color(world->a_h);
}

void	put_pixel_screen(t_world *world)
{
	int	i;
	int	j;
	int	y;
	int	x;

	i = 0;
	y = 0;
	effect_application(world);
	while (i < WIN_HEIGHT)
	{
		j = 0;
		x = 0;
		while (j < WIN_WIDTH)
		{
			pixel_to_image(world->window.screen, j, i,
					world->a_h[y * world->viewplane.x_res + x]);
			j++;
			if (j % world->render_factor == 0)
				x++;
		}
		i++;
		if (i % world->render_factor == 0)
			y++;
	}
}
