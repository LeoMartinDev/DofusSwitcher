#include <nan.h>
#include <node.h>
#include <v8.h>
#include "nan.h"
//#include "ProcessHelper.h";

#using <mscorlib.dll>

#include <iterator>
#include <vector>

#using <System.dll>
using namespace System;

#pragma managed

namespace AukSwitcher {

    // NAN_METHOD is a Nan macro enabling convenient way of creating native node functions.
// It takes a method's name as a param. By C++ convention, I used the Capital cased name.
/*    NAN_METHOD(GetProcesses) {
*//*        std::vector<double> vec = { 5, 6, 7 };
        v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
        for (int i = 0; i < jsArr->Length(); i++) {
            double number = vec.at(i);
            v8::Local<v8::Value> jsElement = Nan::New(number);
            jsArr->Set(i, jsElement);
        }
        info.GetReturnValue().Set(jsArr);*//*
        std::vector<int> processes = Helpers::GetProcesses();
        v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(processes.size());

        for (int i = 0; i < jsArr->Length(); i++) {
            int number = processes.at(i);
            v8::Local<v8::Value> jsElement = Nan::New(number);
            jsArr->Set(i, jsElement);
        }
        info.GetReturnValue().Set(jsArr);
    };*/

    std::vector<int> GetP() {
        array < Diagnostics::Process ^>^processesArray = Diagnostics::Process::GetProcessesByName("Dofus");
        std::vector<int> test = std::vector<int>();

        for (unsigned int i = 0; i <= sizeof(&processesArray) / sizeof(Diagnostics::Process^); i++)
        {
            System::Console::WriteLine(processesArray[i]->MainWindowTitle);
            test.push_back(processesArray[i]->Id);
        }
        System::Console::WriteLine(test.size());
        return test;
    }

    int GetAll() {
        array < Diagnostics::Process ^>^processesArray = Diagnostics::Process::GetProcesses();
        std::vector<int> test;

        for (unsigned int i = 0; i < sizeof(processesArray) / sizeof(processesArray[0]); i++)
        {
            test.push_back(processesArray[i]->Id);
        }
        return test.at(0);
    }

#pragma unmanaged

    NAN_METHOD(GetProcesses) {
        std::vector<int> processes = GetP();
        v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(processes.size());
        for (int i = 0; i < processes.size(); i++) {
            int number = processes.at(i);
            v8::Local<v8::Value> jsElement = Nan::New(number);
            jsArr->Set(i, jsElement);
        }
        info.GetReturnValue().Set(jsArr);
/*        int processes = GetAll();
        info.GetReturnValue().Set(processes);*/
    }
/*    NAN_METHOD(GetProcesses) {
*//*        std::vector<double> vec = { 5, 6, 7 };
        v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
        for (int i = 0; i < jsArr->Length(); i++) {
            double number = vec.at(i);
            v8::Local<v8::Value> jsElement = Nan::New(number);
            jsArr->Set(i, jsElement);
        }
        info.GetReturnValue().Set(jsArr);*//*
        array<int>^ processes = Helpers::GetProcesses();
        v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(processes.size());

        for (int i = 0; i < jsArr->Length(); i++) {
            int number = processes[i];
            v8::Local<v8::Value> jsElement = Nan::New(number);
            jsArr->Set(i, jsElement);
        }
        info.GetReturnValue().Set(jsArr);
    };*/

// Module initialization logic
    NAN_MODULE_INIT(Initialize) {
        // Export the `Hello` function (equivalent to `export function Hello (...)` in JS)
        NAN_EXPORT(target, GetProcesses);
    };

// Create the module called "addon" and initialize it with `Initialize` function (created with NAN_MODULE_INIT macro)
    NODE_MODULE(addon, Initialize);
}
