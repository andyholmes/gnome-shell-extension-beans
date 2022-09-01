// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

/* exported ActorTroupe */

const { Clutter, GObject, Peas } = imports.gi;


var ActorTroupe = GObject.registerClass({
    GTypeName: 'BeansActorTroupe',
}, class ActionMuxer extends GObject.Object {
    #engine;
    #engineHandlerIds;
    #actors;

    constructor(params = {}) {
        super(params);

        this.#engine = Peas.Engine.get_default();
        this.#engineHandlerIds = [];
        this.#actors = new Map();
    }

    get actors() {
        const actors = [];

        for (const actorInfo of this.#actors.values())
            actors.push(actorInfo.actor);

        return actors;
    }

    #onLoadPlugin(engine, pluginInfo) {
        if (!engine.provides_extension(pluginInfo, Clutter.Container))
            return;

        const plugin = engine.create_extension(pluginInfo, Clutter.Container,
            [], []);

        this.#actors.set(pluginInfo, {
            actor: plugin,
            handlerIds: [
                plugin.connect('destroy',
                    this.#onActorDestroy.bind(this)),
            ],
        });
    }

    #onUnloadPlugin(engine, pluginInfo) {
        if (!engine.provides_extension(pluginInfo, Clutter.Container))
            return;

        const { actor, handlerIds } = this.#actors.get(pluginInfo);

        for (const handlerId of handlerIds)
            actor.disconnect(handlerId);

        this.#actors.delete(pluginInfo);
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

        for (const { actor } of this.#actors.values())
            this.#onUnloadPlugin(this.#engine, actor.plugin_info);
        this.#actors.clear();
    }

    #onActorDestroy(actor) {
        this.#actors.delete(actor.plugin_info);
    }
});

