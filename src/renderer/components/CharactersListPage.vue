<template>
    <v-layout row>
        <v-flex xs12>
            <v-container fluid>
                <v-expansion-panel :expand="processes.length > 0">
                    <v-expansion-panel-content :value="processes.length > 0">
                        <div slot="header"><v-chip disabled style="font-weight: bold;">{{ processes.length }}</v-chip> Personnages connectés</div>
                        <v-list two-line>
                            <draggable v-model="processes" :options="{group:'processes'}">
                                <transition-group>
                                    <character v-for="process in processes" :process="process" :key="process.id"></character>
                                </transition-group>
                            </draggable>
                        </v-list>
                    </v-expansion-panel-content>
                </v-expansion-panel>
                <v-expansion-panel :expand="disconnectedCharacters.length > 0">
                    <v-expansion-panel-content :value="disconnectedCharacters.length > 0">
                        <div slot="header"><v-chip disabled style="font-weight: bold;">{{ disconnectedCharacters.length }}</v-chip> Personnages non connectés</div>
<!--                        <v-list two-line>
                            <character v-for="process in disconnectedCharacters"></character>
                        </v-list> -->
                    </v-expansion-panel-content>
                </v-expansion-panel>
            </v-container>
        </v-flex>
    </v-layout>
</template>

<script>
  import SystemInformation from './LandingPage/SystemInformation';
  import draggable from 'vuedraggable';
  import {remote} from 'electron';
  import v4 from 'uuid';
  import DofusWindowsEvent from './DofusWindowsEvent';
  import Vue from 'vue';
  import {mapGetters, mapMutations, mapActions} from 'vuex';
  import TeamList from './TeamList';
  import ProcessSettings from './CharacterSettings';
  import Character from './Character';

  let nextShortcut = null;
  let previousShortcut = null;

  const dofusEvents = new DofusWindowsEvent();

  export default {
    name: 'characters-list-page',
    components: {SystemInformation, draggable, TeamList, ProcessSettings, Character},
    mounted() {
      dofusEvents.on('login', process => {
        this.addProcess(process);
        if (!this.focusedProcess) {
          /*this.$store.commit('ADD_TEAM', { id: v4(), processes: [process] });*/
          this.updateFocusedProcess(process);
        }
      });
      dofusEvents.on('logout', process => {
        this.removeProcess(process);
      });
      dofusEvents.on('close', process => {
        this.removeProcess(process);
      });
      nextShortcut = remote.globalShortcut.register('CommandOrControl+n', () => {
        if (!this.isLocked) {
          this.focusNextProcess();
        }
      });
      previousShortcut = remote.globalShortcut.register('CommandOrControl+,', () => {
        if (!this.isLocked) {
          this.focusPreviousProcess();
        }
      });
    },
    methods: {
      ...mapActions([
        'updateFocusedProcess',
        'removeProcesses',
        'updateProcesses',
        'addProcess',
        'removeProcess',
        'editProcess',
        'focusProcess',
        'focusPreviousProcess',
        'focusNextProcess',
      ]),
      openSettings(item) {
        this.editProcess(item);
      },
      onProcessClick(process) {
      },
      terminate(process) {
        if (process && process.terminate) {
          process.terminate();
        }
      },
      open(link) {
        this.$electron.shell.openExternal(link);
      },
    },
    data() {
      return {
        isLocked: false,
        processSettingsDialog: false,
        selectedProcessSettings: null,
      }
    },
    computed: {
      ...mapGetters([
        'focusedProcess',
        'getCharacterByName',
        'disconnectedCharacters',
        'characters',
      ]),
/*      teams: {
        get() {
          return this.$store.getters.teams;
        },
        set(value) {
          console.log('UPDATE_TEAM : ', value)
          this.UPDATE_TEAM({ id: this.team.id, processes: value });
        }
      },*/
      processes: {
        get() {
          return this.$store.getters.processes;
        },
        set(value) {
          this.updateProcesses(value);
        }
      }
    },
  };
</script>

<style scoped>
</style>
