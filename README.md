# about author

made by TangSong404

my CSDN blog (about TI-MSPM0G3507)

[TI-MSPM0G3507_Tangsong:)的博客-CSDN博客](https://blog.csdn.net/2401_86231275/category_12723410.html?spm=1001.2014.3001.5482)

my own blog(my sweet home)

[TangSong404's Blog](https://www.tangsong404.top/)

# about Libarary directory

Libarary dir is used to store library files that you wrote

the COMMON.h  is used to integrate all library files in the code directory

# about eeprom config

1.in `.syscfg` file

you should focus on the top right corner and find `Show Generated Files`

then  disabled the include of build about `device_linker.cmd`

2.then create `mspm0g3507.cmd` in root dir

content:

```C
-uinterruptVectors
--stack_size=512

MEMORY
{
    FLASH           (RX)  : origin = 0x00000000, length = 0x00020000
    SRAM            (RWX) : origin = 0x20200000, length = 0x00008000
    BCR_CONFIG      (R)   : origin = 0x41C00000, length = 0x00000080
    BSL_CONFIG      (R)   : origin = 0x41C00100, length = 0x00000080

}

SECTIONS
{
    .intvecs:   > 0x00000000
    .EEPROM :   > 0x00001000
    .text   : palign(8) {} > FLASH
    .const  : palign(8) {} > FLASH
    .cinit  : palign(8) {} > FLASH
    .pinit  : palign(8) {} > FLASH
    .rodata : palign(8) {} > FLASH
    .ARM.exidx    : palign(8) {} > FLASH
    .init_array   : palign(8) {} > FLASH
    .binit        : palign(8) {} > FLASH
    .TI.ramfunc   : load = FLASH, palign(8), run=SRAM, table(BINIT)

    .vtable :   > SRAM
    .args   :   > SRAM
    .data   :   > SRAM
    .bss    :   > SRAM
    .sysmem :   > SRAM
    .stack  :   > SRAM (HIGH)

    .BCRConfig  : {} > BCR_CONFIG
    .BSLConfig  : {} > BSL_CONFIG
}
```

The EEPROM is the custom section name and 0x00001000 the custom start address.

 3.use the expression below in whice file you want to use eeprom typeb

```c
const uint32_t EEPROM[4096] __attribute((used)) __attribute((section(".EEPROM")))={0};
```

**causes:**	

If the user code occupies a large amount of space, the data storage may conflict with the user code address and cause incorrect erasion.That's why problem arises.

Once the operation above is done, the compiler will avoid the custom eeprom, and the code will only be stored in the .text.So we can solve the problem.

# about tft180

To fit the code of `TFT180.h`

you should create a SPI named `TFT_SPI`

then create a GPIO port named `TFT`

the GPIO port has 4 pins: `DC`	`RES`	`CS`	`BL`	(The first two default clear, the last two default set)

# about icm20602

To fit the code of `icm20602`

you should create a SPI named `ICM_SPI`

then create a GPIO port named `OTHER`

the GPIO port has 1 pin: `ICM_CS` (default set)

# about openmv

To fit the code of `openmv`

you should create a UARTnamed `OPENMV`

and set the Baud Rate same to openmv (default 19200)

```C
uint8_t openmv_init();//use to check connection

void openmv_cmd(uint8_t cmd , uint8_t (*func)(uint8_t*));//use to register a command with callback function

float openmv_parse_float(uint8_t* data,uint8_t* index);//use to get a float data

int openmv_parse_int(uint8_t* data, uint8_t* index);//use to get a int data

const char* openmv_parse_string(uint8_t* data, uint8_t* index);//use to get a string data

uint8_t openmv_parse_byte(uint8_t* data, uint8_t* index);//use to get a byte data
```

# about tft350

To fit the code of `TFT350`

the config is same to `TFT180`

but you cant use tft350 while the tft180 is using unless spi instances of them are modified

# about esp01

To fit the code of `esp01`

you should create a UART named `ESP01`

and set the Baud Rate 115200

```C
void esp01_init(const char*ssid,const char*password,const char*ip,const char*port);//connect wifi and create udp
void esp01_start();//start to do transparent transimition
void esp01_close();//stop transmition
void esp01_sendData(uint8_t* data,uint8_t len);//send data
void esp01_sendAt(uint8_t* data);//send AT cmd
```

if you get seekfree assistant from [逐飞助手](https://gitee.com/seekfree/seekfree_assistant)

you can use virtual oscilloscope

```c
esp01_oscilloscope_channel(i,a) //set data a at channel i
void elsp01_oscilloscope_send();//transmit all channels that has datas to virtual oscilloscope
```

