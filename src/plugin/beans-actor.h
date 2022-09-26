// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <libpeas/peas.h>
#include <mutter-11/clutter/clutter/clutter.h>

G_BEGIN_DECLS

#define BEANS_TYPE_ACTOR (beans_actor_get_type ())

G_DECLARE_FINAL_TYPE (BeansActor, beans_actor, BEANS, ACTOR, ClutterActor)

void   beans_actor_register_types (PeasObjectModule *module);

G_END_DECLS

