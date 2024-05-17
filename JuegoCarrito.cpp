#include <iostream>
#include <windows.h>
#include <conio.h>

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77


using namespace std;

// Constantes para el tamano de la terminal
const int filas_terminal = 50;
const int columnas_terminal = 100;

// Constante para dibujar el carrito
const char carro = 254;



// Funcion para definir la altura y ancho de la terminal
void definir_tamano_terminal() {
#ifdef _WIN32
    // Obtener el handle de la ventana de la consola
    HWND consoleWindow = GetConsoleWindow();

    // Obtener información del buffer de pantalla
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBufferInfo);

    // Establecer el tamano de la ventana
    SMALL_RECT windowSize = { 0, 0, columnas_terminal - 1, filas_terminal - 1 }; //  filas: 50, columnas: 100 
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
#else
    // Establecer el tamano de la ventana a 50x100
    printf("\033[8;50;100t");
#endif
}

// Funcion para definir la posicion del cursor
void definir_posicion_cursor(int x, int y) {
#ifdef _WIN32
    // Obtener el handle de la ventana de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Establecer la posición del cursor en (x, y)
    COORD coord = { x - 1, y - 1 };
    SetConsoleCursorPosition(hConsole, coord);
#else
    // Establecer la posición del cursor en (x, y)
    printf("\033[%d;%dH", y, x);
#endif
}

// Funcion para dormir la terminal, le insertar como parametro el tiempo en milisec
void dormir_terminal(int milisegundos) {
#ifdef _WIN32
    Sleep(milisegundos);
#else
    usleep(milisegundos * 1000);
#endif
}

// Funcion para limpiar pantalla en linux o window o ios
void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


// Funcion mover el carrito
void moverCarritoArriba(int& x, int& y) {

    if (y > 1) {
        definir_posicion_cursor(x, y);
        cout << " ";

        y--;

        definir_posicion_cursor(x, y);
        cout << carro;
    }

}

void moverCarritoAbajo(int& x, int& y) {

    if (y < 50) {
        definir_posicion_cursor(x, y);
        cout << " ";

        y++;

        definir_posicion_cursor(x, y);
        cout << carro;
    }

}


int main() {
    definir_tamano_terminal();
    limpiar_pantalla();

    int tecla_presionada = 0;

    // posicion inicial carro
    int x = 1;
    int y = 25;

    // Ubicamos el carrito en el medio de la consola
    definir_posicion_cursor(x, y);
    cout << carro;

    // posicion inicial bala
    int x_bala[3] = { 0, 0, 0 };
    int y_bala[3] = { 0, 0, 0 };

    int i = 0;
    int j = 1;
    int k = 2;
    int contador = 1;   // contador = 1 estamos en i; si contador=2 estamos en j; si contador=3 estamos en k;

    // canbiador de direccion del disparo
    int direccion1 = true;   // true : va hacia la derecha; false: va hacia la izquierda
    int direccion2 = true;
    int direccion3 = true;

    while (true) {

        // Capturamos la tecla presionada
        if (_kbhit()) {
            tecla_presionada = _getch();

            if (tecla_presionada == 112) {
                if (contador == 1) {
                    x_bala[i] = x + 1;
                    y_bala[i] = y;

                    contador++;
                }
                else if (contador == 2) {
                    x_bala[j] = x + 1;
                    y_bala[j] = y;

                    contador++;
                }
                else if (contador == 3) {
                    x_bala[k] = x + 1;
                    y_bala[k] = y;
                }

            }
            else {
                tecla_presionada = _getch();
            }


        }

        if (tecla_presionada == ARRIBA) {
            moverCarritoArriba(x, y);

            tecla_presionada = 0;
        }

        if (tecla_presionada == ABAJO) {
            moverCarritoAbajo(x, y);

            tecla_presionada = 0;
        }

        // proyectil logica
        if (x_bala[i] != 0) {
            definir_posicion_cursor(x_bala[i], y_bala[i]);
            cout << "*";

            if (x_bala[i] >= 1 && x_bala[i] <= 100) {
                if (direccion1 == true) {
                    x_bala[i]++;

                    if (x_bala[i] == 99) {
                        direccion1 = false;
                    }
                }
                else if (direccion1 == false) {
                    x_bala[i]--;

                    if (x_bala[i] == 1) {
                        direccion1 = true;
                    }
                }
            }

        }

        if (x_bala[j] != 0) {
            definir_posicion_cursor(x_bala[j], y_bala[j]);
            cout << "*";

            if (x_bala[j] >= 1 && x_bala[j] <= 100) {
                if (direccion2 == true) {
                    x_bala[j]++;

                    if (x_bala[j] == 99) {
                        direccion2 = false;
                    }
                }
                else if (direccion2 == false) {
                    x_bala[j]--;

                    if (x_bala[j] == 1) {
                        direccion2 = true;
                    }
                }
            }
        }

        if (x_bala[k] != 0) {
            definir_posicion_cursor(x_bala[k], y_bala[k]);
            cout << "*";

            if (x_bala[k] >= 1 && x_bala[k] <= 100) {
                if (direccion3 == true) {
                    x_bala[k]++;

                    if (x_bala[k] == 99) {
                        direccion3 = false;
                    }
                }
                else if (direccion3 == false) {
                    x_bala[k]--;

                    if (x_bala[k] == 1) {
                        direccion3 = true;
                    }
                }
            }
        }

        dormir_terminal(50);

        if (x_bala[i] != 0) {

            if (direccion1 == true) {
                definir_posicion_cursor(x_bala[i] - 1, y_bala[i]);
                cout << " ";
            }
            else if (direccion1 == false) {
                definir_posicion_cursor(x_bala[i] + 1, y_bala[i]);
                cout << " ";
            }

        }

        if (x_bala[j] != 0) {
            if (direccion2 == true) {
                definir_posicion_cursor(x_bala[j] - 1, y_bala[j]);
                cout << " ";
            }
            else if (direccion2 == false) {
                definir_posicion_cursor(x_bala[j] + 1, y_bala[j]);
                cout << " ";
            }
        }

        if (x_bala[k] != 0) {
            if (direccion3 == true) {
                definir_posicion_cursor(x_bala[k] - 1, y_bala[k]);
                cout << " ";
            }
            else if (direccion3 == false) {
                definir_posicion_cursor(x_bala[k] + 1, y_bala[k]);
                cout << " ";
            }
        }

        if ((x == x_bala[i] && y == y_bala[i]) || (x == x_bala[j] && y == y_bala[j]) || (x == x_bala[j] && y == y_bala[j])) {
            return  0;
        }

    }




    return 0;
}