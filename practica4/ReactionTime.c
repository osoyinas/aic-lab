#if defined(D_NEXYS_A7)
    #include <bsp_printf.h>
    #include <bsp_mem_map.h>
    #include <bsp_version.h>
#else
    PRE_COMPILED_MSG("no platform was defined")
#endif
#include <psp_api.h>

#include <stdlib.h>



// memory-mapped I/O addresses
#define GPIO_SWs 0x80001400
#define GPIO_LEDs 0x80001404
#define GPIO_INOUT 0x80001408


#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value)                 \
    {                                          \
        (*(volatile unsigned *)dir) = (value); \
    }


void IOsetup();
unsigned int getSwitchVal();


void writeValtoLEDs(unsigned int val);
unsigned int getSwitchesInvert();

int DELAY_GLOBAL = 0; // la funcion delay tiene que modificar una variable global porque si no el compilador lo elimina

void delay(int num);
int reaction = 0;
int main(void)
{
    uartInit();
    IOsetup();
    printfNexys("Iniciando\n");
    while (1) {
        int counter = 0;
        writeValtoLEDs(reaction);
        while(getSwitchVal()&1) {
            counter++;
        }
        writeValtoLEDs(0);
        srand(counter);
        int rand_delay = 1000 + rand()%2000;
        delay(rand_delay);
        writeValtoLEDs(0xFFFF);
        reaction = 0;
        while(!(getSwitchVal() & 1)) {
            reaction++;
            delay(1);
        }
        printfNexys("Tiempo de reaccion: %d en milisegundos\n", reaction);
        writeValtoLEDs(reaction);
        delay(1000);

    }
    return 0;
}


void IOsetup()
{
    int En_Value=0xFFFF;
    WRITE_GPIO(GPIO_INOUT, En_Value);
}


unsigned int getSwitchVal()
{
    unsigned int val;
    val = READ_GPIO(GPIO_SWs); // read value on switches
    val = val >> 16; // shift into lower 16 bits
    return val;
}

 void delay (int num) {
    int j = 0;
    DELAY_GLOBAL = num * 30000; //aprox = 1ms
    while (j < DELAY_GLOBAL) {
        j = j + 1;
    }
    return;
 }

void writeValtoLEDs(unsigned int val)
{
    WRITE_GPIO(GPIO_LEDs, val); // display val on LEDs
}
unsigned int getSwitchesInvert(){
    return ~getSwitchVal();
}
