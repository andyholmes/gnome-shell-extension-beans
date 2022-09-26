// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>

#include "beans-activatable.h"


struct _BeansActivatable
{
  PeasExtensionBase  parent_instance;

  GObject           *object;
};

static void   peas_activatable_iface_init (PeasActivatableInterface *iface);

G_DEFINE_DYNAMIC_TYPE_EXTENDED (BeansActivatable, beans_activatable, PEAS_TYPE_EXTENSION_BASE,
                                0,
                                G_IMPLEMENT_INTERFACE_DYNAMIC (PEAS_TYPE_ACTIVATABLE, peas_activatable_iface_init))

enum {
  PROP_0,
  PROP_OBJECT
};


static void
beans_activatable_activate (PeasActivatable *activatable)
{
  g_message ("%s()", G_STRFUNC);
}

static void
beans_activatable_deactivate (PeasActivatable *activatable)
{
  g_message ("%s()", G_STRFUNC);
}

static void
beans_activatable_update_state (PeasActivatable *activatable)
{
  g_message ("%s()", G_STRFUNC);
}

static void
peas_activatable_iface_init (PeasActivatableInterface *iface)
{
  iface->activate = beans_activatable_activate;
  iface->deactivate = beans_activatable_deactivate;
  iface->update_state = beans_activatable_update_state;
}


static void
beans_activatable_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  BeansActivatable *self = BEANS_ACTIVATABLE (object);

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
beans_activatable_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  BeansActivatable *self = BEANS_ACTIVATABLE (object);

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
beans_activatable_class_finalize (BeansActivatableClass *klass)
{
}

static void
beans_activatable_class_init (BeansActivatableClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = beans_activatable_get_property;
  object_class->set_property = beans_activatable_set_property;

  g_object_class_override_property (object_class, PROP_OBJECT, "object");
}

static void
beans_activatable_init (BeansActivatable *self)
{
}

void
beans_activatable_register_types (PeasObjectModule *module)
{
  beans_activatable_register_type (G_TYPE_MODULE (module));

  peas_object_module_register_extension_type (module,
                                              PEAS_TYPE_ACTIVATABLE,
                                              BEANS_TYPE_ACTIVATABLE);
}

