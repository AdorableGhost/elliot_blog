#include "loginController.h"
#include <iostream>

using namespace std;

void loginController::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                             std::function<void(const HttpResponsePtr &)> &&callback) {
    //write your application logic here
    cout << "Index Controller" << endl;
    auto resp = HttpResponse::newHttpResponse();
    callback(resp);
}