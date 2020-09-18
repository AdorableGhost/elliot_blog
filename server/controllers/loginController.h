#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class loginController : public drogon::HttpSimpleController<loginController> {
public:
    virtual void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        //list path definitions here;
        PATH_ADD(

                "/login", Post, "loginFilter");
    PATH_LIST_END
};
