# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: No rights reserved

FROM registry.fedoraproject.org/fedora:36

# The packages below only include build tooling; the CI handles testing itself
RUN dnf install -y --setopt=install_weak_deps=False \
        git meson zip \
        gcc glib2-devel libpeas-devel mutter-devel && \
    dnf clean all && rm -rf /var/cache/dnf

