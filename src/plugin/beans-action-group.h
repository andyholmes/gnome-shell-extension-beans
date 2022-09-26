// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <libpeas/peas.h>

G_BEGIN_DECLS

#define BEANS_TYPE_ACTION_GROUP (beans_action_group_get_type ())

G_DECLARE_FINAL_TYPE (BeansActionGroup, beans_action_group, BEANS, ACTION_GROUP, GSimpleActionGroup)

void   beans_action_group_register_types (PeasObjectModule *module);

G_END_DECLS

