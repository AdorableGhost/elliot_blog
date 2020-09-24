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
    mounted() {
      console.log("mounted this.showIndex=" + this.showIndex);

    },
    beforeMount() {
      console.log("页面是:" + this.$route.path);

      if (this.$route.path in this.$store.state.blog.except_h_f) {
        this.coursel_display = false;
        console.log(" created this.coursel_display=" + this.coursel_display);
      } else {
        this.coursel_display = true;
      }

    },
    data() {
      return {
        coursel_display: true,
      };
    }
  });
</script>
