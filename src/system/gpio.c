/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Generic GPIO driver implementation

Comment: Relies on the specific board GPIO implementation as well as on
         IO expander driver implementation if one is available on the target
         board.

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
#include "gpio-board.h"

void GpioInit( Gpio_t *obj, PinNames pin, PinModes mode,  PinConfigs config,
               PinTypes type, uint32_t value )
{
    if (NC != pin) {
        GpioMcuInit( obj, pin, mode, config, type, value );
    }
}

void GpioSetInterrupt( Gpio_t *obj, IrqModes irqMode, IrqPriorities irqPriority,
                       GpioIrqHandler *irqHandler )
{
    if (NC != obj->pin) {
        GpioMcuSetInterrupt( obj, irqMode, irqPriority, irqHandler );
    }
}

void GpioRemoveInterrupt( Gpio_t *obj )
{
    if (NC != obj->pin) {
        GpioMcuRemoveInterrupt( obj );
    }
}

void GpioWrite( Gpio_t *obj, uint32_t value )
{
    if (NC != obj->pin) {
        GpioMcuWrite( obj, value );
    }
}

void GpioToggle( Gpio_t *obj )
{
    if (NC != obj->pin) {
        GpioMcuToggle( obj );
    }
}

uint32_t GpioRead( Gpio_t *obj )
{
    if (NC != obj->pin)     {
        return GpioMcuRead( obj );
    } else {
        return 0;
    }
}
