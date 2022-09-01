// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

/* exported ActionMuxer */

const { GObject, Gio, Peas } = imports.gi;


var ActionMuxer = GObject.registerClass({
    GTypeName: 'BeansActionMuxer',
    Implements: [Gio.ActionGroup],
}, class ActionMuxer extends GObject.Object {
    #engine;
    #engineHandlerIds;
    #actionGroups;

    constructor(params = {}) {
        super(params);

        this.#engine = Peas.Engine.get_default();
        this.#engineHandlerIds = [];
        this.#actionGroups = new Map();
    }

    #onLoadPlugin(engine, pluginInfo) {
        if (!engine.provides_extension(pluginInfo, Gio.ActionGroup))
            return;

        const plugin = engine.create_extension(pluginInfo, Gio.ActionGroup,
            [], []);

        this.#actionGroups.set(pluginInfo.get_module_name(), {
            actionGroup: plugin,
            handlerIds: [
                plugin.connect('action-added',
                    this.#onActionAdded.bind(this)),
                plugin.connect('action-removed',
                    this.#onActionRemoved.bind(this)),
                plugin.connect('action-enabled-changed',
                    this.#onActionEnabledChanged.bind(this)),
                plugin.connect('action-state-changed',
                    this.#onActionStateChanged.bind(this)),
            ],
        });

        for (const name of plugin.list_actions())
            this.#onActionAdded(plugin, name);
    }

    #onUnloadPlugin(engine, pluginInfo) {
        if (!engine.provides_extension(pluginInfo, Gio.ActionGroup))
            return;

        const moduleName = pluginInfo.get_module_name();
        const { actionGroup, handlerIds } = this.#actionGroups.get(moduleName);

        for (const handlerId of handlerIds)
            actionGroup.disconnect(handlerId);

        for (const name of actionGroup.list_actions())
            this.#onActionRemoved(actionGroup, name);

        this.#actionGroups.delete(moduleName);
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

        for (const { actionGroup } of this.#actionGroups.values())
            this.#onUnloadPlugin(this.#engine, actionGroup.plugin_info);
        this.#actionGroups.clear();
    }

    /* Signal Relays */
    #onActionAdded(group, name) {
        const actionName = `${group.plugin_info.get_module_name()}.${name}`;
        this.action_added(actionName);
    }

    #onActionRemoved(group, name) {
        const actionName = `${group.plugin_info.get_module_name()}.${name}`;
        this.action_removed(actionName);
    }

    #onActionEnabledChanged(group, name, enabled) {
        const actionName = `${group.plugin_info.get_module_name()}.${name}`;
        this.action_enabled_changed(actionName, enabled);
    }

    #onActionStateChanged(group, name, value) {
        const actionName = `${group.plugin_info.get_module_name()}.${name}`;
        this.action_state_changed(actionName, value);
    }

    /* Gio.ActionGroup */
    _findGroup(action) {
        try {
            const [prefix, name] = action.split('.');
            const { actionGroup } = this.#actionGroups.get(prefix);

            if (actionGroup.has_action(name))
                return [actionGroup, name];

            return [actionGroup, null];
        } catch {
            return [null, null];
        }
    }

    vfunc_has_action(action) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            return actionGroup.has_action(name);

        return false;
    }

    vfunc_list_actions() {
        const actions = [];

        for (const [prefix, groupInfo] of this.#actionGroups) {
            for (const name of groupInfo.actionGroup.list_actions())
                actions.push(`${prefix}.${name}`);
        }

        return actions;
    }

    vfunc_get_action_enabled(action) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            return actionGroup.get_action_enabled(name);

        return false;
    }

    vfunc_get_action_parameter_type(action) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            return actionGroup.get_action_parameter_type(name);

        return null;
    }

    vfunc_get_action_state_type(action) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            return actionGroup.get_action_state_type(name);

        return null;
    }

    vfunc_get_action_state_hint(action) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            return actionGroup.get_action_state_hint(name);

        return null;
    }

    vfunc_get_action_state(action) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            return actionGroup.get_action_state(name);

        return null;
    }

    vfunc_change_action_state(action, value) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            actionGroup.change_action_state(name, value);
    }

    vfunc_activate_action(action, target) {
        const [actionGroup, name] = this._findGroup(action);

        if (actionGroup && name)
            actionGroup.activate_action(name, target);
    }
});

