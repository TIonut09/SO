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

    // IMPLEMENTARE PENTRU WINDOWS

    if (argc == 2) {
        int timpAsteptare = std::stoi(argv[1]);
        std::cout << "Proces copil (Windows) asteapta " << timpAsteptare << " secunde...\n";
        Sleep(timpAsteptare * 1000);
        return 0;
    }

    HANDLE proceseCopil[3];

    for (int i = 1; i <= 3; ++i) {
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::string comanda = std::string(argv[0]) + " " + std::to_string(i);

        CreateProcessA(NULL, &comanda[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

        proceseCopil[i - 1] = pi.hProcess;
        CloseHandle(pi.hThread);        
    }

    WaitForMultipleObjects(3, proceseCopil, TRUE, INFINITE);

#else

    // IMPLEMENTARE PENTRU LINUX

    for (int i = 1; i <= 3; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
            std::cout << "Proces copil (Linux) asteapta " << i << " secunde...\n";
            sleep(i);
            return 0; 
        }
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
#endif

    std::cout << "\nToate procesele au terminat executia!\n";

    return 0;
}
