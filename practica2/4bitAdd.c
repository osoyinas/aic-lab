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
        switches_value = READ_GPIO(GPIO_SWs); // read value on switches

        // Extracting the 4 least significant bits and the 4 most significant bits
        switches_value = switches_value >> 16; // shift into lower 16 bits
        int least_significant = switches_value & 0x0F;
        int most_significant = (switches_value >> 4) & 0x0F;

        int result = least_significant + most_significant;

        // Checking for overflow
        if (result > 15)
            result |= (1 << 4);

        WRITE_GPIO(GPIO_LEDs, result); // display switch value on LEDs
    }
}