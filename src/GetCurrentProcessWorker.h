//
// Created by leoma on 09/03/2018.
//

#ifndef NODEJSNATIVEADDON_GETCURRENTPROCESSWORKER_H
#define NODEJSNATIVEADDON_GETCURRENTPROCESSWORKER_H

#include "nan.h"
#include <v8.h>
#include "Helpers.h"
#include "Process.h"

#pragma unmanaged;

class GetCurrentProcessWorker : public Nan::AsyncWorker {
public:
    int r;
    GetCurrentProcessWorker(Nan::Callback *callback);
    ~GetCurrentProcessWorker();

    void Execute();
    void HandleOKCallback();
};

#endif //NODEJSNATIVEADDON_GETCURRENTPROCESSWORKER_H
