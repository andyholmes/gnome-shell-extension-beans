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

G_DEFINE_DYNAMIC_TYPE_EXTENDED (BeansActivatablePlugin, beans_activatable_plugin, PEAS_TYPE_EXTENSION_BASE,
                                0,
                                G_IMPLEMENT_INTERFACE_DYNAMIC (PEAS_TYPE_ACTIVATABLE, peas_activatable_iface_init))

enum {
  PROP_0,
  PROP_OBJECT
};


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
      self->object = g_value_get_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
beans_activatable_plugin_class_finalize (BeansActivatablePluginClass *klass)
{
}

static void
beans_activatable_plugin_class_init (BeansActivatablePluginClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = beans_activatable_plugin_get_property;
  object_class->set_property = beans_activatable_plugin_set_property;

  g_object_class_override_property (object_class, PROP_OBJECT, "object");
}

static void
beans_activatable_plugin_init (BeansActivatablePlugin *self)
{
}

void
beans_activatable_plugin_register_types (PeasObjectModule *module)
{
  beans_activatable_plugin_register_type (G_TYPE_MODULE (module));

  peas_object_module_register_extension_type (module,
                                              PEAS_TYPE_ACTIVATABLE,
                                              BEANS_TYPE_ACTIVATABLE_PLUGIN);
}

