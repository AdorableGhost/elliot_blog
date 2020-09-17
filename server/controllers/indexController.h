#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class indexController : public drogon::HttpSimpleController<indexController> {
public:
    virtual void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        //list path definitions here;
        PATH_ADD(

                "/", Post, Get, "loginFilter");


    PATH_LIST_END
};
