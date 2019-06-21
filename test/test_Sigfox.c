#include "unity.h"
#include "wssfm1xrx.h"
#include "Wrappers.h"

/**=====================================================================
 *         Testing Software Julian Bustamante
 * =====================================================================
*/

char bufferRx[32];

/**=====================================================================
 *         Datos de comunicación
 * =====================================================================
*/
paso_t ejemplo[] = {
	{
		.tx = "AT\r",  /*INICIALIZO MIEMBRO  de la estructura*/
		.retardo_tx = 1501,
		.rx = "OK\r",
		.retardo_rx = 1501,
	}, {
		.tx = "AT$P=2\r",
		.retardo_tx = 2,
		.rx = "OK\r",
		.retardo_rx = 1,
	},
    {
		.tx = "AT$GI?\r",
		.retardo_tx = 2,
		.rx = "1,4\r",
		.retardo_rx = 1,
	}
    ,
    {
		.tx = "AT$WR\r\r",
		.retardo_tx = 2,
		.rx = "OK\r",
		.retardo_rx = 1,
	}
    ,
    {
		.rx = "OK\r",
        .tx = "OK\r",
		.retardo_tx = 2,
		.retardo_rx = 1,
	}
};

/*Para check channels*/
Channels_t channels;

// se ejecuta antes de cada test
void setUp(void){
    ret = WSSFM1XRX_Init(&Sigfox, 
         reset,reset2, wrapperTXFcn, WSSFM1XRX_RCZ4,
         callback , WrapperGetTick, bufferRx ,
         sizeof(bufferRx), 4);
}


/**=====================================================================
 *         Test Secuencia levantar modulo  
 * =====================================================================
*/
void test_inicializacion(void) {
	char * rspPtr;
    
    estado.paso = 0;
    estado.tick_actual = 0;

    ret = WSSFM1XRX_CheckModule(&Sigfox,WSSFM1XRX_Wait_NonBlock); 
    TEST_ASSERT_EQUAL(WSSFM1XRX_OK_RESPONSE,ret);
    estado.paso++;
    ret = WSSFM1XRX_Sleep(&Sigfox,WSSFM1XRX_Wait_NonBlock); 
    TEST_ASSERT_EQUAL(WSSFM1XRX_OK_RESPONSE,ret);
    estado.paso++;
    ret = WSSFM1XRX_AskChannels(&Sigfox,WSSFM1XRX_Wait_NonBlock,&channels); 
    TEST_ASSERT_EQUAL(WSSFM1XRX_OK_RESPONSE,ret);
   // rspPtr=strchr((const char *)(ejemplo[estado.paso].rx ) , ',');
    TEST_ASSERT_EQUAL(channels.x, *ejemplo[estado.paso].rx -'0' ) ;
    TEST_ASSERT_EQUAL(channels.y, *(ejemplo[estado.paso].rx + 2) -'0' ) ;
    estado.paso++;
    ret = WSSFM1XRX_SaveParameters(&Sigfox,WSSFM1XRX_Wait_NonBlock); 
    TEST_ASSERT_EQUAL(WSSFM1XRX_OK_RESPONSE,ret);

    estado.paso++;
    ret = WSSFM1XRX_MatchResponse(&Sigfox,ejemplo[estado.paso].tx); 
    TEST_ASSERT_EQUAL(WSSFM1XRX_OK_RESPONSE,ret);


}

/**=====================================================================
 *         Wrapper transmision por uart Precargo con la respuest   
 * =====================================================================
*/
void wrapperTXFcn(void * str, char c){
    static int index = 0;
    int k = 0;
    static char buffer[10];
    buffer[index++]= c;
    uint8_t Bufferrx[10];
    
    if(c == '\r'){
        index = 0;
        // Precargo con la respuesta OK\r
        WrapperRX(Bufferrx);
        while(Bufferrx[k] != '\0') {
            WSSFM1XRX_ISRRX(&Sigfox,Bufferrx[k++]); 
        }
        WrapperTX(buffer);       //Verifica buffer Tx con lo trasmitido  
        
    }
}
