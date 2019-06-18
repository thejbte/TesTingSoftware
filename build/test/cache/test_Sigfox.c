#include "build/temp/_test_Sigfox.c"
#include "wssfm1xrx.h"
#include "unity.h"




WSSFM1XRXConfig_t Sigfox;



WSSFM1XRX_Return_t ret ;



char bufferRx[32] = "OK";

char commandTX[10][10] = {"AT\r","AT$P=2\r"};

char commandRX[10][10] = {"OK\r","OK\r"};







uint32_t wrapperGET_TICK(void);



void wrapperTXFcn(void * str, char c);





void simular_recepcion(void);



void reset(uint8_t a);



void reset2(uint8_t b);



WSSFM1XRX_DL_Return_t callback(WSSFM1XRXConfig_t*obj) ;





void setUp(void){

    ret = WSSFM1XRX_Init(&Sigfox,

         reset,reset2, wrapperTXFcn, WSSFM1XRX_RCZ4,

         callback , wrapperGET_TICK, bufferRx ,

         sizeof(bufferRx), 4);



}



void test_respuesta_comando_AT(void){



    ret = WSSFM1XRX_CheckModule(&Sigfox,WSSFM1XRX_Wait_Block);

    simular_recepcion();

    UnityAssertEqualNumber((UNITY_INT)((ret)), (UNITY_INT)((WSSFM1XRX_OK_RESPONSE)), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_INT);

}





uint32_t wrapperGET_TICK(void){

   static uint32_t tick = 0;

     tick++;

     return tick ;

    }





void wrapperTXFcn(void * str, char c){

    static int i = 0;

    static char buffer[10];

    buffer[i++]= c;



    if(c == '\r'){



        i = 0;

       UnityAssertEqualStringArray(( const void*)(("AT\r")), (const char**)(("AT\r")), (UNITY_UINT32)((3)), (

      ((void *)0)

      ), (UNITY_UINT)(60), UNITY_ARRAY_TO_VAL);

    }













}



void simular_recepcion(void){

    int i = 0;

    while(commandRX[0][i] != '\0') WSSFM1XRX_ISRRX(&Sigfox,commandRX[0][i++]);







}



void reset(uint8_t a){



}



void reset2(uint8_t b){



}



WSSFM1XRX_DL_Return_t callback(WSSFM1XRXConfig_t*obj) {



    return 1;

}
