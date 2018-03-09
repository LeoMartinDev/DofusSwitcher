#include "GetCurrentProcessWorker.h"

GetCurrentProcessWorker::GetCurrentProcessWorker(Nan::Callback *callback): AsyncWorker(callback) {};
GetCurrentProcessWorker::~GetCurrentProcessWorker() {};

void GetCurrentProcessWorker::Execute() {
    this->r = 5;
/*    v8::Local <v8::Function> cons = Nan::New(Process::constructor());
    Helpers::RawProcess value = Helpers::GetCurrentProcess();
    const int argc = 4;
    v8::Local <v8::Value> argv[argc] = {Nan::New(value.handle), Nan::New(value.id),
                                        Nan::New(value.mainWindowTitle.c_str()).ToLocalChecked(),
                                        Nan::New(value.mainWindowHandle)};

    _result = Nan::NewInstance(cons, argc, argv).ToLocalChecked();*/
};

void GetCurrentProcessWorker::HandleOKCallback() {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[2] = {
            Nan::Null(),
            Nan::New(this->r),
    };
    this->callback->Call(2, argv);
};