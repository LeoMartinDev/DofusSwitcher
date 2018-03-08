//
// Created by leoma on 02/03/2018.
//

#ifndef NODEJSNATIVEADDON_PROCESS_H
#define NODEJSNATIVEADDON_PROCESS_H

#include <nan.h>
#include "nan.h"

#pragma unmanaged
#using <mscorlib.dll>
#using <System.dll>

using namespace System;
#pragma managed
namespace AukSwitcher {

    class Process: public Nan::ObjectWrap {

    public:
        static Nan::Persistent<v8::FunctionTemplate> constructor;

        static NAN_MODULE_INIT(Init);

        /*static v8::Local<v8::Object> Factory();*/

        static NAN_GETTER(HandleGetters);

        static NAN_METHOD(New);

    private:
        explicit Process(IntPtr handle);
        ~Process();

        int id = 50;
        IntPtr handle;
    };
}

#endif //NODEJSNATIVEADDON_PROCESS_H
