# about author

made by TangSong404

# about code directory

code dir is used to store library files that you wrote

the COMMON.h  is used to integrate all library files in the code directory

# about eeprom config

1.in `.syscfg` file

you should focus on the top right corner and find `Show Generated Files`

then  disabled the include of build about `device_linker.cmd`

2.then create `mspm0g3507.cmd` in root dir

content:

```
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

