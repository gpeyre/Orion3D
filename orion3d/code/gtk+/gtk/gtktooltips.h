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

#ifndef __GTK_TOOLTIPS_H__
#define __GTK_TOOLTIPS_H__

#include <gdk/gdk.h>
#include <gtk/gtkdata.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_TOOLTIPS                  (gtk_tooltips_get_type ())
#define GTK_TOOLTIPS(obj)                  (GTK_CHECK_CAST ((obj), GTK_TYPE_TOOLTIPS, GtkTooltips))
#define GTK_TOOLTIPS_CLASS(klass)          (GTK_CHECK_CLASS_CAST ((klass), GTK_TYPE_TOOLTIPS, GtkTooltipsClass))
#define GTK_IS_TOOLTIPS(obj)               (GTK_CHECK_TYPE ((obj), GTK_TYPE_TOOLTIPS))
#define GTK_IS_TOOLTIPS_CLASS(klass)       (GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TOOLTIPS))
#define GTK_TOOLTIPS_GET_CLASS(obj)        (GTK_CHECK_GET_CLASS ((obj), GTK_TYPE_TOOLTIPS, GtkTooltipsClass))


typedef struct _GtkTooltips	 GtkTooltips;
typedef struct _GtkTooltipsClass GtkTooltipsClass;
typedef struct _GtkTooltipsData	 GtkTooltipsData;

struct _GtkTooltipsData
{
  GtkTooltips *tooltips;
  GtkWidget *widget;
  gchar *tip_text;
  gchar *tip_private;
  GdkFont *font;
  gint width;
  GList *row;
};

struct _GtkTooltips
{
  GtkData data;

  GtkWidget *tip_window;
  GtkTooltipsData *active_tips_data;
  GList *tips_data_list;

  guint   delay : 30;
  guint	  enabled : 1;
  gint	  timer_tag;
};

struct _GtkTooltipsClass
{
  GtkDataClass parent_class;
};

GtkType		 gtk_tooltips_get_type	   (void);
GtkTooltips*	 gtk_tooltips_new	   (void);

void		 gtk_tooltips_enable	   (GtkTooltips   *tooltips);
void		 gtk_tooltips_disable	   (GtkTooltips   *tooltips);
void		 gtk_tooltips_set_delay	   (GtkTooltips   *tooltips,
					    guint	   delay);
void		 gtk_tooltips_set_tip	   (GtkTooltips   *tooltips,
					    GtkWidget	  *widget,
					    const gchar   *tip_text,
					    const gchar   *tip_private);
void		 gtk_tooltips_set_colors   (GtkTooltips   *tooltips,
					    GdkColor	  *background,
					    GdkColor	  *foreground);
GtkTooltipsData* gtk_tooltips_data_get	   (GtkWidget	  *widget);
void             gtk_tooltips_force_window (GtkTooltips   *tooltips);



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_TOOLTIPS_H__ */
