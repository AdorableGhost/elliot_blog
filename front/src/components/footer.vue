<template>
  <div class="q-pa-md row">
    <div class=" col-12">
      <q-tabs
        v-model="tab"
        narrow-indicator
        dense
        align="justify"
      >
        <q-tab class="text-purple" name="mails" icon="mail" label="Mails"/>
        <q-tab class="text-orange" name="alarms" icon="alarm" label="Alarms"/>
        <q-tab class="text-teal" name="movies" icon="movie" label="Movies"/>
      </q-tabs>

    </div>
  </div>
</template>

<script lang="ts">
  import {defineComponent} from '@vue/composition-api';

  export default defineComponent({
    name: 'footer',
  });
</script>
