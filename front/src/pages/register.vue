<template>
  <q-page>
    <q-page-container class="row q-pa-md items-center">
      <div class="col-md-7 col-sm-12 col-xs-12 items-center items-start" style="margin: auto">

        <register></register>
      </div>

    </q-page-container>

  </q-page>
</template>

<script lang="ts">
  import {Todo, Meta} from 'components/models';
  import {defineComponent, ref} from '@vue/composition-api';
  import register from "components/register.vue";

  export default defineComponent({
    name: 'Register',
    components: {
      "register": register,
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
