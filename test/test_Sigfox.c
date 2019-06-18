#include "unity.h"
#include "wssfm1xrx.h"

/*instance*/
WSSFM1XRXConfig_t Sigfox;

WSSFM1XRX_Return_t  ret ;

char bufferRx[32] = "OK";
char commandTX[10][10] = {"AT\r","AT$P=2\r"};
char commandRX[10][10] = {"OK\r","OK\r"};


/* Wrappers*/
uint32_t wrapperGET_TICK(void);

void wrapperTXFcn(void * str, char c); // trasmision guardo en un buffer para evaluar despues que salio bien
 // guardo en un buffer array de respuestas para saber que respondio.

void simular_recepcion(void);

void reset(uint8_t a);

void reset2(uint8_t b);

WSSFM1XRX_DL_Return_t callback(WSSFM1XRXConfig_t*obj) ;

// se ejecuta antes de cada test
void setUp(void){
    ret = WSSFM1XRX_Init(&Sigfox, 
         reset,reset2, wrapperTXFcn, WSSFM1XRX_RCZ4,
         callback , wrapperGET_TICK, bufferRx ,
         sizeof(bufferRx), 4);
  //  leds_create(&puerto_virtual);
}

void test_respuesta_comando_AT(void){
   
    ret = WSSFM1XRX_CheckModule(&Sigfox,WSSFM1XRX_Wait_Block);
    simular_recepcion();
    TEST_ASSERT_EQUAL(ret,WSSFM1XRX_OK_RESPONSE);
}


uint32_t wrapperGET_TICK(void){
   static uint32_t tick = 0;
     tick++; // o cambio 3 10 de vez en cuando
     return tick ;
    }


void wrapperTXFcn(void * str, char c){
    static int i = 0;
    static char buffer[10];
    buffer[i++]= c;
   
    if(c == '\r'){
       // printf("%s \n",buffer);
        i = 0;
       TEST_ASSERT_EACH_EQUAL_STRING("AT\r","AT\r",3); 
    }
                // array predefinido y otro de lo que envio y comparo,  una estructura con la 
        //comunicacion dos  buffer y muevo la posicion del puntero , tambien tengo tres buffers los tick.
        // o tener dististos test  con ticks diferentes y otro que vayan a timeout y otros no.
        //la otra forma , en lugar deguardarla cadena para comparar la que trasmito ,
        // hacerlo directamente en el warpper de tx , me fijo  y sino  corto  
        //TEST_ASSERT_EACH_EQUAL_STRING("OK","OK",2);
}

void simular_recepcion(void){
    int i = 0;
    while(commandRX[0][i] != '\0')    WSSFM1XRX_ISRRX(&Sigfox,commandRX[0][i++]);
     //printf("%s \n",Sigfox.RxFrame);
    // llmaar a Rxisr del driver directamente  ya que no hay fcnRX
   
}

void reset(uint8_t a){
    // pin hardware
}

void reset2(uint8_t b){
    // pin hardware
}

WSSFM1XRX_DL_Return_t callback(WSSFM1XRXConfig_t*obj) {
    // calbback
    return 1;
}