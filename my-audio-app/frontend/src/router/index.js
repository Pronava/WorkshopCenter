import { createRouter, createWebHistory } from 'vue-router';
import Home from '../views/Home.vue';
import AudioVisualizer from '../views/AudioVisualizer.vue';

const routes = [
  {
    path: '/',
    name: 'Home',
    component: Home
  },
  {
    path: '/visualizer',
    name: 'Visualizer',
    component: AudioVisualizer
  }
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
});

export default router;
