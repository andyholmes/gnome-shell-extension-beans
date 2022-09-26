// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>

#include "beans-action-group.h"
#include "beans-activatable.h"
#include "beans-actor.h"


G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
  beans_action_group_register_types (module);
  beans_activatable_register_types (module);
  beans_actor_register_types (module);
}
