#include "GetCurrentProcessWorker.h"

GetCurrentProcessWorker::GetCurrentProcessWorker(Nan::Callback *callback)
        : AsyncWorker(callback) {};

GetCurrentProcessWorker::~GetCurrentProcessWorker() {};

void GetCurrentProcessWorker::Execute() {
    this->_process = Helpers::GetCurrentProcess();
};

void GetCurrentProcessWorker::HandleOKCallback() {
    v8::Local <v8::Function> cons = Nan::New(Process::constructor);
    Helpers::RawProcess value = this->_process;
    v8::Local <v8::Value> consArgv[4] =
    {
         Nan::New(value.handle),
         Nan::New(value.id),
         Nan::New(value.mainWindowTitle.c_str()).ToLocalChecked(),
         Nan::New(value.mainWindowHandle)
     };
    v8::Local<v8::Object> instance = Nan::NewInstance(cons, 4, consArgv).ToLocalChecked();
    v8::Local <v8::Value> argv[2] =
    {
        Nan::Null(),
        instance,
    };
    this->callback->Call(2, argv);
};