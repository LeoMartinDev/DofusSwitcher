export const DIALOG = {
  TERMINATE_ALL: 'terminateAll',
  REPAIR: 'repair',
  PROCESS_SETTINGS: 'processSettings',
};

const state = {
  dialogs: {
    [DIALOG.TERMINATE_ALL]: false,
    [DIALOG.REPAIR]: false,
    [DIALOG.PROCESS_SETTINGS]: false,
  },
};

const mutations = {
  UPDATE_DIALOG(state, { dialog, value }) {
    if (state.dialogs[dialog] !== null) {
      state.dialogs[dialog] = value;
    }
  },
};

const actions = {
  updateDialog({ commit, state }, payload) {
    commit('UPDATE_DIALOG', payload);
  },
  toggleDialog({ commit, state }, payload) {
    if (state.dialogs[payload] !== null) {
      commit('UPDATE_DIALOG', { dialog: payload, value: !state.dialogs[payload] });
    }
  },
};

const getters = {
  dialogs: (state, getters) => state.dialogs,
};

export default {
  state,
  mutations,
  getters,
  actions,
};
