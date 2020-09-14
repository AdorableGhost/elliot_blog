<template>
  <q-page>
    <q-page-container class="row q-pa-md">
      <div class=" row">
        <article_index></article_index>
        <right></right>
      </div>
    </q-page-container>
  </q-page>
</template>

<script lang="ts">
  import {Todo, Meta} from 'components/models';
  import {defineComponent, ref} from '@vue/composition-api';
  import right from 'components/right.vue';
  import article_index from "components/article.vue";

  export default defineComponent({
    name: 'PageIndex',
    components: {
      "article_index": article_index,
      'right': right
    },
    setup() {
    }
  });
</script>
