//
// Created by leoma on 02/03/2018.
//

#ifndef NODEJSNATIVEADDON_PROCESSHELPER_H
#define NODEJSNATIVEADDON_PROCESSHELPER_H

#include "Process.h"

#include <iterator>
#include <vector>
#include <string>
#include <iostream>

#using <mscorlib.dll>
#using <System.dll>

using namespace System;

#pragma managed

namespace Helpers {
/*    AukSwitcher::Process* GetCurrentProcess();*/
    /*std::vector<int> GetProcesses();*/
    std::vector<int> GetProcessesByName(const std::string&);
    int GetCurrentProcess();
}

#endif //NODEJSNATIVEADDON_PROCESSHELPER_H
