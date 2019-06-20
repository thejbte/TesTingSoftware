#include "unity.h"
#include "wssfm1xrx.h"
#include "Wrappers.h"

char bufferRx[32];

paso_t ejemplo[] = {
	{
		.tx = "AT\r",  /*INICIALIZO MIEMBRO  de la estructura*/
		.retardo_tx = 16,
		.rx = "OK\r",
		.retardo_rx = 16,
	}, {
		.tx = "AT$P=2\r",
		.retardo_tx = 2,
		.rx = "OK\r",
		.retardo_rx = 1,
	}
};


// se ejecuta antes de cada test
void setUp(void){
    ret = WSSFM1XRX_Init(&Sigfox, 
         reset,reset2, wrapperTXFcn, WSSFM1XRX_RCZ4,
         callback , WrapperGetTick, bufferRx ,
         sizeof(bufferRx), 4);
}

// El test case inicia el estado en cero y llama a la función de prueba
void test_inicializacion(void) {
	estado.paso = 0;
    estado.tick_actual = 0;

    int i = 0;
    uint8_t Bufferrx[10];
    WrapperRX(Bufferrx);
    for ( int k = 0; k <= 1; k++){
        while(Bufferrx[i] != '\0') {
            WSSFM1XRX_ISRRX(&Sigfox,Bufferrx[i++]); 
        } 
        i = 0;
        ret = WSSFM1XRX_CheckModule(&Sigfox,WSSFM1XRX_Wait_NonBlock); // Luego ya no envía por que ya envio pero el tick se cumple 
  }
    // y en el buffer esta la respuesta 
    TEST_ASSERT_EQUAL(WSSFM1XRX_OK_RESPONSE,ret);
  
}

void wrapperTXFcn(void * str, char c){
    static int i = 0;
    static char buffer[10];
    buffer[i++]= c;
   
    if(c == '\r'){
        WrapperTX(buffer);
    }
}

void simular_recepcion(void){
    int i = 0;
    uint8_t Bufferrx[10];
    WrapperRX(Bufferrx);
    while(Bufferrx != '\0') {
            WSSFM1XRX_ISRRX(&Sigfox,Bufferrx[i++]); 
        }
}