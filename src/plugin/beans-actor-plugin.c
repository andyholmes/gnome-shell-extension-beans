// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>
#include <mutter-10/clutter/clutter/clutter.h>

#include "beans-actor-plugin.h"


struct _BeansActorPlugin
{
  ClutterActor    parent_instance;

  PeasPluginInfo *plugin_info;
};

G_DEFINE_DYNAMIC_TYPE (BeansActorPlugin, beans_actor_plugin, CLUTTER_TYPE_ACTOR)

enum {
  PROP_0,
  PROP_PLUGIN_INFO,
  N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES] = { NULL, };


static void
beans_actor_plugin_constructed (GObject *object)
{
  BeansActorPlugin *self = BEANS_ACTOR_PLUGIN (object);

  // HACK: ClutterActor is derived from GInitiallyUnowned (i.e. floating), but
  //       the reference is somehow dropped by the time it's passed to GJS.
  g_object_ref_sink (self);

  G_OBJECT_CLASS (beans_actor_plugin_parent_class)->constructed (object);
}

static void
beans_actor_plugin_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  BeansActorPlugin *self = BEANS_ACTOR_PLUGIN (object);

  switch (prop_id)
    {
    case PROP_PLUGIN_INFO:
      g_value_set_boxed (value, self->plugin_info);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
beans_actor_plugin_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  BeansActorPlugin *self = BEANS_ACTOR_PLUGIN (object);

  switch (prop_id)
    {
    case PROP_PLUGIN_INFO:
      self->plugin_info = g_value_get_boxed (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
beans_actor_plugin_class_init (BeansActorPluginClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->constructed = beans_actor_plugin_constructed;
  object_class->get_property = beans_actor_plugin_get_property;
  object_class->set_property = beans_actor_plugin_set_property;

  properties [PROP_PLUGIN_INFO] =
    g_param_spec_boxed ("plugin-info", NULL, NULL,
                        PEAS_TYPE_PLUGIN_INFO,
                        (G_PARAM_READWRITE |
                         G_PARAM_CONSTRUCT_ONLY |
                         G_PARAM_EXPLICIT_NOTIFY |
                         G_PARAM_STATIC_STRINGS));

  g_object_class_install_properties (object_class, N_PROPERTIES, properties);
}

static void
beans_actor_plugin_class_finalize (BeansActorPluginClass *klass)
{
}

static void
beans_actor_plugin_init (BeansActorPlugin *self)
{
}

void
beans_actor_plugin_register_types (PeasObjectModule *module)
{
  beans_actor_plugin_register_type (G_TYPE_MODULE (module));

  peas_object_module_register_extension_type (module,
                                              CLUTTER_TYPE_CONTAINER,
                                              BEANS_TYPE_ACTOR_PLUGIN);
}

