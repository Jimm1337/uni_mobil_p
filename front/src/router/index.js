import { createRouter, createWebHistory } from 'vue-router';
import HomeView from '../views/HomeView.vue';
import AboutView from '../views/AboutView.vue';
import FavouriteView from '../views/FavouriteView.vue';
import RegisterView from '../views/RegisterView.vue';
import RankingView from '../views/RankingView.vue';
import FormView from '../views/FormView.vue';

const routes = [
  {
    path: '/',
    name: 'home',
    component: HomeView,
    meta: { hideMenu: true },
  },
  {
    path: '/about',
    name: 'about',
    component: AboutView,
    meta: { hideMenu: false },
  },
  {
    path: '/favourite',
    name: 'favourite',
    component: FavouriteView,
    meta: { hideMenu: false },
  },
  {
    path: '/register',
    name: 'register',
    component: RegisterView,
    meta: { hideMenu: true },
  },
  {
    path: '/ranking',
    name: 'ranking',
    component: RankingView,
    meta: { hideMenu: false },
  },
  {
    path: '/form',
    name: 'form',
    component: FormView,
    meta: { hideMenu: false },
  },
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
});

export default router;
