import Vue from 'vue';
import Vuetify from 'vuetify';
import 'vuetify/dist/vuetify.min.css';

import App from './App';
import router from './router';
import store from './store';

if (!process.env.IS_WEB) Vue.use(require('vue-electron'));
Vue.config.productionTip = false;
Vue.use(Vuetify);

export function toCharacterName(value) {
  if (!value) return ''
  value = value.toString()
  return value.split(' - Dofus').shift();
}

Vue.filter('toCharacterName', toCharacterName);

/* eslint-disable no-new */
new Vue({
  components: { App },
  router,
  store,
  template: '<App/>',
}).$mount('#app');
