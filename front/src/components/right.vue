<template>
  <div class="col-md-4 col-sm-12 col-xs-12" id="right">
    <div class=" text-blue-grey-7 q-pa-md">
      <q-card class="profile bg-teal-2">
        <q-parallax
          src="https://cdn.quasar.dev/img/parallax1.jpg"
          :height="150"
        />
        <q-card-section>
          <div class="text-h6 text-blue-5">Elliot</div>
          <div class="text-subtitle2">Talk is cheap, show me the code</div>
        </q-card-section>
      </q-card>


    </div>

    <div class=" text-blue-grey-7 col-sm-12 col-xs-12 q-pa-md">
      <q-card class="my-card bg-teal-2">
        <q-card-section class=" text-blue-grey-7">
          <div class="text-h6 text-blue-5">分类</div>
          <div class="text-subtitle2">by John Doe</div>
        </q-card-section>
        <q-card-actions class="q-pa-md q-ma-lg-sm items-center">
          <q-btn dense size="md" color="red-4"> CPP</q-btn>

          <q-btn dense size="md" color="blue-5"> PHP</q-btn>
          <q-btn dense size="md" color="blue-5"> PHP</q-btn>
          <q-btn dense size="md" color="blue-5"> PHP</q-btn>
        </q-card-actions>
      </q-card>
    </div>

  </div>
</template>

<script lang="ts">
  import {defineComponent} from '@vue/composition-api';

  export default defineComponent({
    name: 'left',
  });
</script>
