import axios, {AxiosInstance} from 'axios';
import {boot} from 'quasar/wrappers';

declare module 'vue/types/vue' {
  interface Vue {
    $axios: AxiosInstance;
  }
}

export default boot(({Vue}) => {
  // eslint-disable-next-line @typescript-eslint/no-unsafe-member-access
  // 创建 axios
  Vue.prototype.$axios = axios.create({
    // `url` 是用于请求的服务器 URL
    // url: '/user',

    // `method` 是创建请求时使用的方法
    method: 'post', // 默认是 get

    // `baseURL` 将自动加在 `url` 前面，除非 `url` 是一个绝对 URL。
    // 它可以通过设置一个 `baseURL` 便于为 axios 实例的方法传递相对 URL
    baseURL: 'http://127.0.0.1:1995/',

  });
});
