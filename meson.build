# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

project('beans', 'c',
          license: 'GPL-3.0-or-later',
          version: '1.alpha',
    meson_version: '>= 0.59.0',
  default_options: [
    'buildtype=debugoptimized',
    'warning_level=2',
    'werror=true',
  ],
)

#
#
#
extname = 'Beans'
extuuid = 'beans@andyholmes.ca'


#
# Paths
#
prefix = get_option('prefix')
datadir = join_paths(prefix, get_option('datadir'))
libdir = join_paths(prefix, get_option('libdir'))
localedir = join_paths(prefix, get_option('localedir'))

extensionsdir = join_paths(datadir, 'gnome-shell', 'extensions')
pluginsdir = join_paths(libdir, meson.project_name(), 'plugins')


#
# Build
#
subdir('src')


#
# Build Summary
#
summary({
  'Example Plugin': get_option('example'),
  'Tests':          get_option('tests'),
}, section: 'Build')
