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

void main(void)
{
    unsigned int switches_val;
    IOsetup();
    while (1) {
        switches_val = getSwitchVal();
        writeValtoLEDs(switches_val);
        delay(2000);
        writeValtoLEDs(0);
        delay(2000);

    }
    return(0);
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
