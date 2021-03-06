/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_scenes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 13:54:11 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/11 17:56:14 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "light.h"
#include "nuklear.h"
#include "gui.h"
#include "parse.h"

void		reset_camera(t_world *world, int i)
{
	static t_vec3d pos;
	static t_vec3d dir;

	if (i == 0)
	{
		pos = world->camera.pos;
		dir = world->camera.look_at;
	}
	else
	{
		world->camera.pos = pos;
		world->camera.look_at = dir;
	}
	world->camera.up_v = (t_vec3d){0, 1, 0};
	get_camera_axes(&world->camera);
}

static void	launch_scene_select(t_world *world, int i)
{
	char *nb;
	char *start;
	char *path;

	nb = ft_itoa(i);
	start = ft_strjoin("scenes/", nb);
	ft_strdel(&nb);
	path = ft_strjoin(start, ".xml");
	ft_strdel(&start);
	if (parser_checker(path))
	{
		clear_world(world);
		parse_rtv1(world, path);
		ft_strdel(&path);
		reset_camera(world, 0);
		load_data(world);
		rt(world);
		world->img_scene = i;
		world->redraw = 3;
	}
	else
	{
		ft_strdel(&path);
		ft_putendl("Please, enter a valid xml file. Read dtd/norme.dtd");
	}
}

void		press_launch(struct nk_context *ctx, t_world *world,\
						int img_active[5])
{
	if (nk_button_label(ctx, "Launch") && world->render_factor == 1)
	{
		if (img_active[2] == 1)
			launch_scene_select(world, 1);
		else if (img_active[2] == 2)
			launch_scene_select(world, 2);
		else if (img_active[2] == 3)
			launch_scene_select(world, 3);
		else if (img_active[2] == 4)
			launch_scene_select(world, 4);
		else if (img_active[2] == 5)
			launch_scene_select(world, 5);
		else if (img_active[2] == 6)
			launch_scene_select(world, 6);
		else if (img_active[2] == 7)
			launch_scene_select(world, 7);
		else if (img_active[2] == 8)
			launch_scene_select(world, 8);
		img_active[0] = 0;
		img_active[1] = 0;
		nk_popup_close(ctx);
	}
}

int			launch_xml_file(struct nk_context *ctx, t_world *world, char *xml)
{
	char	*path;

	if (nk_button_label(ctx, "Launch") && world->render_factor == 1)
	{
		path = ft_strjoin("testfiles/", xml);
		if (parser_checker(path))
		{
			clear_world(world);
			parse_rtv1(world, path);
			ft_strdel(&path);
			load_data(world);
			rt(world);
			world->img_scene = 0;
			world->redraw = 3;
			nk_popup_close(ctx);
			return (1);
		}
		else
			ft_putendl("Please, enter a valid xml file. Read dtd/norme.dtd");
		ft_strdel(&path);
		nk_popup_close(ctx);
	}
	return (0);
}
