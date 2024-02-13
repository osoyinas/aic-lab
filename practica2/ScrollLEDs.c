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
    int En_Value = 0xFFFF, leds_value = 0x0001, i; // GPIO = 0x0000(in) FFFF(out)
    WRITE_GPIO(GPIO_INOUT, En_Value);

    while (1)
    {
        if (leds_value == 0xFFFF)
        {
            leds_value = 0x0001;
        }
        // desplazamiento a derechas
        for (i = 0; i < 15; i++)
        {
            WRITE_GPIO(GPIO_LEDs, leds_value);
            delay(1000000);
            leds_value = leds_value << 1;
        }

        // dezplazamiento a izquierdas
        for (i = 0; i < 15; i++)
        {
            WRITE_GPIO(GPIO_LEDs, leds_value);
            delay(1000000);
            leds_value = leds_value >> 1;
        }
        leds_value = (leds_value << 1) + 1;
    }
}