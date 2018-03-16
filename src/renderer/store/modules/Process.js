import {DIALOG} from "./UI";

const state = {
  processes: [],
  focusedProcessId: null,
  editingProcessId: null,
};

const mutations = {
  ADD_PROCESS(state, payload) {
    if (state.processes.findIndex(p => p.id === payload.id) < 0) {
      state.processes.push(payload);
    }
  },
  REMOVE_PROCESS(state, payload) {
    let index = state.processes.findIndex(p => p.id === payload.id);

    if (index > -1) {
      if (payload.id === state.editingProcessId) {
        state.editingProcessId = null;
      }
      if (payload === state.focusedProcessId) {
        state.focusedProcessId = null;
      }
      state.processes.splice(index, 1);
    }
  },
  UPDATE_PROCESSES(state, payload) {
    state.processes = payload;
  },
  UPDATE_FOCUSED_PROCESS(state, payload) {
    if (payload && payload.id) {
      state.focusedProcessId = payload.id;
    }
  },
  UPDATE_EDITING_PROCESS(state, payload) {
    if (payload && payload.id) {
      state.editingProcessId = payload.id;
    }
  },
  REMOVE_PROCESSES(state) {
    state.processes.splice(0, state.processes.length);
  }
};

const actions = {
  updateFocusedProcess({commit, state}, processId) {
    commit('UPDATE_FOCUSED_PROCESS', processId);
  },
  removeProcesses({commit, state}) {
    /*state.teams.forEach(team => commit('REMOVE_PROCESSES_FROM_TEAM', team.id));*/
    commit('REMOVE_PROCESSES');
  },
  updateProcesses({commit, state}, processes) {
    commit('UPDATE_PROCESSES', processes);
  },
  addProcess({commit, state, dispatch}, process) {
    commit('ADD_PROCESS', process);
    dispatch('notifyCharacter', process);
  },
  editProcess({commit, state, dispatch}, process) {
    commit('UPDATE_EDITING_PROCESS', process);
    if (state.editingProcessId !== null) {
      dispatch('toggleDialog', DIALOG.PROCESS_SETTINGS);
    }
  },
  focusProcess({commit, state, getters}, id) {
    let process = getters.byId(id);
    console.log(process);
    if (process) {
      process.setToForeground();
      commit('UPDATE_FOCUSED_PROCESS', process);
    }
  },
  focusNextProcess({ commit, state, dispatch, getters }) {
    let currentIndex = getters.processes.findIndex(p => p.id === state.focusedProcessId);
    console.log('focus next');
    if (currentIndex + 1 > getters.processes.length - 1) {
      currentIndex = 0;
    } else {
      currentIndex++;
    }
    let process = getters.processes[currentIndex];
    console.log('next process : ', process);

    dispatch('focusProcess', process.id);
  },
  focusPreviousProcess({ commit, state, dispatch, getters }) {
    let currentIndex = getters.processes.findIndex(p => p.id === getters.focusedProcessId);
    console.log('focus prev');
    if (currentIndex - 1 < 0) {
      currentIndex = getters.processes.length - 1;
    } else {
      currentIndex--;
    }
    let process = getters.processes[currentIndex];
    console.log('prev process : ', process.mainWindowTitle);

    dispatch('focusProcess', process.id);
  },
  closeConnectedProcesses({commit, state, dispatch, getters}) {
    getters.processes.forEach(process => {
      if (process.terminate) {
        process.terminate();
      }
    });
    dispatch('removeProcesses');
  },
  removeProcess({commit, state, getters, dispatch}, process) {
    /*    let teams = state.teams.filter(team => team.processIds.indexOf(process.id) > -1);

        teams.forEach(team => commit('REMOVE_PROCESS_FROM_TEAM', { id: team.id, processId: process.id }));*/
    if (getters.editingProcessId === process.id) {
      dispatch('updateDialog', { dialog: DIALOG.PROCESS_SETTINGS, value: false });
    }
    console.log('Process.js removeProces : ', process);
    dispatch('disconnectCharacter', process);
    commit('REMOVE_PROCESS', process);
  },
  terminateProcess({ commit, state, dispatch }, process) {
    if (process) {
      dispatch('removeProcess', process);
      process.terminate();
    }
  }
};

const getters = {
  processes: (state, getters) => state.processes,
  focusedProcessId: (state) => state.focusedProcessId,
  focusedProcess: (state, getters) => getters.processes.find(p => p.id === getters.focusedProcessId),
  editingProcessId: (state) => state.editingProcessId,
  editingProcess: (state, getters) => getters.processes.find(p => p.id === getters.editingProcessId),
  byId: (state, getters) => id => getters.processes.find(p => p.id === id),
  processByName: (state, getters) => name => getters.processes.find(p => p.name === name),
};

export default {
  state,
  mutations,
  getters,
  actions,
};
