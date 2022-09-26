// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>

#include "beans-action-group.h"


struct _BeansActionGroup
{
  GSimpleActionGroup  parent_instance;

  PeasPluginInfo     *plugin_info;
};

G_DEFINE_DYNAMIC_TYPE (BeansActionGroup, beans_action_group, G_TYPE_SIMPLE_ACTION_GROUP)

enum {
  PROP_0,
  PROP_PLUGIN_INFO,
  N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES] = { NULL, };


static void
beans_action_group_test_action (GSimpleAction *action,
                                GVariant      *parameter,
                                gpointer       user_data)
{
  g_message ("%s()", G_STRFUNC);
}

static const GActionEntry actions[] = {
  {"test", beans_action_group_test_action, NULL, NULL, NULL},
};


static void
beans_action_group_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  BeansActionGroup *self = BEANS_ACTION_GROUP (object);

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
beans_action_group_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  BeansActionGroup *self = BEANS_ACTION_GROUP (object);

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
beans_action_group_class_finalize (BeansActionGroupClass *klass)
{
}

static void
beans_action_group_class_init (BeansActionGroupClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = beans_action_group_get_property;
  object_class->set_property = beans_action_group_set_property;

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
beans_action_group_init (BeansActionGroup *self)
{
  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   actions,
                                   G_N_ELEMENTS (actions),
                                   self);
}

void
beans_action_group_register_types (PeasObjectModule *module)
{
  beans_action_group_register_type (G_TYPE_MODULE (module));

  peas_object_module_register_extension_type (module,
                                              G_TYPE_ACTION_GROUP,
                                              BEANS_TYPE_ACTION_GROUP);
}

