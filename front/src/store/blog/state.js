export default function () {
  return {
    //
    user: {
      name: "",
      password: "",
      email: "",
      phone: "",
      language: "",
      avatar: "eva-name",
      token: ""
    },
    except_h_f: {
      // except_h_f 是不需要 footer 和 header 的 页面,这里在MyLayouts 里面调用就可以判断显示 Header 和Footer
      "/register": true
    }
  }
}
