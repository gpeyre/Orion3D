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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
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

#ifndef __GTK_FILESEL_H__
#define __GTK_FILESEL_H__


#include <gdk/gdk.h>
#include <gtk/gtkwindow.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_FILE_SELECTION            (gtk_file_selection_get_type ())
#define GTK_FILE_SELECTION(obj)            (GTK_CHECK_CAST ((obj), GTK_TYPE_FILE_SELECTION, GtkFileSelection))
#define GTK_FILE_SELECTION_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), GTK_TYPE_FILE_SELECTION, GtkFileSelectionClass))
#define GTK_IS_FILE_SELECTION(obj)         (GTK_CHECK_TYPE ((obj), GTK_TYPE_FILE_SELECTION))
#define GTK_IS_FILE_SELECTION_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FILE_SELECTION))
#define GTK_FILE_SELECTION_GET_CLASS(obj)  (GTK_CHECK_GET_CLASS ((obj), GTK_TYPE_FILE_SELECTION, GtkFileSelectionClass))


typedef struct _GtkFileSelection       GtkFileSelection;
typedef struct _GtkFileSelectionClass  GtkFileSelectionClass;

struct _GtkFileSelection
{
  GtkWindow window;

  GtkWidget *dir_list;
  GtkWidget *file_list;
  GtkWidget *selection_entry;
  GtkWidget *selection_text;
  GtkWidget *main_vbox;
  GtkWidget *ok_button;
  GtkWidget *cancel_button;
  GtkWidget *help_button;
  GtkWidget *history_pulldown;
  GtkWidget *history_menu;
  GList     *history_list;
  GtkWidget *fileop_dialog;
  GtkWidget *fileop_entry;
  gchar     *fileop_file;
  gpointer   cmpl_state;
  
  GtkWidget *fileop_c_dir;
  GtkWidget *fileop_del_file;
  GtkWidget *fileop_ren_file;
  
  GtkWidget *button_area;
  GtkWidget *action_area;
  
};

struct _GtkFileSelectionClass
{
  GtkWindowClass parent_class;
};


GtkType    gtk_file_selection_get_type            (void);
GtkWidget* gtk_file_selection_new                 (const gchar      *title);
void       gtk_file_selection_set_filename        (GtkFileSelection *filesel,
						   const gchar      *filename);
/* This function returns the selected filename in the C runtime's
 * multibyte string encoding, which may or may not be the same as that
 * used by GDK (UTF-8). To convert to UTF-8, call g_filename_to_utf8().
 * The returned string points to a statically allocated buffer and
 * should be copied away.
 */
gchar*     gtk_file_selection_get_filename        (GtkFileSelection *filesel);

void	   gtk_file_selection_complete		  (GtkFileSelection *filesel,
						   const gchar	    *pattern);
void       gtk_file_selection_show_fileop_buttons (GtkFileSelection *filesel);
void       gtk_file_selection_hide_fileop_buttons (GtkFileSelection *filesel);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_FILESEL_H__ */










