# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>


pkgconfig = import('pkgconfig')

plugins_deps = [
  dependency('gio-2.0', version: '>= 2.66.0'),
  dependency('libpeas-1.0', version: '>= 1.22.0'),
  dependency('mutter-clutter-10', version: '>= 42.0'),
]

plugins_c_args = [
  '-Wno-missing-field-initializers',
  '-Wno-unused-parameter',
]
plugins_link_args = []


plugin_sources = files([
  'example-plugin.c',
  'beans-action-group.c',
  'beans-activatable.c',
  'beans-actor.c',
])

plugin_info = configure_file(
   input: 'example.plugin',
  output: 'example.plugin',
    copy: true,
)

plugin_library = shared_library('example',
                                plugin_sources,
         dependencies: plugins_deps,
               c_args: plugins_c_args,
            link_args: plugins_link_args,
  include_directories: [include_directories('.')],
)

