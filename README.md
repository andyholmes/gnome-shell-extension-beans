[![CD](https://github.com/andyholmes/gnome-shell-extension-beans/actions/workflows/cd.yml/badge.svg)](https://github.com/andyholmes/gnome-shell-extension-beans/actions/workflows/cd.yml)

# Beans (GNOME Shell Extension)

Beans is a proof of concept, demonstrating the use of libpeas to load C plugins
within a GNOME Shell extension.

In practical terms this not a great idea, but might be good for educational
purposes or a few laughs.


## Extension

Building the GNOME Shell extension requires `meson` and `zip`. The helper script
`build-aux/misc/ego.sh` will build an extension ZIP that can be installed with
`gnome-extensions`:

```sh
./build-aux/misc/ego.sh
gnome-extensions install --force beans@andyholmes.ca.zip
```


## Example Plugin

Beans includes an example plugin with three extensions:

* `BeansActionsPlugin`: A `Gio.SimpleActionGroup` subclass
* `BeansActivatablePlugin`: An implementation of `Peas.Activatable`
* `BeansActorPlugin`: A `Clutter.Actor` subclass

Building the example plugin requires the development headers for Peas, GIO and
Mutter (e.g. `libpeas-devel`, `glib2-devel` and `mutter-devel` on Fedora):

```sh
meson -Dexample=true _build
meson compile -C _build
```

Beans is hardcoded to load plugins from `XDG_DATA_HOME/beans/plugins`. Once
compiled, you can copy the example plugin there before enabling the extension:

```sh
mkdir -p ~/.local/share/beans/plugins
cp _build/src/plugin/{libexample.so,example.plugin} ~/.local/share/beans/plugins
```

