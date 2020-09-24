<template>

  <div class="col-md-7 col-sm-12 col-xs-12 items-center self-center text-left" id="main_c">
    <div class=" text-blue-grey-7 q-pa-md">
      <q-card class="bg-teal-2">

        <q-card-section class=" row ">
          <div class="text-h6 col-12 ">
            <q-btn icon="eva-person-add" color="grey-6"></q-btn>
          </div>
        </q-card-section>

        <q-card-section class="row">
        </q-card-section>
        <q-card-section class="row">
          <q-input color="purple-12" class="col-md-8 col-sm-12 col-xs-12 col-lg-6" v-model="reg_user.name"
                   style="margin: auto;"
                   label="帐号名称"
                   :rules="[val=>this.name_reg.test(val)||'姓名不能为空']">
            <template v-slot:prepend>
              <q-icon name="eva-person"/>
            </template>
          </q-input>
        </q-card-section>

        <q-card-section class="row">
          <q-input color="purple-12" class="col-md-8 col-sm-12 col-xs-12 col-lg-6" v-model="reg_user.email"
                   unmasked-value
                   hint="xxx@xxx.xxx"
                   :rules="[ val=>email_reg.test(val)|| '邮箱格式部队!']"
                   style="margin: auto;"
                   @focus="reset_v"
                   label="邮箱"

          >
            <template v-slot:prepend>
              <q-icon name="eva-email"/>
            </template>
          </q-input>
        </q-card-section>

        <q-card-section class="row">
          <q-input color="purple-12" :type="isPwd ? 'password' : 'text'"
                   class="col-md-8 col-sm-12 col-xs-12 col-lg-6 q-ma-md" v-model="reg_user.password"
                   style="margin: auto;"
                   :rules="[val=>!!val||'密码不能为空']"
                   clearable
                   label="密码">
            <q-icon
              :name="isPwd ? 'visibility_off' : 'visibility'"
              class="cursor-pointer"
              style="height: 100%"
              @click="isPwd = !isPwd"
            />
            <template v-slot:prepend>
              <q-icon name="eva-eye-off"/>
            </template>

          </q-input>
        </q-card-section>
        <q-card-section class="row">
          <q-input color="purple-12" class="col-md-8 col-sm-12 col-xs-12 col-lg-6" v-model="reg_user.phone"
                   mask="(+86) ### - ### - #####"
                   unmasked-value
                   hint="Mask: (+86) ### - ### - #####"
                   style="margin: auto;"
                   :rules="[val=>!!val&&this.phone_reg.test(val) || '电话号码不符合规范!']"
                   label="电话">
            <template v-slot:prepend>
              <q-icon name="eva-phone"/>
            </template>
            <template v-slot:hint style="color: blue ">
              {{hint}}
            </template>
          </q-input>


        </q-card-section>

        <q-card-section class="row">
          <q-select v-model="reg_user.language" color="purple-12" class="col-md-8 col-sm-12 col-xs-12 col-lg-6"
                    :options="lan_op"
                    style="margin: auto" label="请选择语言"/>


        </q-card-section>


        <div class="col-9 q-pa-sm q-pt-lg items-end text-right">
              <span class="q-pa-sm ">
                <q-btn class="" color="blue-4" label="oatpp"/>
              </span>
        </div>


        <q-card-actions class="col-9 q-pa-sm q-pt-lg" align="right">
          <q-btn dense size="md" color="red-4">忘记密码</q-btn>
          <q-btn dense size="md" color="blue-5"> 登陆</q-btn>
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
        isPwd: true,
        hint: "",
        reg_user: {
          name: "",
          password: "",
          email: "",
          phone: "",
          language: "",
          avatar: "eva-name",
        },
        email_reg: /^([a-zA-Z]|[0-9])(\w|\-)+@[a-zA-Z0-9]+\.([a-zA-Z]{2,4})$/,
        name_reg: /[a-zA-Z+]|[0-9+]/,
        phone_reg: /^1[3456789]\d{9}$/,
        lan_op: [
          {
            label: '简体中文',
            value: '1',
            description: '简体中文',
            category: '1'
          },
          {
            label: 'English',
            value: '2',
            description: 'English',
            category: '1'
          },
        ]


      }
    },
    methods:
      {
        reset_v() {
          this.$refs.input.resetValidation();
        },
        valid_email() {
          let reg = /^([a-zA-Z]|[0-9])(\w|\-)+@[a-zA-Z0-9]+\.([a-zA-Z]{2,4})$/;
          if (reg.test(this.email)) {
            return true
              ;
          } else {
            return false
              ;
          }

        }
      },
    mounted() {

    }
  });
</script>
