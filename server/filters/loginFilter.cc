/**
 *
 *  loginFilter.cc
 *
 */

#include "loginFilter.h"


void loginFilter::doFilter(const HttpRequestPtr &req,
                           FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    //Edit your logic here

    uuid_generate(this->uuid);

    uuid_unparse(this->uuid, this->uuid_str);
    cout << "Login Filter" << endl;
    cout << "UUID IS \t " << this->uuid_str << endl;

    auto db = drogon::app().getDbClient("blog");

    //  流借口无法访 修改外部的变量
//    *db << "select * from users where name=  $1"
//        << "elliot"
//        >> [&](const Result &result) {
//
//            if (result.size() < 1) {
//                cout << this->uuid_str << "uuid again!" << endl;
//                std::cout << "找不到用户!" << std::endl;
//            } else {
//                std::cout << "找到了用户!" << std::endl;
//
//                this->is_valid = true;
//            }
//
//        } >> [&](const DrogonDbException &exception) {
//        auto res = drogon::HttpResponse::newHttpResponse();
//        std::string mess = "数据库链接错误";
//        mess += exception.base().what();
//        res->setStatusCode(k500InternalServerError);
//        res->setContentTypeCode(CT_TEXT_PLAIN);
//        res->setBody(mess);
//        fcb(res);
//    };

//    db->execSqlAsync("select * from users where name=$1",
//                     [this, fccb = move(fccb), fcb = move(fcb)](const Result &result) {
//
//                         if (result.size() < 1) {
//                             cout << this->uuid_str << "uuid again!" << endl;
//                             std::cout << "找不到用户!" << std::endl;
//                             fccb();
//                         } else {
//                             std::cout << "找到了用户!" << std::endl;
//                             this->is_valid = true;
//                             cout << "found Again! is_valid is :" << this->is_valid << endl;
//                             fccb();
//                         }
//
//                     },
//                     [fcb](const DrogonDbException &exception) {
//                         auto res = drogon::HttpResponse::newHttpResponse();
//                         std::string mess = "数据库链接错误";
//                         mess += exception.base().what();
//                         res->setStatusCode(k500InternalServerError);
//                         res->setContentTypeCode(CT_TEXT_PLAIN);
//                         res->setBody(mess);
//                         fcb();
//                     },
//                     "elliot");


// 使用 furture 借口

    cout << "Before params" << endl;
    auto params = req->getJsonObject();

    Json::Value error;

    error["code"] = 421;
    error["message"] = "发生了错误!";
    // req->getBody() 返回 string_view 类型,可以判断是否为空
    auto req_1 = req->getBody();


    if (req_1.empty() || params->empty() || !(*params)["user"].isString() ||
        !(*params)["password"].isString()) {
        cout << "here is ok 1" << endl;
        error["message"] = "用户名或者密码为空";
        auto resp = HttpResponse::newHttpJsonResponse(error);
        fcb(resp);
    }


    auto f = db->execSqlAsyncFuture("select * from users where name = $1 or phone = $2 or email = $3",
                                    (*params)["user"].asString(),
                                    (*params)["user"].asString(),
                                    (*params)["user"].asString());
    try {
        auto result = f.get();
        if (result.size() < 1) {
            error["message"] = "找不到用户!";
            auto res = drogon::HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k404NotFound);
            fcb(res);
        } else {
            std::cout << "找到了用户,开始验证用户名密码:" << std::endl;
            this->is_valid = true;

            // 验证 逻辑为:
            // 1. 发送 用户名 到 服务器端,服务器端查看是否有这个用户,有的话就返回 公匙,没有的话返回404 找不到用户
            // 2.找到用户以后,客户端再次发送用RSA 加密过的密码秘文到服务器端.
            // 3. 服务器比对是否一直

            // 验证成功. 跳转到控制器.
            fccb();
        }
    } catch (DrogonDbException exception) {


        error["message"] = "数据库链接错误" + (string) exception.base().what();
        auto res = drogon::HttpResponse::newHttpJsonResponse(error);
        res->setStatusCode(k500InternalServerError);
        fcb(res);
    }


}


string &loginFilter::getPassWord(string input_rsa_s, string input_rsa_private) {
    // 通过获取来的
    string result("");
    while (input_rsa_s.empty() || input_rsa_private.empty()) {
        return result;
    }

    // pretend we are decrypting a message we have received using a the private key we have
    char *rsaPrivateKeyChar = (char *) input_rsa_private.c_str();
    // write char array to BIO
    BIO *rsaPrivateBIO = BIO_new_mem_buf(rsaPrivateKeyChar, -1);
    // create a RSA object from private key char array
    RSA *rsaPrivateKey = NULL;
    PEM_read_bio_RSAPrivateKey(rsaPrivateBIO, &rsaPrivateKey, NULL, NULL);
    int length = RSA_size(rsaPrivateKey);
    auto decrypText = make_shared<string>();
    unsigned char *d_char = (unsigned char *) new char(length + 1);
    memset(d_char, 0, length + 1);
    int rect = RSA_private_decrypt(input_rsa_s.length(), (const unsigned char *) input_rsa_s.c_str(), d_char,
                                   rsaPrivateKey, RSA_PKCS1_PADDING);
    if (rect > 0) {
        decrypText->append((char *) d_char);
    }

    free(d_char);
    BIO_free_all(rsaPrivateBIO);
    RSA_free(rsaPrivateKey);

    return *decrypText;

}
