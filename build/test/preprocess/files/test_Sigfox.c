#include "build/temp/_test_Sigfox.c"
#include "Wrappers.h"
#include "wssfm1xrx.h"
#include "unity.h"


char bufferRx[32];



paso_t ejemplo[] = {

 {

  .tx = "AT\r",

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







void setUp(void){

    ret = WSSFM1XRX_Init(&Sigfox,

         reset,reset2, wrapperTXFcn, WSSFM1XRX_RCZ4,

         callback , WrapperGetTick, bufferRx ,

         sizeof(bufferRx), 4);

}





void test_inicializacion(void) {

 estado.paso = 0;

    estado.tick_actual = 0;



    int i = 0;

    uint8_t Bufferrx[10];



    WrapperRX(Bufferrx);

    while(Bufferrx[i] != '\0') {

            WSSFM1XRX_ISRRX(&Sigfox,Bufferrx[i++]);

        }





    ret = WSSFM1XRX_CheckModule(&Sigfox,WSSFM1XRX_Wait_NonBlock);

    UnityAssertEqualNumber((UNITY_INT)((WSSFM1XRX_OK_RESPONSE)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_INT);



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
