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
  beans_actions_plugin_register_types (module);
  beans_activatable_plugin_register_types (module);
  beans_actor_plugin_register_types (module);
}
