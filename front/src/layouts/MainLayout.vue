<template>
  <q-layout view="lHh Lpr lFf" class="">
    <indexHeader></indexHeader>
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

    }
  });
</script>
