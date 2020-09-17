/**
 *
 *  loginFilter.cc
 *
 */

#include "loginFilter.h"
#include <drogon/drogon.h>
#include  <drogon/orm/DbClient.h>
#include <uuid/uuid.h>

using namespace drogon::orm;
using namespace drogon;

void loginFilter::doFilter(const HttpRequestPtr &req,
                           FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    //Edit your logic here
    unsigned char uuid[100];
    uuid_generate(uuid);
    auto db = drogon::app().getDbClient("blog");
    *db << "select * from users where id=  $1"
        << (uint16_t)*uuid
        >> [&](const Result &result) {

            if (result.size() < 1) {
                std::cout << "找不到用户!" << std::endl;
                fccb();
            } else {
                std::cout << "找到了用户!" << std::endl;
                fccb();
            }

        } >> [&](const DrogonDbException &exception) {
        auto res = drogon::HttpResponse::newHttpResponse();
        std::string mess = "数据库链接错误";
        mess += exception.base().what();
        res->setStatusCode(k500InternalServerError);
        res->setContentTypeCode(CT_TEXT_PLAIN);
        res->setBody(mess);
        fcb(res);
    };

//    if (1) {
//        //Passed
//        std::cout << "Loging Filter Here" << std::endl;
//        fccb();
//        return;
//    }
    //Check failed

}
