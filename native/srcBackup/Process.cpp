#include "Process.h"

NAN_MODULE_INIT(Process::Init) {
    v8::Local <v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "setToForeground", setToForeground);

    Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New("handle").ToLocalChecked(), Process::HandleGetters);
    Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New("id").ToLocalChecked(), Process::HandleGetters);
    Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New("mainWindowTitle").ToLocalChecked(), Process::HandleGetters,
                     nullptr);
    Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New("mainWindowHandle").ToLocalChecked(), Process::HandleGetters,
                     nullptr);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
};

NAN_METHOD(Process::GetCurrent) {
    v8::Local <v8::Function> cons = Nan::New(constructor());
    Helpers::RawProcess value = Helpers::GetCurrentProcess();
    const int argc = 4;
    v8::Local <v8::Value> argv[argc] = {Nan::New(value.handle), Nan::New(value.id),
                                        Nan::New(value.mainWindowTitle.c_str()).ToLocalChecked(),
                                        Nan::New(value.mainWindowHandle)};

    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
};

NAN_METHOD(Process::GetByName) {
    if (!info[0]->IsString()) {
        return Nan::ThrowError(Nan::New("Process::GetByName - name must be a string!").ToLocalChecked());
    }
    v8::Local <v8::Function> cons = Nan::New(constructor());
    v8::String::Utf8Value processName(info[0]);
    std::vector <Helpers::RawProcess> value = Helpers::GetProcessesByName(std::string(*processName));
    v8::Local <v8::Array> jsProcessesArray = Nan::New<v8::Array>(value.size());

    for (unsigned int i = 0; i < jsProcessesArray->Length(); i++) {
        const int argc = 4;
        v8::Local <v8::Value> argv[argc] = {Nan::New(value.at(i).handle), Nan::New(value.at(i).id),
                                            Nan::New(value.at(i).mainWindowTitle.c_str()).ToLocalChecked(),
                                            Nan::New(value.at(i).mainWindowHandle)};
        v8::Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();

        jsProcessesArray->Set(i, instance);
    }
    info.GetReturnValue().Set(jsProcessesArray);
};

NAN_METHOD(Process::GetById) {
    if (!info[0]->IsNumber()) {
        return Nan::ThrowError(Nan::New("Process::GetById - id must be a number!").ToLocalChecked());
    }
    v8::Local <v8::Function> cons = Nan::New(constructor());
    int id = info[0]->NumberValue();
    try {
        Helpers::RawProcess value = Helpers::GetProcessById(id);
        const int argc = 4;
        v8::Local <v8::Value> argv[argc] = {Nan::New(value.handle), Nan::New(value.id),
                                            Nan::New(value.mainWindowTitle.c_str()).ToLocalChecked(),
                                            Nan::New(value.mainWindowHandle)};

        info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
    catch (const std::invalid_argument &e) {
        info.GetReturnValue().Set(Nan::Undefined());
    }
};

NAN_METHOD(Process::GetCurrentAsync) {
    if(!info[0]->IsFunction()) {
        return Nan::ThrowError(Nan::New("expected arg 1: function callback").ToLocalChecked());
    }
    v8::Local <v8::Function> cons = Nan::New(constructor());

    Nan::AsyncQueueWorker(new GetCurrentProcessWorker(
            new Nan::Callback(info[0].As<v8::Function>()),
            cons
    ));
};


NAN_GETTER(Process::HandleGetters) {
    Process *self = Nan::ObjectWrap::Unwrap<Process>(info.This());

    std::string propertyName = std::string(*Nan::Utf8String(property));
    if (propertyName == "handle") {
        info.GetReturnValue().Set(self->handle());
    } else if (propertyName == "id") {
        info.GetReturnValue().Set(self->id());
    } else if (propertyName == "mainWindowTitle") {
        info.GetReturnValue().Set(Nan::New(self->mainWindowTitle().c_str()).ToLocalChecked());
    } else if (propertyName == "mainWindowHandle") {
        info.GetReturnValue().Set(self->mainWindowHandle());
    } else {
        info.GetReturnValue().Set(Nan::Undefined());
    }
};

int Process::handle() const {
    return _handle;
}

int Process::id() const {
    return _id;
}

std::string Process::mainWindowTitle() const {
    return _mainWindowTitle;
}

int Process::mainWindowHandle() const {
    return _mainWindowHandle;
}

Nan::Persistent<v8::Function> &Process::constructor() {
    static Nan::Persistent<v8::Function> construct;
    return construct;
};

Process::Process(int handle, int id, std::string mainWindowTitle, int mainWindowHandle) : _handle(handle), _id(id),
                                                                                          _mainWindowTitle(
                                                                                                  mainWindowTitle),
                                                                                          _mainWindowHandle(
                                                                                                  mainWindowHandle) {}

Process::~Process() {};

NAN_METHOD(Process::New) {
    if (info.IsConstructCall()) {
        int handle = Nan::To<int>(info[0]).FromJust();
        int value = Nan::To<int>(info[1]).FromJust();
        v8::String::Utf8Value mainWindowTitle(info[2]->ToString());
        int mainWindowHandle = Nan::To<int>(info[3]).FromJust();

        Process *obj = new Process(handle, value, *mainWindowTitle, mainWindowHandle);
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        const int argc = 4;

        v8::Local <v8::Value> argv[argc] = {info[0], info[1], info[2], info[3]};
        v8::Local <v8::Function> cons = Nan::New(constructor());
        info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
};

NAN_METHOD(Process::setToForeground) {
    Process *obj = Nan::ObjectWrap::Unwrap<Process>(info.Holder());

    SetForegroundWindow((HWND) obj->_mainWindowHandle);
};

NAN_MODULE_INIT(Init) {
    Process::Init(target);
    Nan::Set(target,
             Nan::New<v8::String>("getProcessById").ToLocalChecked(),
             Nan::GetFunction(
                     Nan::New<v8::FunctionTemplate>(Process::GetById)).ToLocalChecked()
    );
    Nan::Set(target,
             Nan::New<v8::String>("getCurrentProcessAsync").ToLocalChecked(),
             Nan::GetFunction(
                     Nan::New<v8::FunctionTemplate>(Process::GetCurrentAsync)).ToLocalChecked()
    );
    Nan::Set(target,
             Nan::New<v8::String>("getCurrentProcess").ToLocalChecked(),
             Nan::GetFunction(
                     Nan::New<v8::FunctionTemplate>(Process::GetCurrent)).ToLocalChecked()
    );
    Nan::Set(target,
             Nan::New<v8::String>("getProcessesByName").ToLocalChecked(),
             Nan::GetFunction(
                     Nan::New<v8::FunctionTemplate>(Process::GetByName)).ToLocalChecked()
    );
}

NODE_MODULE(addon, Init)
