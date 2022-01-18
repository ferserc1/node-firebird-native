
#include "fbtest.h"
#include "ibpp/ibpp.h"
#include <iostream>

std::string runSimpleTest(
    const std::string & host, 
    const std::string & dbPath, 
    const std::string & user, 
    const std::string & pass,
    const std::string & query
) {
    std::string result = "Error";

    try {
        IBPP::Database db = IBPP::DatabaseFactory(host.c_str(), dbPath.c_str(), user.c_str(), pass.c_str());
        db->Connect();

        IBPP::Transaction tr1 = IBPP::TransactionFactory(
            db,
            IBPP::amWrite, IBPP::ilConcurrency, IBPP::lrWait);
        
        tr1->Start();

        IBPP::Statement st1 = IBPP::StatementFactory(db, tr1);

        

        st1->Prepare(query.c_str());
        st1->Execute();
        result = "";
        while (st1->Fetch()) {
            int id;
            std::string name;
            std::string lastname;
            st1->Get(1,id);
            st1->Get(2,name);
            st1->Get(3,lastname);
            result += std::to_string(id) + " - " + name + " " + lastname + "\n";
        }

        tr1->Commit();

        db->Disconnect();
    }
    catch(IBPP::Exception& e) {
        std::cout << e.ErrorMessage() << std::endl;
    }
    return result;
}

Napi::String RunSimpleTestWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length()<4 ||
        !info[0].IsString() ||
        !info[1].IsString() ||
        !info[2].IsString() ||
        !info[3].IsString())
    {
        Napi::TypeError::New(env, "Unexpected parameters. Four strings required (host, db, user, pass)").ThrowAsJavaScriptException();
    }

    Napi::String host = info[0].As<Napi::String>();
    Napi::String db = info[1].As<Napi::String>();
    Napi::String user = info[2].As<Napi::String>();
    Napi::String pass = info[3].As<Napi::String>();
    Napi::String query = info[4].As<Napi::String>();

    Napi::String returnValue = Napi::String::New(env, runSimpleTest(
        host.Utf8Value(), 
        db.Utf8Value(), 
        user.Utf8Value(), 
        pass.Utf8Value(),
        query.Utf8Value()));
    return returnValue;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        "runSimpleTest", Napi::Function::New(env, RunSimpleTestWrapped)
    );
    return exports;
}
