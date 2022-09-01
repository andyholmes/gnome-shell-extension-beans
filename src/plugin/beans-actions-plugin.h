// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <libpeas/peas.h>

G_BEGIN_DECLS

#define BEANS_TYPE_ACTIONS_PLUGIN (beans_actions_plugin_get_type ())

G_DECLARE_FINAL_TYPE (BeansActionsPlugin, beans_actions_plugin, BEANS, ACTIONS_PLUGIN, GSimpleActionGroup)

G_END_DECLS

