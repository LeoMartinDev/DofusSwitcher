#include "GetCurrentProcessWorker.h"

GetCurrentProcessWorker::GetCurrentProcessWorker(Nan::Callback *callback)
        : AsyncWorker(callback)/*, _constructor(constructor)*/ {};

GetCurrentProcessWorker::~GetCurrentProcessWorker() {};

void GetCurrentProcessWorker::Execute() {
/*    v8::Local <v8::Function> cons = Nan::New(_constructor);
    Helpers::RawProcess value = Helpers::GetCurrentProcess();
    const int argc = 4;
    v8::Local <v8::Value> argv[argc] = {Nan::New(value.handle), Nan::New(value.id),
                                        Nan::New(value.mainWindowTitle.c_str()).ToLocalChecked(),
                                        Nan::New(value.mainWindowHandle)};

    this->_result = Nan::NewInstance(cons, argc, argv).ToLocalChecked();*/
};

void GetCurrentProcessWorker::HandleOKCallback() {
    v8::Local <v8::Value> argv[2] = {
            Nan::Null(),
            Nan::Null(),
    };/*    v8::Local <v8::Value> argv[2] = {
            Nan::Null(),
            this->_result,
    };*/

    this->callback->Call(2, argv);
};