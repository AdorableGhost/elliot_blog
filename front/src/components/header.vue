<template>
  <div class="q-gutter-md">
    <div class="">
      <div class="bg-cyan text-white">
        <q-toolbar>
          <!--          <q-btn flat round dense icon="assignment_ind"/>-->

          <q-btn dense class="animate__shakeY" flat round>
            <q-img src="../../public/icons/favicon-128x128.png" style="width: 40px;height: 40px"></q-img>
          </q-btn>


          <q-toolbar-title>魔鬼精灵</q-toolbar-title>
          <q-breadcrumbs active-color="white" style="font-size: 16px">
            <q-breadcrumbs-el label="Home" to="/index" class="text-brown-8 eva-hover" icon="eva-home"/>

            <q-breadcrumbs-el class="text-brown-7" to="/article" label="文章" icon="eva-folder eva-shake"/>
            <q-breadcrumbs-el class="text-brown-6" label="个人中心" to="admin" icon="eva-person"/>
            <q-breadcrumbs-el class="text-brown-5" label="Github"
                              v-on:click="open_github" icon="eva-github"/>
          </q-breadcrumbs>
        </q-toolbar>
      </div>
    </div>

    <q-carousel
      v-model="slide"
      transition-prev="slide"
      transition-next="fade"
      swipeable
      animated
      v-show="coursel_display"
      control-color="white"
      navigation
      padding
      arrows
      height="300px"
      class="bg-teal-1 text-blue-grey-10 shadow-4 rounded-borders"
    >
      <q-carousel-slide name="style" class="column no-wrap flex-center">
        <q-icon name="eva-star" size="56px"/>
        <div class="q-mt-md text-center">
          {{slogan}}
        </div>
      </q-carousel-slide>
      <q-carousel-slide name="tv" class="column no-wrap flex-center">
        <q-icon name="live_tv" size="56px"/>
        <div class="q-mt-md text-center">
          {{slogan}}
        </div>
      </q-carousel-slide>
      <q-carousel-slide name="layers" class="column no-wrap flex-center">
        <q-icon name="layers" size="56px"/>
        <div class="q-mt-md text-center">
          {{slogan}}
        </div>
      </q-carousel-slide>
      <q-carousel-slide name="map" class="column no-wrap flex-center">
        <q-icon name="terrain" size="56px"/>
        <div class="q-mt-md text-center">
          {{slogan}}
        </div>
        slide
      </q-carousel-slide>
    </q-carousel>

  </div>

</template>

<script lang="ts">
  import {defineComponent} from '@vue/composition-api';

  export default defineComponent({
    name: 'index_header',
    props: ["coursel_display"],
    data() {
      return {
        slide: 'style',
        slogan: '北宫黝之养勇也，不肤挠，不目逃，思以一豪挫於人，若挞之于市朝；不受于褐宽博，' +
          '亦不受于万乘之君；视刺万乘之君，若刺褐夫；无严诸侯，恶声至，必反之。孟施舍之所养勇也，' +
          '曰：‘视不胜犹胜也；量敌而后进，虑胜而后会，是畏三军者也。舍岂能为必胜哉，能无惧而已矣。’' +
          '孟施舍似曾子，北宫黝似子夏。夫二子之勇，未知其孰贤，然而孟施舍守约也。昔者曾子谓子襄曰：‘' +
          '子好勇乎？吾尝闻大勇于夫子矣：自反而不缩，虽褐宽博，吾不惴焉。自反而缩，虽千万人吾往矣。' +
          '’孟施舍之守气，又不如曾子之守约也。',
        trans_annimate: 'animated shakeY'

      }
    },
    methods: {
      shake: (item, el) => {
        console.log("shake this");

      },
      open_github() {
        window.open('https://github.com/AdorableGhost');
      }
    }
  });
</script>
