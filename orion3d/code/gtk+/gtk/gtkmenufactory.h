/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-1999.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __GTK_MENU_FACTORY_H__
#define __GTK_MENU_FACTORY_H__


#include <gtk/gtkwidget.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct _GtkMenuEntry	GtkMenuEntry;
typedef struct _GtkMenuPath	GtkMenuPath;
typedef struct _GtkMenuFactory	GtkMenuFactory;

typedef void (*GtkMenuCallback) (GtkWidget *widget,
				 gpointer   user_data);

struct _GtkMenuEntry
{
  gchar *path;
  gchar *accelerator;
  GtkMenuCallback callback;
  gpointer callback_data;
  GtkWidget *widget;
};

struct _GtkMenuPath
{
  char *path;
  GtkWidget *widget;
};

struct _GtkMenuFactory
{
  gchar *path;
  GtkMenuFactoryType type;
  GtkAccelGroup *accel_group;
  GtkWidget *widget;
  GList *subfactories;
};

/* Note: the use of GtkMenuFactory is strongly deprecated.
 * use GtkItemFactory instead (gtkitemfactory.h and gtkitemfactory.c).
 * gtkmenufactory.h and gtkmenufactory.c are sheduled for removal
 * in some future gtk versions.
 */

GtkMenuFactory* gtk_menu_factory_new		   (GtkMenuFactoryType	type);
void		gtk_menu_factory_destroy	   (GtkMenuFactory     *factory);
void		gtk_menu_factory_add_entries	   (GtkMenuFactory     *factory,
						    GtkMenuEntry       *entries,
						    int			nentries);
void		gtk_menu_factory_add_subfactory	   (GtkMenuFactory     *factory,
						    GtkMenuFactory     *subfactory,
						    const char	       *path);
void		gtk_menu_factory_remove_paths	   (GtkMenuFactory     *factory,
						    char	      **paths,
						    int			npaths);
void		gtk_menu_factory_remove_entries	   (GtkMenuFactory     *factory,
						    GtkMenuEntry       *entries,
						    int			nentries);
void		gtk_menu_factory_remove_subfactory (GtkMenuFactory     *factory,
						    GtkMenuFactory     *subfactory,
						    const char	       *path);
GtkMenuPath*	gtk_menu_factory_find		   (GtkMenuFactory     *factory,
						    const char	       *path);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_MENU_FACTORY_H__ */
