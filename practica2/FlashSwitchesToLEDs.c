// memory-mapped I/O addresses
#define GPIO_SWs 0x80001400
#define GPIO_LEDs 0x80001404
#define GPIO_INOUT 0x80001408

#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value)                 \
    {                                          \
        (*(volatile unsigned *)dir) = (value); \
    }

void delay(int n)
{
    for (int i = 0; i < n; i++)
        ;
}
int main(void)
{
    int En_Value = 0xFFFF, switches_value; // GPIO = 0x0000(in) FFFF(out)
    WRITE_GPIO(GPIO_INOUT, En_Value);
    while (1)
    {
        switches_value = READ_GPIO(GPIO_SWs);  // read value on switches
        switches_value = switches_value >> 16; // shift into lower 16 bits
        WRITE_GPIO(GPIO_LEDs, switches_value); // display switch value on LEDs
        delay(1000000);
        WRITE_GPIO(GPIO_LEDs, 0x0000); // display switch value on LEDs
        delay(1000000);
    }
}