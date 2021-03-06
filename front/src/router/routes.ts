import {RouteConfig} from 'vue-router';

const routes: RouteConfig[] = [
  {
    path: '/',
    component: () => import('layouts/MainLayout.vue'),
    children: [
      {path: '/', component: () => import('pages/Index.vue')},
      {path: 'index', component: () => import('pages/Index.vue')},
      {path: 'article', component: () => import('pages/article.vue')},
      {path: 'admin', component: () => import('pages/admin.vue')},
      {path: 'register', component: () => import('pages/register.vue')},
    ]
  },

  // Always leave this as last one,
  // but you can also remove it
  {
    path: '*',
    component: () => import('pages/Error404.vue')
  }
];

export default routes;
