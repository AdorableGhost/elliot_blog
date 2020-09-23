#include "registController.h"

shared_ptr<map<string, string>> mkRsaKey(int g_nBits);

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
        || !(*params)["language"].isString() || !(*params)["avatar"].isString()) {
        cout << "here is ok 1" << endl;
        error["message"] = "参数不对!,缺少必要参数.";
        auto resp = HttpResponse::newHttpJsonResponse(error);
        callback(resp);
    }

    // 参数检查完成,可以进行注册动作.
    // 首先生成 RSA 密匙和公匙,
    auto rsa_key = mkRsaKey(1024);

//    cout << "before insert " << endl;
//    cout << " rsa_key  private" << rsa_key.get()->find("private")->second << endl;
//    cout << " rsa_key  public " << rsa_key.get()->find("public")->second << endl;

    string rsa_pri = rsa_key.get()->find("private")->second;
    string rsa_pub = rsa_key.get()->find("public")->second;


    auto res = db->execSqlAsyncFuture(
            "insert into users(name,email,phone,password,rsa_private,rsa_public) values($1,$2,$3,$4,$5,$6)",
            (*params)["name"].asString(), (*params)["email"].asString(), (*params)["phone"].asString(),
            (*params)["password"].asString(),
            rsa_pri, rsa_pub);

    try {
        auto result = res.get();
        cout << "" << result.size() << endl;
        if (result.affectedRows() < 1) {
            error["message"] = "未成功!!";
            auto res = drogon::HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k500InternalServerError);
            callback(res);
        } else {
            std::cout << "增加用户成功!" << std::endl;
            error["code"] = 200;
            error["message"] = "OK";

            // 如果插入成功,设置Token 并且Token 入库,返回Token,跳转到后台中心 (前端动作)

            auto res = drogon::HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k200OK);
            callback(res);

        }
    } catch (const DrogonDbException exception) {


        error["message"] = "数据库链接错误" + (string) exception.base().what();
        auto res = drogon::HttpResponse::newHttpJsonResponse(error);
        res->setStatusCode(k500InternalServerError);
        callback(res);
    }


}

//namespace drogon;

shared_ptr<map<string, string>> mkRsaKey(int g_nBits) {
    // 自动生成 RSA 密匙,返回为 map <string,string> 的容器
    RSA *pRsa = RSA_generate_key(g_nBits, RSA_F4, nullptr, nullptr);
    auto mp = make_shared<map<string, string>>();
    string result = "";
    while (pRsa == NULL) {
        cout << "Generate RSA Key Error" << endl;
        return mp;
    }

    //
    //    // extract private key as string
    //    // create a place to dump the IO, in this case in memory
    BIO *privateBIO = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(privateBIO, pRsa, NULL, NULL, 0, NULL, NULL);
    // get buffer length
    int privateKeyLen = BIO_pending(privateBIO);

    // create char reference of private key length
    auto privateString = make_shared<string>();
    char *privateKeyChar = (char *) malloc(privateKeyLen);
    // read the key from the buffer and put it in the char reference
    BIO_read(privateBIO, privateKeyChar, privateKeyLen);
    privateKeyChar[privateKeyLen] = '\0';
    privateString->append(privateKeyChar);

    mp->insert_or_assign("private", privateString->data());
    // 释放内存地址
//    cout << "in Function" << endl;
//    cout << privateKeyChar << endl;
//    cout << "------0-------" << endl;
//    cout << privateKeyChar[privateKeyLen] << endl;
//    cout << "-------1-------" << endl;
//    cout << privateKeyChar[privateKeyLen - 1] << endl;
//    cout << "--------2------" << endl;
//    cout << privateKeyChar[privateKeyLen - 2] << endl;
//    cout << " end in Function" << endl;
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

    auto publicString = make_shared<string>();
    publicString->append(publicKeyChar);
    mp->insert_or_assign("public", publicString->data());

    RSA_free(pRsa);
    free(publicKeyChar);
    free(privateKeyChar);
    BIO_free_all(privateBIO);
    BIO_free_all(publicBIO);
    return mp;
}