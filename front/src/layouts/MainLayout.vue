<template>
  <q-layout view="lHh Lpr lFf" class="">
    <indexHeader :coursel_display="coursel_display"></indexHeader>
    <q-page-container class="q-ma-lg q-pa-lg">

      <router-view/>
      <bottom></bottom>
    </q-page-container>
  </q-layout>
</template>

<script lang="ts">
  import indexHeader from 'components/header.vue';
  import bottom from 'components/footer.vue';
  import left from 'components/right.vue';


  import {defineComponent, ref} from '@vue/composition-api';

  export default defineComponent({
    name: 'MainLayout',
    components: {
      indexHeader,
      bottom,
      left
    },
    setup() {


    },
    created() {
      if (this.$route.path in this.$store.state.blog.except_h_f) {
        this.coursel_display = false;
        console.log(" created this.coursel_display=" + this.coursel_display);
      } else {
        this.coursel_display = true;
      }

    },
    beforeRouteUpdate(to, from, next) {
      console.log("to页面是:" + to.path);
      console.log("from页面是:" + from.path);
      // console.log("next页面是:" + next.path);

      if (to.path in this.$store.state.blog.except_h_f) {
        this.coursel_display = false;
        console.log(" created this.coursel_display=" + this.coursel_display);
      } else {
        this.coursel_display = true;
      }

      next();
    },
    data() {
      return {
        coursel_display: true,
      };
    }
  });
</script>
