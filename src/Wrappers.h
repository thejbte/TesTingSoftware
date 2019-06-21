#include "wssfm1xrx.h"



/**=====================================================================
 *       pasos de comunicacion
 * =====================================================================
*/
typedef struct {
	const char * tx;
	uint32_t retardo_tx;
	const char * rx;
	uint32_t retardo_rx;
} paso_t;

// Define un arreglo de las estructuras con la secuencia de comunicación a probar
extern paso_t ejemplo[5];

/* Define una variable con el estado actual de la comunicación*/
typedef struct {
	uint8_t paso;
	uint32_t tick_actual;
} estado_t;


extern WSSFM1XRXConfig_t Sigfox;
extern WSSFM1XRX_Return_t  ret ;
extern estado_t estado;



/**=====================================================================
 *       verifica la cadena enviada y avanza el estado actual
 * =====================================================================
*/
void WrapperTX(char * BufferTX);

/**=====================================================================
 *         devuelve la cadena de respuesta y avanza el estado actuall  
 * =====================================================================
*/
void  WrapperRX(char * BufferRX);


/**=====================================================================
 *          tick devuelve siempre el valor actual de 
 *          reloj definido por las transmisiones y recepciones
 * =====================================================================
*/
uint32_t WrapperGetTick(void);


/**=====================================================================
 *         Wrapper transmision por uart Precargo con la respuest   
 * =====================================================================
*/
void wrapperTXFcn(void * str, char c); 


void reset(uint8_t a);
void reset2(uint8_t b);
WSSFM1XRX_DL_Return_t callback(WSSFM1XRXConfig_t*obj) ;