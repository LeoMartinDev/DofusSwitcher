import * as _ from 'lodash';

const state = {
  characters: JSON.parse(localStorage.getItem('characters')) || [],
};

const mutations = {
  ADD_CHARACTER: (state, payload) => {
    let index = state.characters.findIndex(c => c.name === payload.name);
    if (index < 0) {
      let storage = JSON.parse(localStorage.getItem('characters')) || [];
      storage.push(payload);

      localStorage.setItem('characters', JSON.stringify(storage));
      state.characters.push(payload);
    }
  },
  UPDATE_CHARACTER: (state, payload) => {
    let index = state.characters.findIndex(c => c.name === payload.name);

    if (index > -1) {
      let storage = JSON.parse(localStorage.getItem('characters')) || [];
      let storageIndex = storage.findIndex(c => c.name === payload.name);

      storage[storageIndex] = payload;
      localStorage.setItem('characters', JSON.stringify(storage));
      state.characters.splice(index, 1, payload);
    }
  },
  REMOVE_CHARACTER(state, payload) {
    let index = state.characters.findIndex(c => c.name === payload.name);

    if (index > -1) {
      let storage = JSON.parse(localStorage.getItem('characters')) || [];
      let storageIndex = storage.findIndex(c => c.name === payload.name);

      storage.splice(storageIndex, 1);
      localStorage.setItem('characters', JSON.stringify(storage));
      state.characters.splice(index, 1);
    }
  },
  REMOVE_CHARACTERS(state, payload) {
    localStorage.setItem('characters', JSON.stringify([]));
    state.characters = [];
  },
};

const actions = {
  notifyCharacter({ commit, state, dispatch }, process) {
    let index = state.characters.findIndex(c => c.name === process.mainWindowTitle);

    if (index < 0) {
      commit('ADD_CHARACTER', {
        name: process.mainWindowTitle,
        initiative: 0,
        className: null,
        imagePath: null,
        sexe: null,
        startedAt: new Date(),
        connectedTime: 0, //seconds
        id: process.id,
      });
    } else {
      commit('UPDATE_CHARACTER', { startedAt: new Date(), id: process.id });
    }
  },
  disconnectCharacter({commit, state, dispatch, getters}, process) {
    let character = getters.getCharacterById(process.id);

    if (character) {

      commit('UPDATE_CHARACTER', _.merge({}, character, {
        startedAt: '',
        connectedTime: ((new Date() - character.startedAt) / 1000) + character.connectedTime,
        id: null,
      }));
    }
  },
  addCharacter({commit, state, dispatch}, character) {
    commit('ADD_CHARACTER', character);
  },
  updateCharacter({commit, state, dispatch}, character) {
    commit('UPDATE_CHARACTER', character);
  },
  upsertCharacter({commit, state, dispatch, getters}, character) {
    let index = getters.characters.findIndex(c => c.name === character.name);

    if (index > -1) {
      commit('UPDATE_CHARACTER', character);
    } else {
      commit('ADD_CHARACTER', character);
    }
  },
  removeCharacter({commit, state, dispatch}, character) {
    commit('REMOVE_CHARACTER', character);
  },
  removeCharacters({commit, state, dispatch}) {
    commit('REMOVE_CHARACTERS');
  }
};

const getters = {
  characters: (state, getters) => state.characters,
  getCharacterByName: (state, getters) => name => getters.characters.find(c => c.name === name),
  getCharacterById: (state, getters) => id => getters.characters.find(c => c.id === id),
  editingCharacter: (state, getters) => getters.getCharacterByName(_.get(getters.editingProcess, 'mainWindowTitle')),
  disconnectedCharacters: (state, getters) => getters.characters.filter(c => !getters.processByName(c.name)),
};

export default {
  state,
  mutations,
  getters,
  actions,
};
