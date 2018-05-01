#ifndef __G_MARSHAL_H__
#define __G_MARSHAL_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* VOID:VOID (./gmarshal.list:25) */
extern void g_cclosure_marshal_VOID__VOID (GClosure     *closure,
                                           GValue       *return_value,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint,
                                           gpointer      marshal_data);

/* VOID:UINT,POINTER (./gmarshal.list:26) */
extern void g_cclosure_marshal_VOID__UINT_POINTER (GClosure     *closure,
                                                   GValue       *return_value,
                                                   guint         n_param_values,
                                                   const GValue *param_values,
                                                   gpointer      invocation_hint,
                                                   gpointer      marshal_data);

/* VOID:PARAM (./gmarshal.list:27) */
extern void g_cclosure_marshal_VOID__POINTER (GClosure     *closure,
                                              GValue       *return_value,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint,
                                              gpointer      marshal_data);
#define g_cclosure_marshal_VOID__PARAM	g_cclosure_marshal_VOID__POINTER

/* VOID:INT (./gmarshal.list:28) */
extern void g_cclosure_marshal_VOID__INT (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);

/* VOID:OBJECT (./gmarshal.list:29) */
#define g_cclosure_marshal_VOID__OBJECT	g_cclosure_marshal_VOID__POINTER

/* VOID:POINTER (./gmarshal.list:30) */

/* VOID:STRING (./gmarshal.list:31) */
#define g_cclosure_marshal_VOID__STRING	g_cclosure_marshal_VOID__POINTER

/* VOID:UINT (./gmarshal.list:32) */
extern void g_cclosure_marshal_VOID__UINT (GClosure     *closure,
                                           GValue       *return_value,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint,
                                           gpointer      marshal_data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __G_MARSHAL_H__ */
