// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

/* exported init */

const { GLib, Peas } = imports.gi;

const ExtensionUtils = imports.misc.extensionUtils;
const ExtensionMeta = ExtensionUtils.getCurrentExtension();

const { ActionMuxer } = ExtensionMeta.imports.actionMuxer;
const { Activator } = ExtensionMeta.imports.activator;
const { ActorTroupe } = ExtensionMeta.imports.actorTroupe;


class Extension {
    #engine;
    #actionMuxer;
    #activator;
    #actorTroupe;

    constructor() {
        const pluginsDir = GLib.build_filenamev([GLib.get_user_data_dir(),
            'beans', 'plugins']);

        this.#engine = Peas.Engine.get_default();
        this.#engine.prepend_search_path(pluginsDir, null);
    }

    enable() {
        for (let pluginInfo of this.#engine.get_plugin_list())
            this.#engine.load_plugin(pluginInfo);

        this.#actionMuxer = new ActionMuxer();
        this.#actionMuxer.enable();

        this.#activator = new Activator();
        this.#activator.enable();

        this.#actorTroupe = new ActorTroupe();
        this.#actorTroupe.enable();
    }

    disable() {
        this.#actionMuxer.disable();
        this.#actionMuxer = null;

        this.#activator.disable();
        this.#activator = null;

        this.#actorTroupe.disable();
        this.#actorTroupe = null;

        for (let pluginInfo of this.#engine.get_plugin_list())
            this.#engine.unload_plugin(pluginInfo);
    }
}


/** */
function init() {
    return new Extension();
}

