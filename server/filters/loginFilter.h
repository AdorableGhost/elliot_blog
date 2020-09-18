/**
 *
 *  loginFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
#include <drogon/drogon.h>
#include  <drogon/orm/DbClient.h>
#include <uuid/uuid.h>
#include <iostream>
#include <map>
#include <json/json.h>

using namespace drogon::orm;
using namespace drogon;
using namespace std;
using namespace drogon;
using namespace Json;

class loginFilter : public HttpFilter<loginFilter> {
private:
    bool is_valid = false;
    unsigned char uuid[100];
    char uuid_str[200];


public:
    loginFilter() {}

    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

