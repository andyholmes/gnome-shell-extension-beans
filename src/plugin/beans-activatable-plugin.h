// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <libpeas/peas.h>

G_BEGIN_DECLS

#define BEANS_TYPE_ACTIVATABLE_PLUGIN (beans_activatable_plugin_get_type ())

G_DECLARE_FINAL_TYPE (BeansActivatablePlugin, beans_activatable_plugin, BEANS, ACTIVATABLE_PLUGIN, PeasExtensionBase)

G_END_DECLS

