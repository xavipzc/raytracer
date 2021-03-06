/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 17:29:28 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/03 13:57:52 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
**	Find objects and execute their own parsing associate
*/

static void		get_object_node_next(t_world *world, xmlNodePtr obj)
{
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"paraboloid")))
		parse_paraboloid(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"hyperboloid")))
		parse_hyperboloid(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"torus")))
		parse_torus(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"triangle")))
		parse_triangle(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"cube")))
		parse_cube(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"h_cube")))
		parse_h_cube(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"ambient")))
		parse_ambient(world, obj);
}

static void		get_object_node(t_world *world, xmlNodePtr obj)
{
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"camera")))
		parse_camera(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"light")))
		parse_light(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"plane")))
		parse_plane(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"sphere")))
		parse_sphere(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"mobius")))
		parse_mobius(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"cylinder")))
		parse_cylinder(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"disk")))
		parse_disk(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"cone")))
		parse_cone(world, obj);
	get_object_node_next(world, obj);
}

/*
**	Initialize the title of the scene
**  Parse all the objects inside the scene
*/

static void		parse_file(t_world *world, const char *docname)
{
	xmlDocPtr	doc;
	xmlNodePtr	cur;
	xmlChar		*title;

	if (!(doc = xmlParseFile(docname)))
		show_error("xml file not parsed successfully");
	if (!(cur = xmlDocGetRootElement(doc)))
	{
		xmlFreeDoc(doc);
		show_error("empty file");
	}
	title = xmlGetProp(cur, (const xmlChar *)"name");
	world->title = ft_strjoin("Title : ", (char*)title);
	xmlFree(title);
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if (xmlStrcmp(cur->name, (const xmlChar *)"text"))
			get_object_node(world, cur);
		cur = cur->next;
	}
	xmlFreeDoc(doc);
}

/*
**	Parser that use libxml2 to well parse the xml file
**  who describe the scene. If it's not valid it quit properly
*/

void			parse_rtv1(t_world *world, char *argv)
{
	if (parser_checker(argv))
		parse_file(world, argv);
	else
		ft_putendl("Please, give me a valid xml file. Read the dtd/norme.dtd");
}
