// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>

#include "beans-actions-plugin.h"
#include "beans-activatable-plugin.h"
#include "beans-actor-plugin.h"


G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
  peas_object_module_register_extension_type (module,
                                              G_TYPE_ACTION_GROUP,
                                              BEANS_TYPE_ACTIONS_PLUGIN);

  peas_object_module_register_extension_type (module,
                                              PEAS_TYPE_ACTIVATABLE,
                                              BEANS_TYPE_ACTIVATABLE_PLUGIN);

  peas_object_module_register_extension_type (module,
                                              CLUTTER_TYPE_CONTAINER,
                                              BEANS_TYPE_ACTOR_PLUGIN);
}
