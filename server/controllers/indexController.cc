#include "indexController.h"

void indexController::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                             std::function<void(const HttpResponsePtr &)> &&callback) {
    //write your application logic here

    auto resp = HttpResponse::newHttpResponse();
    callback(resp);
}