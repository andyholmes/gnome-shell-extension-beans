// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>

#include "beans-activatable-plugin.h"


struct _BeansActivatablePlugin
{
  PeasExtensionBase  parent_instance;

  GObject           *object;
};

static void   peas_activatable_iface_init (PeasActivatableInterface *iface);

G_DEFINE_TYPE_WITH_CODE (BeansActivatablePlugin, beans_activatable_plugin, PEAS_TYPE_EXTENSION_BASE,
                         G_IMPLEMENT_INTERFACE (PEAS_TYPE_ACTIVATABLE, peas_activatable_iface_init))

enum {
  PROP_0,
  PROP_OBJECT,
  N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES] = { NULL, };


static void
beans_activatable_plugin_activate (PeasActivatable *activatable)
{
  g_message ("%s()", G_STRFUNC);
}

static void
beans_activatable_plugin_deactivate (PeasActivatable *activatable)
{
  g_message ("%s()", G_STRFUNC);
}

static void
beans_activatable_plugin_update_state (PeasActivatable *activatable)
{
  g_message ("%s()", G_STRFUNC);
}

static void
peas_activatable_iface_init (PeasActivatableInterface *iface)
{
  iface->activate = beans_activatable_plugin_activate;
  iface->deactivate = beans_activatable_plugin_deactivate;
  iface->update_state = beans_activatable_plugin_update_state;
}


static void
beans_activatable_plugin_dispose (GObject *object)
{
  BeansActivatablePlugin *self = BEANS_ACTIVATABLE_PLUGIN (object);

  g_clear_object (&self->object);

  G_OBJECT_CLASS (beans_activatable_plugin_parent_class)->dispose (object);
}

static void
beans_activatable_plugin_get_property (GObject    *object,
                                       guint       prop_id,
                                       GValue     *value,
                                       GParamSpec *pspec)
{
  BeansActivatablePlugin *self = BEANS_ACTIVATABLE_PLUGIN (object);

  switch (prop_id)
    {
    case PROP_OBJECT:
      g_value_set_object (value, self->object);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
beans_activatable_plugin_set_property (GObject      *object,
                                       guint         prop_id,
                                       const GValue *value,
                                       GParamSpec   *pspec)
{
  BeansActivatablePlugin *self = BEANS_ACTIVATABLE_PLUGIN (object);

  switch (prop_id)
    {
    case PROP_OBJECT:
      self->object = g_value_dup_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
beans_activatable_plugin_class_init (BeansActivatablePluginClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->dispose = beans_activatable_plugin_dispose;
  object_class->get_property = beans_activatable_plugin_get_property;
  object_class->set_property = beans_activatable_plugin_set_property;

  properties [PROP_OBJECT] =
    g_param_spec_object ("object", NULL, NULL,
                         G_TYPE_OBJECT,
                         (G_PARAM_READWRITE |
                          G_PARAM_CONSTRUCT_ONLY |
                          G_PARAM_EXPLICIT_NOTIFY |
                          G_PARAM_STATIC_STRINGS));

  g_object_class_install_properties (object_class, N_PROPERTIES, properties);
}

static void
beans_activatable_plugin_init (BeansActivatablePlugin *self)
{
}

