#pragma once

#include <drogon/HttpSimpleController.h>
#include <uuid/uuid.h>
#include <iostream>
#include <map>
#include <json/json.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>


using namespace drogon;
using namespace drogon::orm;
using namespace std;

class registController : public drogon::HttpSimpleController<registController> {
public:
    virtual void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;



    PATH_LIST_BEGIN
        //list path definitions here;
        PATH_ADD("/register", Post);
    PATH_LIST_END
};
