<template>
  <q-page>
    <q-page-container class="row q-pa-md">
      <div class=" row">
        <article_index></article_index>
        <right></right>
      </div>

    </q-page-container>
    <!--    分页 -->
    <div class="text-blue-grey-7 col-sm-12 col-xs-12 q-pa-md flex flex-bottom" id="paginator">

      <div class="q-pa-lg flex flex-bottom flex-left">
        <q-pagination
          v-model="current"
          color="purple"
          :max="10"
          :max-pages="6"
          :boundary-numbers="true"
        >
        </q-pagination>
      </div>
    </div>
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
    },
    data() {
      return {
        current: 6
      };
    }
  });
</script>
