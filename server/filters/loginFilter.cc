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


    auto f = db->execSqlAsyncFuture("select * from users where name = $1", "elliot");
    try {
        auto result = f.get();
        if (result.size() < 1) {
            cout << this->uuid_str << "uuid again!" << endl;
            std::cout << "找不到用户!" << std::endl;
            fccb();
        } else {
            std::cout << "找到了用户!" << std::endl;
            this->is_valid = true;
            cout << "found Again! is_valid is :" << this->is_valid << endl;
            fccb();
        }
    } catch (DrogonDbException exception) {


        error["message"] = "数据库链接错误" + (string) exception.base().what();
        auto res = drogon::HttpResponse::newHttpJsonResponse(error);
        res->setStatusCode(k500InternalServerError);
        fcb(res);
    }


}
