// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <libpeas/peas.h>
#include <mutter-10/clutter/clutter/clutter.h>

G_BEGIN_DECLS

#define BEANS_TYPE_ACTOR_PLUGIN (beans_actor_plugin_get_type ())

G_DECLARE_FINAL_TYPE (BeansActorPlugin, beans_actor_plugin, BEANS, ACTOR_PLUGIN, ClutterActor)

G_END_DECLS

