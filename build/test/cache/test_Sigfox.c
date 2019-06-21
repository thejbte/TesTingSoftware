#include "build/temp/_test_Sigfox.c"
#include "Wrappers.h"
#include "wssfm1xrx.h"
#include "unity.h"


char bufferRx[32];











paso_t ejemplo[] = {

 {

  .tx = "AT\r",

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





Channels_t channels;





void setUp(void){

    ret = WSSFM1XRX_Init(&Sigfox,

         reset,reset2, wrapperTXFcn, WSSFM1XRX_RCZ4,

         callback , WrapperGetTick, bufferRx ,

         sizeof(bufferRx), 4);

}













void test_inicializacion(void) {

 char * rspPtr;



    estado.paso = 0;

    estado.tick_actual = 0;



    ret = WSSFM1XRX_CheckModule(&Sigfox,WSSFM1XRX_Wait_NonBlock);

    UnityAssertEqualNumber((UNITY_INT)((WSSFM1XRX_OK_RESPONSE)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_INT);

    estado.paso++;

    ret = WSSFM1XRX_Sleep(&Sigfox,WSSFM1XRX_Wait_NonBlock);

    UnityAssertEqualNumber((UNITY_INT)((WSSFM1XRX_OK_RESPONSE)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);

    estado.paso++;

    ret = WSSFM1XRX_AskChannels(&Sigfox,WSSFM1XRX_Wait_NonBlock,&channels);

    UnityAssertEqualNumber((UNITY_INT)((WSSFM1XRX_OK_RESPONSE)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((channels.x)), (UNITY_INT)((*ejemplo[estado.paso].rx -'0')), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT) ;

    UnityAssertEqualNumber((UNITY_INT)((channels.y)), (UNITY_INT)((*(ejemplo[estado.paso].rx + 2) -'0')), (

   ((void *)0)

   ), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_INT) ;

    estado.paso++;

    ret = WSSFM1XRX_SaveParameters(&Sigfox,WSSFM1XRX_Wait_NonBlock);

    UnityAssertEqualNumber((UNITY_INT)((WSSFM1XRX_OK_RESPONSE)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_INT);



    estado.paso++;

    ret = WSSFM1XRX_MatchResponse(&Sigfox,ejemplo[estado.paso].tx);

    UnityAssertEqualNumber((UNITY_INT)((WSSFM1XRX_OK_RESPONSE)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(84), UNITY_DISPLAY_STYLE_INT);





}











void wrapperTXFcn(void * str, char c){

    static int index = 0;

    int k = 0;

    static char buffer[10];

    buffer[index++]= c;

    uint8_t Bufferrx[10];



    if(c == '\r'){

        index = 0;



        WrapperRX(Bufferrx);

        while(Bufferrx[k] != '\0') {

            WSSFM1XRX_ISRRX(&Sigfox,Bufferrx[k++]);

        }

        WrapperTX(buffer);



    }

}
