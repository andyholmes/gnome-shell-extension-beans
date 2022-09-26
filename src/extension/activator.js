// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

/* exported Activator */

const { GObject, Peas } = imports.gi;


var Activator = GObject.registerClass({
    GTypeName: 'BeansActivator',
}, class Activator extends GObject.Object {
    #engine;
    #engineHandlerIds;
    #activatables;

    constructor(params = {}) {
        super(params);

        this.#engine = Peas.Engine.get_default();
        this.#engineHandlerIds = [];
        this.#activatables = new Map();
    }

    get activatables() {
        return Array.from(this.#activatables.values());
    }

    #onLoadPlugin(engine, pluginInfo) {
        if (!engine.provides_extension(pluginInfo, Peas.Activatable))
            return;

        const plugin = engine.create_extension(pluginInfo, Peas.Activatable,
            ['object'], [this]);

        this.#activatables.set(pluginInfo, plugin);
        plugin.activate();
    }

    #onUnloadPlugin(engine, pluginInfo) {
        if (!engine.provides_extension(pluginInfo, Peas.Activatable))
            return;

        const plugin = this.#activatables.get(pluginInfo);

        plugin.deactivate();
        this.#activatables.delete(pluginInfo);
    }

    enable() {
        this.#engineHandlerIds = [
            this.#engine.connect_after('load-plugin',
                this.#onLoadPlugin.bind(this)),
            this.#engine.connect('unload-plugin',
                this.#onUnloadPlugin.bind(this)),
        ];

        for (const pluginInfo of this.#engine.get_plugin_list())
            this.#onLoadPlugin(this.#engine, pluginInfo);
    }

    disable() {
        for (const handlerId of this.#engineHandlerIds)
            this.#engine.disconnect(handlerId);
        this.#engineHandlerIds = [];

        for (const pluginInfo of this.#activatables.keys())
            this.#onUnloadPlugin(this.#engine, pluginInfo);
        this.#activatables.clear();
    }
});

