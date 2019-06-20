#include "wssfm1xrx.h"


//paso de comunicacion y tiempo que pasa entre los mismos
typedef struct {
	const char * tx;
	uint8_t retardo_tx;
	const char * rx;
	uint8_t retardo_rx;
} paso_t;

// Define un arreglo de las estructuras con la secuencia de comunicación a probar
extern paso_t ejemplo[2];
/* Define una variable con el estado actual de la comunicación*/
typedef struct {
	uint8_t paso;
	uint32_t tick_actual;
} estado_t;


extern WSSFM1XRXConfig_t Sigfox;
extern WSSFM1XRX_Return_t  ret ;
extern estado_t estado;


// El Mock de TX verifica la cadena enviada y avanza el estado actual
void WrapperTX(char * BufferTX);

// El Mock de RX devuelve la cadena de respuesta y avanza el estado actual
void  WrapperRX(char * BufferRX);

// El tico devuelve siempre el valor actual de reloj definido por las transmisiones y recepciones
uint32_t WrapperGetTick(void);

void simular_recepcion(void);

void wrapperTXFcn(void * str, char c); // trasmision guardo en un buffer para evaluar despues que salio bien
 // guardo en un buffer array de respuestas para saber que respondio.

void wrapperTXFcn(void * str, char c);
void simular_recepcion(void);
void reset(uint8_t a);
void reset2(uint8_t b);
WSSFM1XRX_DL_Return_t callback(WSSFM1XRXConfig_t*obj) ;