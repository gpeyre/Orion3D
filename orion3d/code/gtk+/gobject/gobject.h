/* GObject - GLib Type, Object, Parameter and Signal Library
 * Copyright (C) 1998, 1999, 2000 Tim Janik and Red Hat, Inc.
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
#ifndef __G_OBJECT_H__
#define __G_OBJECT_H__

#include        <gobject/gtype.h>
#include        <gobject/gvalue.h>
#include        <gobject/gparam.h>
#include        <gobject/gclosure.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* --- type macros --- */
#define G_TYPE_IS_OBJECT(type)     (G_TYPE_FUNDAMENTAL (type) == G_TYPE_OBJECT)
#define G_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), G_TYPE_OBJECT, GObject))
#define G_OBJECT_CLASS(class)      (G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_OBJECT, GObjectClass))
#define G_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), G_TYPE_OBJECT))
#define G_IS_OBJECT_CLASS(class)   (G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_OBJECT))
#define G_OBJECT_GET_CLASS(object) (G_TYPE_INSTANCE_GET_CLASS ((object), G_TYPE_OBJECT, GObjectClass))
#define G_OBJECT_TYPE(object)      (G_TYPE_FROM_INSTANCE (object))
#define G_OBJECT_TYPE_NAME(object) (g_type_name (G_OBJECT_TYPE (object)))
#define G_OBJECT_CLASS_TYPE(class) (G_TYPE_FROM_CLASS (class))
#define G_OBJECT_CLASS_NAME(class) (g_type_name (G_OBJECT_CLASS_TYPE (class)))
#define G_IS_VALUE_OBJECT(value)   (G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_OBJECT))


/* --- typedefs & structures --- */
typedef struct _GObject                  GObject;
typedef struct _GObjectClass             GObjectClass;
typedef struct _GObjectConstructParam    GObjectConstructParam;
typedef void (*GObjectGetPropertyFunc)  (GObject      *object,
                                         guint         property_id,
                                         GValue       *value,
                                         GParamSpec   *pspec,
                                         const gchar  *trailer);
typedef void (*GObjectSetPropertyFunc)  (GObject      *object,
                                         guint         property_id,
                                         const GValue *value,
                                         GParamSpec   *pspec,
                                         const gchar  *trailer);
typedef void (*GObjectFinalizeFunc)     (GObject      *object);
struct  _GObject
{
  GTypeInstance g_type_instance;
  
  /*< private >*/
  guint         ref_count;
  GData        *qdata;
};
struct  _GObjectClass
{
  GTypeClass   g_type_class;

  /* private, these fields might vanish */
  guint        n_property_specs;
  GParamSpec **property_specs;
  GSList      *construct_properties;

  /* public overridable methods */
  GObject*   (*constructor)     (GType                  type,
                                 guint                  n_construct_properties,
                                 GObjectConstructParam *construct_properties);
  void       (*set_property)            (GObject        *object,
                                         guint           property_id,
                                         const GValue   *value,
                                         GParamSpec     *pspec,
                                         const gchar    *trailer);
  void       (*get_property)            (GObject        *object,
                                         guint           property_id,
                                         GValue         *value,
                                         GParamSpec     *pspec,
                                         const gchar    *trailer);
  void       (*shutdown)                (GObject        *object);
  void       (*finalize)                (GObject        *object);

  /*< private >*/
  void       (*dispatch_properties_changed) (GObject      *object,
					     guint	   n_pspecs,
					     GParamSpec  **pspecs);

  /* signals */
  void	     (*properties_changed)	(GObject	*object,
					 guint		 n_pspecs,
					 GParamSpec    **pspecs);
  void	     (*notify)			(GObject	*object,
					 GParamSpec	*pspec);
};
struct _GObjectConstructParam
{
  GParamSpec  *pspec;
  GValue      *value;
  const gchar *trailer;
};


/* --- prototypes --- */
void        g_object_class_install_property   (GObjectClass   *oclass,
					       guint           property_id,
					       GParamSpec     *pspec);
GParamSpec* g_object_class_find_property      (GObjectClass   *oclass,
					       const gchar    *property_name);
gpointer    g_object_new                      (GType           object_type,
					       const gchar    *first_property_name,
					       ...);
gpointer    g_object_new_valist               (GType           object_type,
					       const gchar    *first_property_name,
					       va_list         var_args);
void        g_object_set                      (gpointer	       object,
					       const gchar    *first_property_name,
					       ...);
void        g_object_get                      (gpointer        object,
					       const gchar    *first_property_name,
					       ...);
void        g_object_set_valist               (GObject        *object,
					       const gchar    *first_property_name,
					       va_list         var_args);
void        g_object_get_valist               (GObject        *object,
					       const gchar    *first_property_name,
					       va_list         var_args);
void        g_object_set_property             (GObject        *object,
					       const gchar    *property_name,
					       const GValue   *value);
void        g_object_get_property             (GObject        *object,
					       const gchar    *property_name,
					       GValue         *value);
void        g_object_freeze_notify            (GObject        *object);
void        g_object_notify                   (GObject        *object,
					       const gchar    *property_name);
void        g_object_thaw_notify              (GObject        *object);
gpointer    g_object_ref                      (gpointer        object);
void        g_object_unref                    (gpointer        object);
gpointer    g_object_get_qdata                (GObject        *object,
					       GQuark          quark);
void        g_object_set_qdata                (GObject        *object,
					       GQuark          quark,
					       gpointer        data);
void        g_object_set_qdata_full           (GObject        *object,
					       GQuark          quark,
					       gpointer        data,
					       GDestroyNotify  destroy);
gpointer    g_object_steal_qdata              (GObject        *object,
					       GQuark          quark);
gpointer    g_object_get_data                 (GObject        *object,
					       const gchar    *key);
void        g_object_set_data                 (GObject        *object,
					       const gchar    *key,
					       gpointer        data);
void        g_object_set_data_full            (GObject        *object,
					       const gchar    *key,
					       gpointer        data,
					       GDestroyNotify  destroy);
gpointer    g_object_steal_data               (GObject        *object,
					       const gchar    *key);
void        g_object_watch_closure            (GObject        *object,
					       GClosure       *closure);
GClosure*   g_cclosure_new_object             (GCallback       callback_func,
					       gpointer        object);
GClosure*   g_cclosure_new_object_swap        (GCallback       callback_func,
					       gpointer        object);
GClosure*   g_closure_new_object              (guint           sizeof_closure,
					       GObject        *object);
void        g_value_set_object                (GValue         *value,
					       GObject        *v_object);
GObject*    g_value_get_object                (const GValue   *value);
GObject*    g_value_dup_object                (const GValue   *value);
guint	    g_signal_connect_object           (gpointer	       instance,
					       const gchar    *detailed_signal,
					       GCallback       c_handler,
					       gpointer	       gobject,
					       gboolean        swapped,
					       gboolean        after);


/* --- implementation macros --- */
#define G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec) \
G_STMT_START { \
  GObject *_object = (GObject*) (object); \
  GParamSpec *_pspec = (GParamSpec*) (pspec); \
  guint _property_id = (property_id); \
  g_warning ("%s: invalid property id %u for \"%s\" of type `%s' in `%s'", \
             G_STRLOC, \
             _property_id, \
             _pspec->name, \
             g_type_name (G_PARAM_SPEC_TYPE (_pspec)), \
             G_OBJECT_TYPE_NAME (_object)); \
} G_STMT_END



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __G_OBJECT_H__ */
