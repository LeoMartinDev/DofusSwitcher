//
// Created by leoma on 09/03/2018.
//

#ifndef NODEJSNATIVEADDON_GETCURRENTPROCESSWORKER_H
#define NODEJSNATIVEADDON_GETCURRENTPROCESSWORKER_H

#include "nan.h"
#include <nan.h>
#include <v8.h>
#include "Helpers.h"
#include "Process.h"

#pragma managed;

class GetCurrentProcessWorker : public Nan::AsyncWorker {
public:
    GetCurrentProcessWorker(Nan::Callback *callback);
    ~GetCurrentProcessWorker();

    void Execute();
    void HandleOKCallback();

private:
    v8::Local<v8::Object> _result;
    v8::Local <v8::Function> _constructor;
};

#endif //NODEJSNATIVEADDON_GETCURRENTPROCESSWORKER_H
