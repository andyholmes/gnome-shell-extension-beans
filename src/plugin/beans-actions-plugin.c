// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>

#include "beans-actions-plugin.h"


struct _BeansActionsPlugin
{
  GSimpleActionGroup  parent_instance;

  PeasPluginInfo     *plugin_info;
};

G_DEFINE_TYPE (BeansActionsPlugin, beans_actions_plugin, G_TYPE_SIMPLE_ACTION_GROUP)

enum {
  PROP_0,
  PROP_PLUGIN_INFO,
  N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES] = { NULL, };


static void
beans_actions_plugin_test_action (GSimpleAction *action,
                                  GVariant      *parameter,
                                  gpointer       user_data)
{
  g_message ("%s()", G_STRFUNC);
}

static const GActionEntry actions[] = {
  {"test", beans_actions_plugin_test_action, NULL, NULL, NULL},
};


static void
beans_actions_plugin_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  BeansActionsPlugin *self = BEANS_ACTIONS_PLUGIN (object);

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
beans_actions_plugin_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  BeansActionsPlugin *self = BEANS_ACTIONS_PLUGIN (object);

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
beans_actions_plugin_class_init (BeansActionsPluginClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = beans_actions_plugin_get_property;
  object_class->set_property = beans_actions_plugin_set_property;

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
beans_actions_plugin_init (BeansActionsPlugin *self)
{
  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   actions,
                                   G_N_ELEMENTS (actions),
                                   self);
}

