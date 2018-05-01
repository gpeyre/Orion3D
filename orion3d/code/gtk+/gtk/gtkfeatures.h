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
#ifndef __GTK_FEATURES_H__
#define __GTK_FEATURES_H__


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* compile time version
 */
#define GTK_MAJOR_VERSION				(1)
#define GTK_MINOR_VERSION				(3)
#define GTK_MICRO_VERSION				(0)
#define GTK_BINARY_AGE					(0)
#define GTK_INTERFACE_AGE				(0)
#define	GTK_CHECK_VERSION(major,minor,micro)	\
    (GTK_MAJOR_VERSION > (major) || \
     (GTK_MAJOR_VERSION == (major) && GTK_MINOR_VERSION > (minor)) || \
     (GTK_MAJOR_VERSION == (major) && GTK_MINOR_VERSION == (minor) && \
      GTK_MICRO_VERSION >= (micro)))


/* new gtk_container_set_focus_[hv]adjustment()
 */
#define GTK_HAVE_CONTAINER_FOCUS_ADJUSTMENTS		1-0-1

/* newly exported gtk_signal_init()
 * new gtk_signal_n_emissions*()
 * "signal-name" is now an alias for "signal_name"
 * new gtk_signal_emitv*()
 */
#define GTK_HAVE_SIGNAL_INIT				1-0-2
  
/* Gtk+ 1.1.0 version tag.
 * - new gtk_rc_set_image_loader () to install custom image loaders for rc
 *   files.
 * - GtkAccel groups replaced GtkAcceleratorTables
 * - Gdk supports full crossing event now.
 * - Buttons featur relief styles now.
 * - gdk_rgb_*() functions are in place.
 * - stringified enum values can be queried for enum types now.
 * - new key binding system is in place (GtkBindingSet).
 * - simple algorithm for pattern matching is exported now (GtkPatternSpec).
 */
#define GTK_HAVE_FEATURES_1_1_0				1-1-0

/* Gtk+ 1.1.2 version tag
 * - ctree function name changes
 */
#define GTK_HAVE_FEATURES_1_1_2				1-1-2

/* Gtk+ 1.1.4 version tag
 * - clist v/hscrollbar -> v/hadjustment changes
 */
#define GTK_HAVE_FEATURES_1_1_4				1-1-4

/* Gtk+ 1.1.5 version tag
 */
#define GTK_HAVE_FEATURES_1_1_5				1-1-5

/* Gtk+ 1.1.6 version tag
 */
#define GTK_HAVE_FEATURES_1_1_6				1-1-6

/* Gtk+ 1.1.7 version tag
 */
#define GTK_HAVE_FEATURES_1_1_7				1-1-7

/* Gtk+ 1.1.8 version tag
 */
#define GTK_HAVE_FEATURES_1_1_8				1-1-8

/* Gtk+ 1.1.9 version tag
 */
#define GTK_HAVE_FEATURES_1_1_9				1-1-9

/* Gtk+ 1.1.10 version tag
 */
#define GTK_HAVE_FEATURES_1_1_10			1-1-10

/* Gtk+ 1.1.11 version tag
 */
#define GTK_HAVE_FEATURES_1_1_11			1-1-11

/* Gtk+ 1.1.12 version tag
 */
#define GTK_HAVE_FEATURES_1_1_12			1-1-12

/* Gtk+ 1.1.13 version tag
 * gtk_toggle_button_set_state name changes
 */
#define GTK_HAVE_FEATURES_1_1_13			1-1-13

/* Gtk+ 1.1.14 version tag
 * working gtk layout, etc
 */
#define GTK_HAVE_FEATURES_1_1_14			1-1-14

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_FEATURES_H__ */
