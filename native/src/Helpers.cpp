#include "Helpers.h"

namespace Helpers {

    std::vector <RawProcess> GetProcessesByName(const std::string &name) {
        String ^ processName = gcnew String(name.c_str());
        array < Diagnostics::Process ^>^processesArray = Diagnostics::Process::GetProcessesByName(processName);
        std::vector <RawProcess> processesVector = std::vector<RawProcess>();

        for (unsigned int i = 0; i < processesArray->Length; i++) {
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

    RawProcess GetProcessById(const int id) {
        try {
            Diagnostics::Process ^currentProcess = Diagnostics::Process::GetProcessById(id);

            std::string mainWindowTitle = msclr::interop::marshal_as<std::string>(currentProcess->MainWindowTitle);
            RawProcess result = {
                    currentProcess->Handle.ToInt32(),
                    currentProcess->Id,
                    mainWindowTitle,
                    currentProcess->MainWindowHandle.ToInt32(),
            };
            return result;
        } catch (ArgumentException^error) {
            throw std::invalid_argument("Cannot find process for id " + std::to_string(id));
        }
    }
}//
// Created by leoma on 09/03/2018.
//

