#include <iostream>

using namespace std;

// Constantes para el tamano de la terminal
const int filas_terminal = 50;
const int columnas_terminal = 100;

// Constante para dibujar el carrito
const char carro = 254;

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <stdio.h>

    extern "C" {
        #include <ncurses.h>
    }

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

    #ifdef __linux__
        // configuracion para videjuego con la libreria ncurses
        initscr();  // inicializa ncurses
        noecho();   // hace que no se muestre lo que se escribe
        cbreak();   // desabilita el buffer de linea
    #endif

    int palabra = getch();

    cout<<"Escribe: "<<palabra<<endl;

	
	#ifdef __linux__
        endwin(); // finaliza ncurses
    #endif

    return 0;
}