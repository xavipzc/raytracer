/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_h_cubes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 08:13:23 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/26 16:30:15 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

static void	draw_infos(struct nk_context *c, struct media *m, t_world *w,\
						int i)
{
	ui_widget_value_infos(c, m, &w->h_cubes[i].pos.x, "POS X:");
	ui_widget_value_infos(c, m, &w->h_cubes[i].pos.y, "POS Y:");
	ui_widget_value_infos(c, m, &w->h_cubes[i].pos.z, "POS Z:");
	ui_slide_float_0_to_1(c, &w->h_cubes[i].reflection_coef, "REFLECTION:");
	ui_slide_float_0_to_2(c, &w->h_cubes[i].refraction_coef, "REFRACTION:");
	ui_slide_float_0_to_1(c, &w->h_cubes[i].transparence_coef, "Transparence:");
	draw_infos_next(c, m, &w->h_cubes[i].perlin, w);
	draw_apply_button(c, m, w);
	draw_p_presets(c, m, w, &w->h_cubes[i].perlin);
}

static void	draw_delete_button(struct nk_context *c, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(c, media, 10);
	ui_widget_centered(c, media, 20);
	nk_style_set_font(c, &media->font_14->handle);
	if (nk_button_image_label(c, media->del, "DELETE OBJECT", NK_TEXT_CENTERED))
	{
		remove_h_cube(&world->h_cubes_tmp, &o);
		load_h_cubes(&world->h_cubes, world->h_cubes_tmp, &world->h_cubes_len);
		world->redraw = 1;
	}
}

void		h_cube_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->h_cubes_len)
	{
		if (world->id_save == world->h_cubes[i].id)
		{
			header_info(ctx, media->h_cube, "HOLLOW CUBE");
			draw_infos(ctx, media, world, i);
			ui_widget_centered(ctx, media, 5);
			ui_header(ctx, media, "---- Colors ----");
			nk_style_set_font(ctx, &media->font_14->handle);
			draw_color_picker(ctx, &world->h_cubes[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, media, world, &world->h_cubes[i].chess);
			refresh_h_cube(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			if (move_object_without_norm(ctx, &world->h_cubes[i].pos))
				world->redraw = 1;
			break ;
		}
		i++;
	}
}
