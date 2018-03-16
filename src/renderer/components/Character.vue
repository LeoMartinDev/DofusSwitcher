<template>
    <v-list-tile>
        <v-list-tile-avatar>
            <img v-if="character.imagePath !== ''" :src="character.imagePath">
            <img v-else src="/static/images/avatars/default.png">
        </v-list-tile-avatar>
        <v-list-tile-content>
            <v-list-tile-title style="font-weight: bold;" v-text="process.mainWindowTitle"></v-list-tile-title>
        </v-list-tile-content>
        <v-list-tile-content v-if="character.initiative">
            <v-chip disabled style="font-weight: bold;">{{ character.initiative }}</v-chip>
        </v-list-tile-content>
        <v-list-tile-action>
            <v-btn icon ripple @click.native="focusProcess(process.id)">
                <v-icon color="grey">open_in_browser</v-icon>
            </v-btn>
        </v-list-tile-action>
        <v-list-tile-action>
            <v-menu offset-y transition="scale-transition" class="no-drag">
                <v-btn icon class="no-drag" slot="activator">
                    <v-icon color="grey">more_vert</v-icon>
                </v-btn>
                <v-list>
                    <v-list-tile avatar @click="editProcess(process)">
                        <v-list-tile-avatar>
                            <v-icon>settings</v-icon>
                        </v-list-tile-avatar>
                        <v-list-tile-title>Paramètres</v-list-tile-title>
                    </v-list-tile>
                    <v-list-tile avatar @click="terminateProcess(process)">
                        <v-list-tile-avatar>
                            <v-icon>close</v-icon>
                        </v-list-tile-avatar>
                        <v-list-tile-title>Fermer</v-list-tile-title>
                    </v-list-tile>
                </v-list>
            </v-menu>
        </v-list-tile-action>
    </v-list-tile>
</template>

<script>
  import { mapGetters, mapMutations, mapActions } from 'vuex';

  export default {
    name: "character",
    props: {
      process: {
        required: true,
      },
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
        'terminateProcess',
      ]),
      tileClick() {
        console.log('process : ', this.process);
        console.log('character : ', this.character);
      },
    },
    computed: {
      character() {
        console.log(this.$store.getters.getCharacterByName(this.process.name));
        return this.$store.getters.getCharacterByName(this.process.mainWindowTitle) || {};
      }
    }
  }
</script>

<style scoped>

</style>