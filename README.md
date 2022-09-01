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

There are also nightly builds available for [download][nightly-build].

[nightly-build]:  https://nightly.link/andyholmes/gnome-shell-extension-beans/workflows/cd/main/nightly-build.zip


## Example Plugin

Beans includes an example plugin with three extensions:

* `BeansActionsPlugin`: A `Gio.SimpleActionGroup` subclass

    Beans is setup to load `Gio.ActionGroup` implementations and aggregate them
    with a simple `Gio.ActionGroup` muxer, [`actionMuxer.js`][action-muxer].
    
* `BeansActivatablePlugin`: An implementation of `Peas.Activatable`

    Beans will load each extension implementing `Peas.Activatable` into
    [`activator.js`][activator]. It will call `Peas.Activatable.activate()` when
    the GNOME Shell extension is enabled, and `Peas.Activatable.deactivate()`
    when it is disabled.
    
* `BeansActorPlugin`: A `Clutter.Actor` subclass

    Beans will load each extension implementing `Clutter.Container` into
    [`actorTroupe.js`][actor-troupe]. It creates an instance of the actor and
    watch for the `destroy` signal.

[action-muxer]: https://github.com/andyholmes/gnome-shell-extension-beans/blob/main/src/extension/actionMuxer.js
[activator]: https://github.com/andyholmes/gnome-shell-extension-beans/blob/main/src/extension/activator.js
[actor-troupe]: https://github.com/andyholmes/gnome-shell-extension-beans/blob/main/src/extension/actorTroupe.js


### Compiling

Building the example plugin requires the development headers for Peas, GLib and
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

There are also nightly builds available for [download][example-plugin].

[example-plugin]: https://nightly.link/andyholmes/gnome-shell-extension-beans/workflows/cd/main/example-plugin.zip

