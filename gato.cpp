#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
//colores de texto
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define WHITE   "\x1B[37m"
#define RESET   "\x1b[0m"
//Colores de fondo
#define BG_WHITE   "\x1B[47m"
#define BG_BLUE    "\x1B[44m"



struct Estadisticas {
	int partidasHumanoVsHumano;
	int partidasHumanoVsComputadora;
	int partidasGanadasHumano1;
	int partidasGanadasHumano2;
	int partidasGanadasComputadora;
	int partidasEmpatadas;
	int partidasCanceladas;
	
	Estadisticas()
		: partidasHumanoVsHumano(0),
		partidasHumanoVsComputadora(0),
		partidasGanadasHumano1(0),
		partidasGanadasHumano2(0),
		partidasGanadasComputadora(0),
		partidasEmpatadas(0),
		partidasCanceladas(0) {}
};

char tablero [3][3]= {' '};
int dificultad;//1 facil , 2 dificil
void configuracionInicial();
char getJugarDeNuevo();
char getJugador();
void menuPrincipal();
void inicializaTablero();
void imprimirTablero();
void setDificultad();
bool hayGanador(char);
bool prediceVictoria(char [3][3],char);
bool tableroLleno();
bool realizarJugada(int, int, char);
bool simulaJugada(char [3][3],int,char);
bool esGanadorProximoMovimiento(int, int, char);
void jugadaMaquinaFacil();
void movimientoMaquinaDificil() ;
void jugarHumanoVsHumano(Estadisticas& estadisticas) ;
void jugarContraMaquina(Estadisticas& estadisticas);
void mostrarEstadisticas(const Estadisticas& estadisticas);

int main() {
    configuracionInicial();
	menuPrincipal();
	return 0;
}
//establece las configuraciones iniciales del juego .
void configuracionInicial(){
	//establece que el inivel de dificultad inicial sea facil
	dificultad=1;
}
//funcion que le pregunta al usuario  que jugador va a iniciar primero , el humano o la maquina y hace validaciones de las respuestas
char getJugador(){
    system("clear");
    bool bandera;
    bandera = true;
    int opc;
    do{
        system("clear");
        cout<<"\tSelecciona que jugador inicia la partida :"<<endl;
        cout<<"\t1. Jugador 1."<<endl;
        cout<<"\t2. Computadora."<<endl;
        cin>>opc;
        if(opc>=1 && opc<=2)
        bandera=false;
        else{
            cout << RED<<BG_WHITE<<"Opción no valida" << RESET << endl;
            cin.clear();
	        cin.ignore();
	        cin.get();
        }
    }while(bandera);
    if (opc == 1)
        return 'X';
    else
        return 'O';

}
//funcion que le pregunta al usuario si desea jugar de nuevo y hace validaciones de las respuestas
char getJugarDeNuevo(){
    bool bandera;
    bandera = true;
    char opc;
    do{
        cout<<"\t¿Desea jugar otra partida? S/N"<<endl;
        cin>>opc;
        if(opc=='S'|| opc=='s'|| opc=='N' || opc=='n')
        bandera=false;
        else{
            cout << RED<<BG_WHITE<<"Opción no valida" << RESET << endl;
            cin.clear();
	        cin.ignore();
	        cin.get();
        }
    }while(bandera);
    switch (opc)
    {
    case 'N':
        opc = 'N';
        break;
    
    case 'n':
        opc = 'N';
        break;
    case 'S':
        opc = 'S';
        break;
    case 's':
        opc = 'S';
        break;
    }

   return opc;

}
//metodo que muestra el menu principal
void menuPrincipal(){
	int opcionJuego, nivelDificultad;
	Estadisticas estadisticas;
    bool bandera;
    bandera = true;
	do {
		system("clear");
		cout << WHITE <<BG_BLUE<< "\n\n\n\n\t\t\tBienvenido al Juego del Gato #" <<RESET<<endl;
		cout << "\n\n";
		cout << "\t1. Multijugador"<<endl;
		cout << "\t2. Contra la computadora"<<endl;
		cout << "\t3. Instrucciones"<<endl;
		cout << "\t4. Ver Estadisticas"<<endl;
        cout << "\t5. Configuración"<<endl;
		cout << "\t6. Salir"<<endl;
		cout << "\n\tIngrese la opcion (1, 2, 3, 4, ó 5): ";
		cin >> opcionJuego;
        switch(opcionJuego){
            case 1:
                jugarHumanoVsHumano(estadisticas);
                break;
            case 2:
                jugarContraMaquina(estadisticas);
                break;
            case 3:
			    cout << RED<<BG_WHITE<<"Aun no me desarrollan" << RESET << endl;
            	cin.clear();
	        	cin.ignore();
	        	cin.get();
                break;
            case 4:
                mostrarEstadisticas(estadisticas);
                break;
            case 5:
                setDificultad();
                break;
            case 6:
                cout<<GREEN<<BG_WHITE<<"! Hasta pronto !"<<RESET<<endl;
                bandera=false;
			    break;
            //default:
            
            
        }
	} while (bandera);
	
}
void setDificultad(){
    bool bandera;
    bandera = true;
    int opc;
    do{
        system("clear");
        cout<<"\tSelecciona la dificultad de la maquina :"<<endl;
        cout<<"\t1. Fácil."<<endl;
        cout<<"\t2. Difícil."<<endl;
        cin>>opc;
        if(opc>=1 && opc<=2)
        bandera=false;
        else{
            cout << RED<<BG_WHITE<<"Opción no valida" << RESET << endl;
            cin.clear();
	        cin.ignore();
	        cin.get();
        }
    }while(bandera);
    dificultad = opc;
    cout <<GREEN<<BG_WHITE<<"Se modificó el nivel de dificultad" << RESET << endl;
    cin.clear();
	cin.ignore();
	cin.get();
}
void imprimirTablero() {
	
	cout << " +---+---+---+\n";
	for (int i = 0; i < 3; i++) {
		cout << " | ";
		for (int j = 0; j < 3; j++) {
			cout << tablero[i][j] << " | ";
		}
		cout << "\n +---+---+---+\n";
	}
}
void inicializaTablero(){
	int cont;
	cont = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tablero[i][j] = '0'+cont;
			cont++;
		}
	}

	
}

// Función para verificar si hay un ganador
bool hayGanador(char jugador) {
    //recorre el tablero de forma horizontal 
	for (int i = 0; i < 3; i++) {
		if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
			(tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
			return true;
		}
	}
	//recorre la matriz de forma diagonal
	if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
		(tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)) {
		return true;
	}
		//no hay ganador regresa falso 
		return false;
}
bool prediceVictoria(char simulacionTablero[3][3],char jugador){
    //se le esta mandando una matriz auxiliar para validar que si ese movimiento futuro hace que gane
	for (int i = 0; i < 3; i++) {
		//verifica si gana por horizontal
		if ((simulacionTablero[i][0] == jugador && simulacionTablero[i][1] == jugador && simulacionTablero[i][2] == jugador) ||
			(simulacionTablero[0][i] == jugador && simulacionTablero[1][i] == jugador && simulacionTablero[2][i] == jugador)) {
			return true;
		}
	}
	//verifica si gana por diagonal
	if ((simulacionTablero[0][0] == jugador && simulacionTablero[1][1] == jugador && simulacionTablero[2][2] == jugador) ||
		(simulacionTablero[0][2] == jugador && simulacionTablero[1][1] == jugador && simulacionTablero[2][0] == jugador)) {
		return true;
	}
		
		return false;
	
}

// Función para verificar si el tablero está lleno
bool tableroLleno() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tablero[i][j] == '1' || tablero[i][j] == '2' || tablero[i][j] == '3' || tablero[i][j] == '4' || tablero[i][j] == '5'  || tablero[i][j] == '6'  || tablero[i][j] == '7'  || tablero[i][j] == '8'  || tablero[i][j] == '9')
				return false;
		}
	}
	return true;
}

// Función para realizar un movimiento en el tablero
bool realizarJugada(int fila, int columna, char jugador) {
	if ((tablero[fila][columna] == 'X') ||(tablero[fila][columna] == 'O')) {
		return false;  // Movimiento inválido
	}
	
	tablero[fila][columna] = jugador;
	return true;  // Movimiento válido
}

bool simulaJugada(char simulacionTablero[3][3],int fila, int columna, char jugador) {
    //hace la simulacion en una matriz o tablero auxiliar
	if ((simulacionTablero[fila][columna] == 'X') ||(simulacionTablero[fila][columna] == 'O')) {
		return false;  // Movimiento inválido
	}
	
	simulacionTablero[fila][columna] = jugador;
	return true;  // Movimiento válido
}

// Función para verificar si realizar un movimiento hará ganar al jugador
bool esGanadorProximoMovimiento(int fila, int columna, char jugador) {
	char tableroCopia[3][3];
	copy(&tablero[0][0], &tablero[0][0] + 3 * 3, &tableroCopia[0][0]);
	
	if (simulaJugada(tableroCopia, fila, columna, jugador) && prediceVictoria(tableroCopia, jugador)) {
		return true;
	}
	
	return false;
}

// Función para que la máquina en el modo fácil realice un movimiento aleatorio
void jugadaMaquinaFacil() {
	int fila, columna;
	srand(time(0)); //para generar numeros aleatorios
	do {
        //genera los numeros
		fila = rand() % 3 ;
		columna = rand() % 3 ;
        //intenta realizar la jugada en la posicion generada automaticamente
        //si la casilla esta ocupada volverá a entrar al ciclo y generar otra casilla aleatoria, hasta que se pueda realizar la jugada
	} while (!realizarJugada(fila, columna, 'O'));
}


// Función para que la máquina en el modo difícil realice un movimiento estratégico
void movimientoMaquinaDificil() {
	// Intentar ganar
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
            //valida que el tablero tenga un lugar libre
			if(tablero[i][j]=='1' || tablero[i][j] =='2'|| tablero[i][j] =='3'|| tablero[i][j] =='4'|| tablero[i][j] =='5'|| tablero[i][j] =='6'|| tablero[i][j] =='7'|| tablero[i][j] =='8'|| tablero[i][j] =='9'){
				//ese lugar libre tiene opcion de ganar ?
                if (esGanadorProximoMovimiento(i, j, 'O')) {
                    //si tiene opcion de ganar  , entonces va a realizar la jugada
					realizarJugada(i, j, 'O');
					return;
				}
			}
		}
	}
	
	// no hay opcion de ganar pues , vamos a ver si el oponente ya va ganar y si es asi bloquear su jugada
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if(tablero[i][j]=='1' || tablero[i][j] =='2'|| tablero[i][j] =='3'|| tablero[i][j] =='4'|| tablero[i][j] =='5'|| tablero[i][j] =='6'|| tablero[i][j] =='7'|| tablero[i][j] =='8'|| tablero[i][j] =='9'){
				if (esGanadorProximoMovimiento( i, j, 'X')) {
					realizarJugada( i, j, 'O');
					return;
				}
			}
		}
	}
	
	// no hay posibilidad de ganar y  tampoco no hay nada que bloquear, vamos a tirar aleatroiamente en una posicion del tablero
    //mandamos a llamar a la funcion que tira un numero aleatorio que es jugadamaquinafacil..
	jugadaMaquinaFacil();
}

// Función para jugar entre dos jugadores humanos
void jugarHumanoVsHumano(Estadisticas& estadisticas) {
   //primer ciclo que permite que se jueguen varias partidas hasta que el usuario responda N de no jugar mas
	while (true) {
        inicializaTablero();
	    int opc;
	    char jugadorActual = 'X';
        //inicia la partida
        while(true){
            system("clear");
		    imprimirTablero();
		    cout<<BLUE<<"Turno del jugador:"<<jugadorActual<<RESET<<endl;
		    cout<<"Selecciona una casilla del tablero ó 0 para cancelar partida: ";
		    cin >> opc;
		    if (opc == 0) {
		    	estadisticas.partidasCanceladas++;
                cout << GREEN <<BG_WHITE <<"! Partida Cancelada !" <<RESET;
			    cin.clear();
	            cin.ignore();
	            cin.get();
			    break;
		    }
		    while(opc < 1 || opc > 9) {
                cout << RED<<BG_WHITE<<"Número de casilla inválido." << RESET << endl;
                cout << "selecciona una casilla del tablero :";
                cin >> opc;
            }
		    int fila = (opc - 1) / 3;
		    int columna = (opc - 1) % 3;
            //una vez que se validaron las opciones de la casilla , vamos a realizar la jugada
             //si la casilla esta libre se queda la jugada, si no el jugador deberá teclear otra casilla de nuevo
		    if (!realizarJugada(fila, columna, jugadorActual)) {
			    cout << RED<<BG_WHITE<<"La casilla seleccionada ya se encuentra ocupada" << RESET << endl;
                cin.clear();
	            cin.ignore();
	            cin.get();
			    continue;
		    }
		    //valida si ya hay ganador
		    if (hayGanador(jugadorActual)) {
                //si hay ganador entonces
                system("clear");
			    imprimirTablero();
			    cout << GREEN <<BG_WHITE <<"Jugador: "<<jugadorActual<<" ¡ Has ganado !" << RESET;
			    cin.clear();
	            cin.ignore();
	            cin.get();
                //agrega las estadisticas
			    if (jugadorActual == 'X') 
				    estadisticas.partidasGanadasHumano1++;
			    else 
				estadisticas.partidasGanadasHumano2++;
			    estadisticas.partidasHumanoVsHumano++;
			    break;
                //no hay ganador aun vamos a ver si hay tablero lleno entonces es empate
		    } else if (tableroLleno()) {
                system("clear");
			    imprimirTablero();
                //modificamos las estadisticas
                estadisticas.partidasEmpatadas++;
			    estadisticas.partidasHumanoVsHumano++;
			    cout << GREEN <<BG_WHITE <<"! Es un Empate !"<<RESET;
                cin.clear();
	            cin.ignore();
	            cin.get();
			    break;
		    }
		    //cambiamos de jugador
		    jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
        }
        //ya termino la partida vamos a preguntar si quiere volver a jugar 
        if (getJugarDeNuevo()=='N')
            break;

    }   
}

//Metodo para jugar contra la máquina recibe  las estadisticas
void jugarContraMaquina(Estadisticas& estadisticas) {
    while (true){
        inicializaTablero();
	    char jugadorActual = getJugador();
        //ciclo de la partida
	    while (true) {
            system("clear");
            string nivel;
            if (dificultad==1)
                nivel="Fácil";
            else
                nivel="Difícil";
            cout<< BLUE<<"Modo:"<<nivel<<RESET<<endl;
		    imprimirTablero();
		    int opc;
		    if (jugadorActual == 'X') {
			    cout <<BLUE<<"Turno del jugador:"<<jugadorActual<<RESET<<endl;
			    cout << "Selecciona una casilla del tablero ó 0 para cancelar partida: ";
			    cin >> opc;
			    if (opc == 0) {
				    estadisticas.partidasCanceladas++;
                    cout << GREEN <<BG_WHITE <<"! Partida Cancelada !" <<RESET;
				    cin.clear();
	                cin.ignore();
	                cin.get();
				    break;
			    }
			    while(opc < 1 || opc > 9) {
                    cout << RED<<BG_WHITE<<"Número de casilla inválido." << RESET << endl;
                    cout << "selecciona una casilla del tablero :";
                    cin >> opc;
                }
                //convierte la casilla seleccionada a cordenadas de la matriz
			    int fila = (opc - 1) / 3;
			    int columna = (opc - 1) % 3;
                //Realiza el movimiento , en caso de que la casilla seleccionada ya este ocupada mandará mensaje de error
			    if (!realizarJugada( fila, columna, 'X')) {
                    cout << RED<<BG_WHITE<<"La casilla seleccionada ya se encuentra ocupada" << RESET << endl;
                    cin.clear();
	                cin.ignore();
	                cin.get();
				    continue;
			    }
		    } else {
                //turno de la maquina
			    if (dificultad == 1) 
				    jugadaMaquinaFacil();
			    else 
				    movimientoMaquinaDificil();
			
		        }
		    //valida despues de realizar los movimientos de cada jugador si ya hay ganador o un empate
		    if (hayGanador(jugadorActual)) {
                system("clear");
			    imprimirTablero();
			    if (jugadorActual == 'X') {
                    estadisticas.partidasGanadasHumano1++; //aumenta las estadisticas de que gano el jugador x o humanos
                    cout << GREEN <<BG_WHITE <<"Jugador: "<<jugadorActual<<" ¡ Has ganado !" << RESET;
				    cin.clear();
	                cin.ignore();
	                cin.get();
				} else {
                    //gano la maquina
                    estadisticas.partidasGanadasComputadora++; //aumenta el registro de partidas ganadas de la maquina
				    cout << GREEN <<BG_WHITE <<"! La maquina ha ganado !" <<RESET;
				    cin.clear();
	                cin.ignore();
	                cin.get();
			        }
                //aumenta las partidas jugadas
			    estadisticas.partidasHumanoVsComputadora++; 
			    break;
                //si no hubo ganadores entonces validamos si hay empate
		    } else if (tableroLleno()) {
                system("clear");
			    imprimirTablero();
                //aumenta estadisticas
                estadisticas.partidasEmpatadas++;
			    estadisticas.partidasHumanoVsComputadora++;
			    cout << GREEN <<BG_WHITE <<"! Es un Empate !"<<RESET;
                cin.clear();
	            cin.ignore();
	            cin.get();
			    break;
		        }
		    //hacemos el cambio de jugador
		    jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
	    }
        //ya termino la partida vamos a preguntar si quiere volver a jugar 
        if (getJugarDeNuevo()=='N')
            break;
    }
	
}

//Metodo para mostrar las estadísticas del partido
void mostrarEstadisticas(const Estadisticas& estadisticas) {
    system("clear");
    cout << BLUE <<BG_WHITE << "Estadísticas del juego:" << RESET << endl;
	cout << "Número de partidas jugadas entre Jugador X y Jugador O: " << estadisticas.partidasHumanoVsHumano <<endl;
	cout << "Número de partidas jugadas entre Jugador y Computadora: " << estadisticas.partidasHumanoVsComputadora <<endl;
	cout << "Número de partidas ganadas por Jugador X: " << estadisticas.partidasGanadasHumano1 <<endl;
	cout << "Número de partidas ganadas por Jugador O: " << estadisticas.partidasGanadasHumano2 <<endl;
	cout << "Número de partidas ganadas por Computadora: " << estadisticas.partidasGanadasComputadora <<endl;
    cout << "Número de partidas empatadas: " << estadisticas.partidasEmpatadas <<endl;
    cout << "Número de partidas canceladas: " << estadisticas.partidasCanceladas <<endl;
    cout << "\nPresione Enter para regresar al Menú Principal ";
    cin.clear();
	cin.ignore();
	cin.get();
}

