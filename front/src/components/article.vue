<template>

  <div class="col-md-8 col-sm-12 col-xs-12" id="main_c">
    <div class=" text-blue-grey-7 q-pa-md">
      <q-card class="bg-teal-2">
        <q-card-section class=" row ">
          <div class="text-h6 col-12">oatpp 学习 - 持续更新</div>

          <div class="text-h7 col-9 q-pa-md q-ma-lg-md">
            oatpp DTO 声明
            使用

            class MessageDto : public oatpp::DTO {

            DTO_INIT(MessageDto, oatpp::DTO /* Extends */)

            DTO_FIELD(Int32, statusCode); // Status code field
            DTO_FIELD(String, message); // Message field

            };

            /* End DTO code-generation */
            #include OATPP_CODEGEN_END(DTO)
            不能使用：
          </div>
          <q-item clickable v-ripple class="q-pa-sm col-3">
            <q-item-section side>
              <q-avatar size="48px">
                <img src="../../public/icons/favicon-128x128.png"/>
                <!--                  <q-badge floating color="teal">new</q-badge>-->
              </q-avatar>
            </q-item-section>
            <q-item-section>
              <q-item-label class="text-blue-7">Elliot</q-item-label>
              <q-item-label class="text-blue-5" caption>Admin</q-item-label>
            </q-item-section>
            <q-item-section class="text-blue-5" side>
              3 min ago
            </q-item-section>
          </q-item>
        </q-card-section>

        <q-separator/>

        <div class="col-9 q-pa-sm q-pt-lg">
              <span class="q-pa-sm ">
                <q-btn class="" color="blue-4" label="oatpp"/>
              </span>
          <span class="q-pa-sm">
                <q-btn class="" color="blue-4" label="oatpp"/>
              </span>
        </div>


        <q-card-actions class="col-3" align="right">
          <q-btn dense size="md" color="red-4"> 点赞</q-btn>
          <q-btn dense size="md" color="blue-5"> 阅读</q-btn>
        </q-card-actions>
      </q-card>
    </div>

  </div>


</template>

<script lang="ts">
  import {defineComponent} from '@vue/composition-api';

  export default defineComponent({
    name: 'header',
    data() {
      return {
        slide: 'style',
        current: 6,
        slogan: '北宫黝之养勇也，不肤挠，不目逃，思以一豪挫於人，若挞之于市朝；不受于褐宽博，亦不受于万乘之君；视刺万乘之君，若刺褐夫；无严诸侯，恶声至，必反之。孟施舍之所养勇也，曰：‘视不胜犹胜也；量敌而后进，虑胜而后会，是畏三军者也。舍岂能为必胜哉，能无惧而已矣。’孟施舍似曾子，北宫黝似子夏。夫二子之勇，未知其孰贤，然而孟施舍守约也。昔者曾子谓子襄曰：‘子好勇乎？吾尝闻大勇于夫子矣：自反而不缩，虽褐宽博，吾不惴焉。自反而缩，虽千万人吾往矣。’孟施舍之守气，又不如曾子之守约也。'
      }
    },
  });
</script>
