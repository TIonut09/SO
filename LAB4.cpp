#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
    // VARIANTA PENTRU WINDOWS
    if (argc == 2) {
        int waitTime = std::stoi(argv[1]);
        std::cout << "Proces " << waitTime << " (Windows) asteapta " << waitTime << " secunde...\n";
        Sleep(waitTime * 1000);
        return 0; 
    }
    HANDLE processes[3];

    for (int i = 1; i <= 3; ++i) {
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::string cmd = std::string(argv[0]) + " " + std::to_string(i);

        if (CreateProcessA(NULL, &cmd[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            processes[i - 1] = pi.hProcess;
            CloseHandle(pi.hThread);
        }
    }
    WaitForMultipleObjects(3, processes, TRUE, INFINITE);

    for (int i = 0; i < 3; ++i) {
        CloseHandle(processes[i]);
    }

#else
    // VARIANTA PENTRU LINUX

    for (int i = 1; i <= 3; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
            std::cout << "Proces " << i << " (Linux) asteapta " << i << " secunde...\n";
            sleep(i); 
            return 0; 
        }
    }

    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }
#endif
    std::cout << "\nToate procesele au terminat!\n";

    return 0;
}