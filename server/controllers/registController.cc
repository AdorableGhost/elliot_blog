#include "registController.h"
#include

void registController::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                              std::function<void(const HttpResponsePtr &)> &&callback) {
    //write your application logic here


    auto db = drogon::app().getDbClient("blog");
    cout << "Before params" << endl;
    auto params = req->getJsonObject();

    Json::Value error;

    error["code"] = 421;
    error["message"] = "发生了错误!";
    // req->getBody() 返回 string_view 类型,可以判断是否为空
    auto req_1 = req->getBody();


    if (req_1.empty() || params->empty() || !(*params)["name"].isString() ||
        !(*params)["password"].isString() || !(*params)["email"].isString() || !(*params)["phone"].isString()
        || !(*params)["language"].isString()) {
        cout << "here is ok 1" << endl;
        error["message"] = "参数不对!,缺少必要参数.";
        auto resp = HttpResponse::newHttpJsonResponse(error);
        fcb(resp);
    }

    // 参数检查完成,可以进行注册动作.
    // 首先生成 RSA 密匙和公匙,
    // 然后判断 是否提交了头像,如果没有提交,那么生成默认的头像

    auto rsa_key = this->mkRsaKey(1024);




    // 如果插入成功,设置Token 并且Token 入库,返回Token,跳转到后台中心 (前端动作)
}

inline map <string, string> *registController::mkRsaKey(int g_nBits) {
    // 自动生成 RSA 密匙,返回为 map <string,string> 的容器
    RSA *pRsa = RSA_generate_key(g_nBits, RSA_F4, nullptr, nullptr);
    auto mp = make_shared < map < string, string>>();
    string result = "";
    while (pRsa == NULL) {
        cout << "Generate RSA Key Error" << endl;
        return mp.get();
    }

    //
    //    // extract private key as string
    //    // create a place to dump the IO, in this case in memory
    BIO *privateBIO = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(privateBIO, pRsa, NULL, NULL, 0, NULL, NULL);
    // get buffer length
    int privateKeyLen = BIO_pending(privateBIO);

    // create char reference of private key length
    string privateString;
    char *privateKeyChar = (char *) malloc(privateKeyLen);
    // read the key from the buffer and put it in the char reference
    BIO_read(privateBIO, privateKeyChar, privateKeyLen);
    privateString.append(privateKeyChar);

    mp->insert_or_assign("private", privateString);
    // 释放内存地址

    // at this point we can save the private key somewhere

    // 生成成功 私匙.


    // extract public key as string
    // create a place to dump the IO, in this case in memory
    BIO *publicBIO = BIO_new(BIO_s_mem());
    // dump key to IO
    PEM_write_bio_RSAPublicKey(publicBIO, pRsa);
    // get buffer length
    int publicKeyLen = BIO_pending(publicBIO);
    // create char reference of public key length
    char *publicKeyChar = (char *) malloc(publicKeyLen);
    // read the key from the buffer and put it in the char reference
    BIO_read(publicBIO, publicKeyChar, publicKeyLen);
    // at this point we can save the public somewhere

    string publicString;
    publicString.append(publicKeyChar);
    mp->insert_or_assign("public", publicString);

    RSA_free(pRsa);
    free(publicKeyChar);
    free(privateKeyChar);
    BIO_free_all(privateBIO);
    BIO_free_all(publicBIO);
    return mp.get();
}