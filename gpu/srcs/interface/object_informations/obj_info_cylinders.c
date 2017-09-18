/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_cylinders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/13 17:13:46 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

static void	draw_infos(struct nk_context *ctx, struct media *m, t_world *w,\
						int i)
{
	if (ui_widget_value_infos(ctx, m, &w->cylinders[i].pos.x, "POS X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].pos.y, "POS Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].pos.z, "POS Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].up.x, "NORMAL X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].up.y, "NORMAL Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].up.z, "NORMAL Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].height, "HEIGHT:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].radius, "RADIUS:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].reflection_coef,\
			"REFLECTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].refraction_coef,\
			"REFRACTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cylinders[i].transparence_coef,\
			"TRANSPARENCE:"))
		w->redraw = 1;
}

static void	draw_delete_button(struct nk_context *ctx, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(ctx, media, 10);
	ui_widget_centered(ctx, media, 30);
	if (nk_button_image_label(ctx, media->del, "DELETE OBJECT",\
		NK_TEXT_CENTERED))
	{
		remove_cylinder(&world->cylinders_tmp, &o);
		load_cylinders(&world->cylinders, world->cylinders_tmp,\
						&world->cylinders_len);
		world->redraw = 1;
	}
}

void		cylinder_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->cylinders_len)
	{
		if (world->id_save == world->cylinders[i].id)
		{
			header_info(ctx, media->cylinder, "CYLINDER");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->cylinders[i].color, world);
			refresh_cylinder(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}