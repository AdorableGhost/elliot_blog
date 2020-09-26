#include <drogon/drogon.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    //Set HTTP listener address and port
//    drogon::app().addListener("0.0.0.0", 1995);
    //Load config file
    drogon::app().loadConfigFile("config.json");
//    drogon::app().loadConfigFile("./config.json");
    std::cout << "开始运行了:" << std::endl;
    std::cout << "运行在:" << (drogon::app().getCustomConfig())["listeners"]["port"].asString() << std::endl;

    //Run HTTP framework,the method will block in the internal event loop


    drogon::app().run();


    return 0;
}
