<template>
    <v-list two-line>
        <draggable v-model="processes" :options="{group:'processes'}">
            <transition-group>
                <v-list-tile v-if="processes.length > 0" v-for="item in processes" :key="item.id">
                    <v-list-tile-content>
                        <v-list-tile-title v-text="item.mainWindowTitle"></v-list-tile-title>
                    </v-list-tile-content>
                    <v-list-tile-action>
                        <v-btn icon ripple @click="">
                            <v-icon color="grey">open_in_browser</v-icon>
                        </v-btn>
                    </v-list-tile-action>
                    <v-list-tile-action>
                        <v-menu offset-y transition="scale-transition" class="no-drag">
                            <v-btn icon class="no-drag" slot="activator">
                                <v-icon>more_vert</v-icon>
                            </v-btn>
                            <v-list>
                                <v-list-tile avatar @click="">
                                    <v-list-tile-avatar>
                                        <v-icon>settings</v-icon>
                                    </v-list-tile-avatar>
                                    <v-list-tile-title>Paramètres</v-list-tile-title>
                                </v-list-tile>
                                <v-list-tile avatar @click="">
                                    <v-list-tile-avatar>
                                        <v-icon>close</v-icon>
                                    </v-list-tile-avatar>
                                    <v-list-tile-title>Fermer</v-list-tile-title>
                                </v-list-tile>
                            </v-list>
                        </v-menu>
                    </v-list-tile-action>
                </v-list-tile>
            </transition-group>
        </draggable>
    </v-list>
</template>

<script>
  import {mapMutations} from 'vuex';
  import draggable from 'vuedraggable';

  export default {
    name: "team-list",
    components: {
      draggable
    },
    props: {
      team: {}
    },
    methods: {
      ...mapMutations([
        'ADD_PROCESS',
        'REMOVE_PROCESS',
        'UPDATE_FOCUSED_PROCESS',
        'UPDATE_PROCESSES',
        'UPDATE_TEAM',
        'ADD_PROCESS_TO_TEAM',
      ]),
    },
    computed: {
      processes: {
        get() {
          return this.$store.getters.teamProcesses(this.team.id);
        },
        set(value) {
          this.ADD_PROCESS_TO_TEAM({ id: this.team.id, process: value });
        }
      }
    }
  }
</script>

<style scoped>

</style>