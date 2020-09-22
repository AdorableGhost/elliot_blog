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

class registController : public drogon::HttpSimpleController<registController> {
public:
    virtual void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    static map <string, string> *mkRsaKey(int g_nBits);

    PATH_LIST_BEGIN
    //list path definitions here;
    //PATH_ADD("/path","filter1","filter2",HttpMethod1,HttpMethod2...);
    PATH_LIST_END
};
