<template>
    <v-list-tile>
        <v-list-tile-avatar>
            <img v-if="character.imagePath !== ''" :src="character.imagePath">
            <img v-else src="/static/images/avatars/default.png">
        </v-list-tile-avatar>
        <v-list-tile-content>
            <v-list-tile-title style="font-weight: bold;">{{ process.mainWindowTitle | toCharacterName }}</v-list-tile-title>
        </v-list-tile-content>
<!--         <v-list-tile-content v-if="character.initiative">
            <v-chip disabled style="font-weight: bold;">{{ character.initiative }}</v-chip>
        </v-list-tile-content> -->
        <v-list-tile-action>
            <v-switch
                    v-model="isDisabled"
            ></v-switch>
        </v-list-tile-action>
        <v-list-tile-action>
            <v-btn icon ripple @click.native="focusProcess(process)">
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
import { mapActions } from "vuex";

export default {
  name: "character",
  props: {
    process: {
      required: true
    }
  },
  methods: {
    ...mapActions([
      "updateFocusedProcess",
      "removeProcesses",
      "updateProcesses",
      "addProcess",
      "removeProcess",
      "editProcess",
      "focusProcess",
      "focusPreviousProcess",
      "focusNextProcess",
      "terminateProcess",
      "toggleAccessiblity"
    ]),
    tileClick() {}
  },
  computed: {
    character() {
      return (
        this.$store.getters.getCharacterByName(this.process.mainWindowTitle) ||
        {}
      );
    },
    isDisabled: {
      get() {
        return !this.process.disabled;
      },
      set() {
        this.toggleAccessiblity(this.process);
      }
    }
  }
};
</script>

<style scoped>

</style>