#include "ProcessHelper.h"

namespace Helpers {
    int GetCurrentProcess() {
        Diagnostics::Process ^currentProcess = Diagnostics::Process::GetCurrentProcess();

        return currentProcess->Id;
    }

    std::vector<int> GetProcessesByName(const std::string& name) {
        String^ processName = gcnew String(name.c_str());
        array < Diagnostics::Process ^>^processesArray = Diagnostics::Process::GetProcessesByName(processName);
        std::vector<int> test = std::vector<int>();

        for (unsigned int i = 0; i <= sizeof(&processesArray) / sizeof(Diagnostics::Process^); i++)
        {
            System::Console::WriteLine(processesArray[i]->MainWindowTitle);
            test.push_back(processesArray[i]->Id);
        }
        System::Console::WriteLine(test.size());
        return test;
    }
}