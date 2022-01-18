#include <napi.h>
#include <string>

std::string runSimpleTest(
    const std::string & host, 
    const std::string & dbPath, 
    const std::string & user, 
    const std::string & pass,
    const std::string & query);
Napi::String RunSimpleTestWrapped(const Napi::CallbackInfo& info);
Napi::Object Init(Napi::Env env, Napi::Object exports);
