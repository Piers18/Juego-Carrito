#include <iostream>

using namespace std;

int const filas_terminal = 50;
int const columnas_terminal = 100;

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <stdio.h>
#endif

// Funcion para definir la altura y ancho de la terminal
void definir_tamano_terminal(){
    #ifdef _WIN32
        // Obtener el handle de la ventana de la consola
        HWND consoleWindow = GetConsoleWindow();

        // Obtener información del buffer de pantalla
        CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBufferInfo);

        // Establecer el tamano de la ventana
        SMALL_RECT windowSize = {0, 0, columnas_terminal-1, filas_terminal-1}; //  filas: 50, columnas: 100 
        SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    #else
        // Establecer el tamano de la ventana a 50x100
        printf("\033[8;50;100t");
    #endif
}

// Funcion para definir la posicion del cursor
void definir_posicion_cursor(int x, int y){
    #ifdef _WIN32
        // Obtener el handle de la ventana de la consola
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Establecer la posición del cursor en (x, y)
        COORD coord = {x-1, y-1};
        SetConsoleCursorPosition(hConsole, coord);
    #else
        // Establecer la posición del cursor en (x, y)
        printf("\033[%d;%dH", y, x);
    #endif
}

// Funcion para dormir la terminal, le insertar como parametro el tiempo en milisec
void dormir_terminal(int milisegundos){
    #ifdef _WIN32
        Sleep(milisegundos);
    #else
        usleep(milisegundos * 1000);
    #endif
}

// Funcion para limpiar pantalla en linux o window o ios
void limpiar_pantalla(){
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
}

int main(){
    definir_tamano_terminal();

    char carro = 254;
	
	cout<<carro<<endl;

    return 0;
}