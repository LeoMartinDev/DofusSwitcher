<template>
    <v-layout row>
        <v-flex xs12>
            <v-toolbar color="cyan" dark fixed>
                <v-menu offset-y transition="scale-transition">
                    <v-toolbar-side-icon slot="activator"></v-toolbar-side-icon>
                    <v-list>
                        <v-list-tile @click="">
                            <v-list-tile-title>Paramètres</v-list-tile-title>
                        </v-list-tile>
                        <v-list-tile @click="">
                            <v-list-tile-title>Paramètres</v-list-tile-title>
                        </v-list-tile>
                    </v-list>
                </v-menu>
                <v-toolbar-title>Inbox</v-toolbar-title>
                <v-spacer></v-spacer>
                <v-btn icon>
                    <v-icon>minimize</v-icon>
                </v-btn>
                <v-btn icon>
                    <v-icon>close</v-icon>
                </v-btn>
            </v-toolbar>

            <v-list two-line>
                <draggable v-model="items" :options="{draggable:'.item'}">
                    <v-list-tile avatar v-for="item in items" :key="item.id" @click="" class="item">
                        <v-list-tile-action>
                            <v-icon v-if="item.icon" color="pink">star</v-icon>
                        </v-list-tile-action>
                        <v-list-tile-content>
                            <v-list-tile-title v-text="item.title"></v-list-tile-title>
                        </v-list-tile-content>
                        <v-list-tile-avatar>
                            <img :src="item.avatar">
                        </v-list-tile-avatar>
                    </v-list-tile>
                </draggable>

            </v-list>
        </v-flex>
    </v-layout>
</template>

<script>
    import SystemInformation from './LandingPage/SystemInformation';
    import draggable from 'vuedraggable';
    import v4 from 'uuid';

    export default {
        name: 'characters-list-page',
        components: {SystemInformation, draggable},
        methods: {
            open(link) {
                this.$electron.shell.openExternal(link);
            },
        },
        data() {
            return {
                items: [
                    {header: 'Today'},
                    {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'sdfdsfsdf this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: '111 this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    }, {
                        id: v4(),
                        avatar: '/static/doc-images/lists/1.jpg',
                        title: 'Brunch this weekend?',
                        subtitle: "<span class='text--primary'>Ali Connors</span> &mdash; I'll be in your neighborhood doing errands this weekend. Do you want to hang out?"
                    },
                ]
            }
        }
    };
</script>

<style>
    @import url('https://fonts.googleapis.com/css?family=Source+Sans+Pro');

    * {
        box-sizing: border-box;
        margin: 0;
        padding: 0;
    }

    body {
        font-family: 'Source Sans Pro', sans-serif;
    }

    #wrapper {
        background: radial-gradient(
                ellipse at top left,
                rgba(255, 255, 255, 1) 40%,
                rgba(229, 229, 229, .9) 100%
        );
        height: 100vh;
        padding: 60px 80px;
        width: 100vw;
    }

    #logo {
        height: auto;
        margin-bottom: 20px;
        width: 420px;
    }

    main {
        display: flex;
        justify-content: space-between;
    }

    main > div {
        flex-basis: 50%;
    }

    .left-side {
        display: flex;
        flex-direction: column;
    }

    .welcome {
        color: #555;
        font-size: 23px;
        margin-bottom: 10px;
    }

    .title {
        color: #2c3e50;
        font-size: 20px;
        font-weight: bold;
        margin-bottom: 6px;
    }

    .title.alt {
        font-size: 18px;
        margin-bottom: 10px;
    }

    .doc p {
        color: black;
        margin-bottom: 10px;
    }

    .doc button {
        font-size: .8em;
        cursor: pointer;
        outline: none;
        padding: 0.75em 2em;
        border-radius: 2em;
        display: inline-block;
        color: #fff;
        background-color: #4fc08d;
        transition: all 0.15s ease;
        box-sizing: border-box;
        border: 1px solid #4fc08d;
    }

    .doc button.alt {
        color: #42b983;
        background-color: transparent;
    }
</style>
