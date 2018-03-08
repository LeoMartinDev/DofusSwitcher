//#include "nan.h"
#include <nan.h>
#include <v8.h>
#include <map>
#include <msclr\marshal_cppstd.h>
#include <windows.h>

#pragma unmanaged
#using <mscorlib.dll>
#using <System.dll>

using namespace System;

#pragma managed

namespace Helpers {

    struct RawProcess {
        int handle;
        int id;
        std::string mainWindowTitle;
        int mainWindowHandle;
    };

    std::vector <RawProcess> GetProcessesByName(const std::string &name) {
        String ^ processName = gcnew String(name.c_str());
        array < Diagnostics::Process ^>^processesArray = Diagnostics::Process::GetProcessesByName(processName);
        std::vector <RawProcess> processesVector = std::vector<RawProcess>();

        for (unsigned int i = 0; i <= sizeof(&processesArray) / sizeof(Diagnostics::Process ^ ); i++) {
            System::Console::WriteLine(processesArray[i]->MainWindowTitle);
            std::string mainWindowTitle = msclr::interop::marshal_as<std::string>(processesArray[i]->MainWindowTitle);
            RawProcess result = {
                    processesArray[i]->Handle.ToInt32(),
                    processesArray[i]->Id,
                    mainWindowTitle,
                    processesArray[i]->MainWindowHandle.ToInt32(),
            };
            processesVector.push_back(result);
        }
        System::Console::WriteLine(processesVector.size());
        return processesVector;
    }

    RawProcess GetCurrentProcess() {
        Diagnostics::Process ^currentProcess = Diagnostics::Process::GetCurrentProcess();
        std::string mainWindowTitle = msclr::interop::marshal_as<std::string>(currentProcess->MainWindowTitle);
        RawProcess result = {
                currentProcess->Handle.ToInt32(),
                currentProcess->Id,
                mainWindowTitle,
                currentProcess->MainWindowHandle.ToInt32(),
        };
        System::Console::Write(currentProcess->MainWindowTitle);
        return result;
    }
}

#pragma unmanaged

class Process : public Nan::ObjectWrap {

public:
    static NAN_MODULE_INIT(Init) {
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

    static NAN_METHOD(GetCurrent) {
        v8::Local <v8::Function> cons = Nan::New(constructor());
        Helpers::RawProcess value = Helpers::GetCurrentProcess();
        const int argc = 4;
        v8::Local <v8::Value> argv[argc] = {Nan::New(value.handle), Nan::New(value.id),
                                            Nan::New(value.mainWindowTitle.c_str()).ToLocalChecked(),
                                            Nan::New(value.mainWindowHandle)};
        info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    };

    static NAN_METHOD(GetByName) {
        v8::Local <v8::Function> cons = Nan::New(constructor());
        v8::String::Utf8Value processName(info[0]);
        std::vector <Helpers::RawProcess> value = Helpers::GetProcessesByName(std::string(*processName));
        v8::Local <v8::Array> jsProcessesArray = Nan::New<v8::Array>(value.size());

        for (unsigned int i = 0; i < jsProcessesArray->Length(); i++) {
            const int argc = 4;
            v8::Local <v8::Value> argv[argc] = {Nan::New(value.at(i).handle), Nan::New(value.at(i).id),
                                                Nan::New(value.at(i).mainWindowTitle.c_str()).ToLocalChecked(),
                                                Nan::New(value.at(i).mainWindowHandle)};
            v8::Local <v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();

            jsProcessesArray->Set(i, instance);
        }
        info.GetReturnValue().Set(jsProcessesArray);
    };

    static NAN_GETTER(HandleGetters) {
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

    inline int handle() const {
        return _handle;
    }

    inline int id() const {
        return _id;
    }

    inline std::string mainWindowTitle() const {
        return _mainWindowTitle;
    }

    inline int mainWindowHandle() const {
        return _mainWindowHandle;
    }

private:
    explicit Process(int handle, int id, std::string mainWindowTitle, int mainWindowHandle) : _handle(handle), _id(id),
                                                                                              _mainWindowTitle(
                                                                                                      mainWindowTitle),
                                                                                              _mainWindowHandle(
                                                                                                      mainWindowHandle) {}

    ~Process() {}

    static NAN_METHOD(New) {
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

    static NAN_METHOD(setToForeground) {
        Process *obj = Nan::ObjectWrap::Unwrap<Process>(info.Holder());

        SetForegroundWindow((HWND) obj->_mainWindowHandle);
    };

    static inline Nan::Persistent<v8::Function> &constructor() {
        static Nan::Persistent<v8::Function> construct;
        return construct;
    };

    int _handle;
    int _id;
    std::string _mainWindowTitle;
    int _mainWindowHandle;
};


NAN_MODULE_INIT(Init) {
    Process::Init(target);
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

NODE_MODULE(ProcessFactory, Init)
