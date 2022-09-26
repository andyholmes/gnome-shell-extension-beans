// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <libpeas/peas.h>

G_BEGIN_DECLS

#define BEANS_TYPE_ACTIVATABLE (beans_activatable_get_type ())

G_DECLARE_FINAL_TYPE (BeansActivatable, beans_activatable, BEANS, ACTIVATABLE, PeasExtensionBase)

void   beans_activatable_register_types (PeasObjectModule *module);

G_END_DECLS

