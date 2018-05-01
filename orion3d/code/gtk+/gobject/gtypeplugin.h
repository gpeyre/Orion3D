/* GObject - GLib Type, Object, Parameter and Signal Library
 * Copyright (C) 2000 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef __G_TYPE_PLUGIN_H__
#define __G_TYPE_PLUGIN_H__


#include	<gobject/gtype.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/* --- type macros --- */
#define G_TYPE_TYPE_PLUGIN		(g_type_plugin_get_type ())
#define G_TYPE_PLUGIN(inst)		(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TYPE_PLUGIN, GTypePlugin))
#define G_TYPE_PLUGIN_CLASS(vtable)	(G_TYPE_CHECK_CLASS_CAST ((vtable), G_TYPE_TYPE_PLUGIN, GTypePluginClass))
#define G_IS_TYPE_PLUGIN(inst)		(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TYPE_PLUGIN))
#define G_IS_TYPE_PLUGIN_CLASS(vtable)	(G_TYPE_CHECK_CLASS_TYPE ((vtable), G_TYPE_TYPE_PLUGIN))
#define G_TYPE_PLUGIN_GET_CLASS(inst)	(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_TYPE_PLUGIN, GTypePluginClass))


/* --- typedefs & structures --- */
typedef struct _GTypePluginClass		   GTypePluginClass;
typedef void  (*GTypePluginUse)			  (GTypePlugin     *plugin);
typedef void  (*GTypePluginUnuse)		  (GTypePlugin     *plugin);
typedef void  (*GTypePluginCompleteTypeInfo)	  (GTypePlugin     *plugin,
						   GType            g_type,
						   GTypeInfo       *info,
						   GTypeValueTable *value_table);
typedef void  (*GTypePluginCompleteInterfaceInfo) (GTypePlugin     *plugin,
						   GType            interface_type,
						   GType            instance_type,
						   GInterfaceInfo  *info);
struct _GTypePluginClass
{
  GTypeInterface		   base_iface;
  
  GTypePluginUse		   use_plugin;
  GTypePluginUnuse		   unuse_plugin;
  GTypePluginCompleteTypeInfo	   complete_type_info;
  GTypePluginCompleteInterfaceInfo complete_interface_info;
};


/* --- prototypes --- */
GType	g_type_plugin_get_type			(void)	G_GNUC_CONST;
void	g_type_plugin_use			(GTypePlugin	 *plugin);
void	g_type_plugin_unuse			(GTypePlugin	 *plugin);
void	g_type_plugin_complete_type_info	(GTypePlugin     *plugin,
						 GType            g_type,
						 GTypeInfo       *info,
						 GTypeValueTable *value_table);
void	g_type_plugin_complete_interface_info	(GTypePlugin     *plugin,
						 GType            interface_type,
						 GType            instance_type,
						 GInterfaceInfo  *info);





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __G_TYPE_PLUGIN_H__ */
