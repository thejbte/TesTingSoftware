#include "Wrappers.h"
#include "unity.h"

WSSFM1XRXConfig_t Sigfox;
WSSFM1XRX_Return_t  ret ;
estado_t estado;




/**=====================================================================
 *         verifica la cadena enviada y avanza el estado actual  
 * =====================================================================
*/
void WrapperTX(char * BufferTX) {
    puts(BufferTX);
    puts(ejemplo[estado.paso].tx);
	TEST_ASSERT_EQUAL_STRING(ejemplo[estado.paso].tx, BufferTX);
	estado.tick_actual += ejemplo[estado.paso].retardo_tx;
    
}

 
/**=====================================================================
 *         devuelve la cadena de respuesta y avanza el estado actuall  
 * =====================================================================
*/
void  WrapperRX(char * BufferRX) {
	memcpy(BufferRX, ejemplo[estado.paso].rx, 10);
	estado.tick_actual += ejemplo[estado.paso].retardo_rx;
}


/**=====================================================================
 *          tick devuelve siempre el valor actual de 
 *          reloj definido por las transmisiones y recepciones
 * =====================================================================
*/
uint32_t WrapperGetTick(void) {
    return estado.tick_actual;
}


void reset(uint8_t a){
    // pin hardware
}

void reset2(uint8_t b){
    // pin hardware
}

WSSFM1XRX_DL_Return_t callback(WSSFM1XRXConfig_t*obj) {
     //Callback Downlink
       return 1;
}