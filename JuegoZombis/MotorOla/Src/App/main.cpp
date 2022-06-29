#include <iostream>
#include <Motor.h>

#if _DEBUG
    #include "utils/checkML.h"
#endif

int __stdcall WinMain(void*, void*, char* cmdLine, int)
{
#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    std::cout << "APLICACION INICIADA\n";

    bool hayError = false;
    Motor* m = nullptr;

    // Inicia el Motor
    std::cout << "CREANDO MOTOR\n";
    try {
        m = new Motor();
    }
    catch (const char* error) {
        std::cout << "Error creando el motor:\n" << error << "\n";
        hayError = true;
    }

    // Intenta iniciar los sistemas principales
    std::cout << "INICIALIZANDO MOTOR\n";
    try {
        m->initSystems();
    }
    catch (const char* error) {
        std::cout << "Error iniciando el motor:\n" << error << "\n";
        hayError = true;
        system("pause");
    }

    // Pone en marcha el bucle principal del Motor
    std::cout << "ARRANCANDO BUCLE PPAL.\n";
    try {
        m->mainLoop();
    }
    catch (const char* error) {
        std::cout << "Error durante el bucle principal del motor:\n" << error << "\n";
        hayError = true;
        system("pause");
    }

    // Libera la memoria del Motor y los sistemas principales
    std::cout << "CERRANDO\n";
    if (m != nullptr) {
        delete m;
        m = nullptr;
    }

    return hayError;
}

/*
https://social.msdn.microsoft.com/Forums/vstudio/en-US/b8fe3dbc-f06c-430c-959b-c75af6421b2a/hiding-a-console-window-in-c?forum=vcgeneral
int main() {
}
*/
