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
#ifndef __GPIO_H__
#define __GPIO_H__

/* Board GPIO pin names */
typedef enum __attribute__((packed))
{
    PA_0, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7,
    PA_8, PA_9, PA_10, PA_11, PA_12, PA_13, PA_14, PA_15,

    PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7,
    PB_8, PB_9, PB_10, PB_11, PB_12, PB_13, PB_14, PB_15,

    PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7,
    PC_8, PC_9, PC_10, PC_11, PC_12, PC_13, PC_14, PC_15,

    PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7,
    PD_8, PD_9, PD_10, PD_11, PD_12, PD_13, PD_14, PD_15,

    PE_0, PE_1, PE_2, PE_3, PE_4, PE_5, PE_6, PE_7,
    PE_8, PE_9, PE_10, PE_11, PE_12, PE_13, PE_14, PE_15,

    PF_0, PF_1, PF_2, PF_3, PF_4, PF_5, PF_6, PF_7,
    PF_8, PF_9, PF_10, PF_11, PF_12, PF_13, PF_14, PF_15,

    PH_0, PH_1, PH_2, PH_3, PH_4, PH_5, PH_6, PH_7,
    PH_8, PH_9, PH_10, PH_11, PH_12, PH_13, PH_14, PH_15,

    // Not connected
    NC = 0xFF
}PinNames;

/*!
 * Operation Mode for the GPIO
 */
typedef enum
{
    PIN_INPUT = 0,
    PIN_OUTPUT,
    PIN_ALTERNATE_FCT,
    PIN_ANALOG
}PinModes;

/*!
 * Add a pull-up, a pull-down or nothing on the GPIO line
 */
typedef enum
{
    PIN_NO_PULL = 0,
    PIN_PULL_UP,
    PIN_PULL_DOWN
}PinTypes;

/*!
 * Define the GPIO as Push-pull type or Open Drain
 */
typedef enum
{
    PIN_PUSH_PULL = 0,
    PIN_OPEN_DRAIN
}PinConfigs;

/*!
 * Define the GPIO IRQ on a rising, falling or both edges
 */
typedef enum
{
    NO_IRQ = 0,
    IRQ_RISING_EDGE,
    IRQ_FALLING_EDGE,
    IRQ_RISING_FALLING_EDGE
}IrqModes;

/*!
 * Define the IRQ priority on the GPIO
 */
typedef enum
{
    IRQ_VERY_LOW_PRIORITY = 0,
    IRQ_LOW_PRIORITY,
    IRQ_MEDIUM_PRIORITY,
    IRQ_HIGH_PRIORITY,
    IRQ_VERY_HIGH_PRIORITY
}IrqPriorities;

/*!
 * Structure for the GPIO
 */
typedef struct
{
    PinNames  pin;
    uint16_t pinIndex;
    void *port;
    uint16_t portIndex;
    PinTypes pull;
}Gpio_t;

/*!
 * GPIO IRQ handler function prototype
 */
typedef void( GpioIrqHandler )( void );

/*!
 * \brief Initializes the given GPIO object
 *
 * \param [IN] obj    Pointer to the GPIO object
 * \param [IN] pin    Pin name
 * \param [IN] mode   Pin mode [PIN_INPUT, PIN_OUTPUT,
 *                              PIN_ALTERNATE_FCT, PIN_ANALOG]
 * \param [IN] config Pin config [PIN_PUSH_PULL, PIN_OPEN_DRAIN]
 * \param [IN] type   Pin type [PIN_NO_PULL, PIN_PULL_UP, PIN_PULL_DOWN]
 * \param [IN] value  Default output value at initialization
 */
void GpioInit( Gpio_t *obj, PinNames pin, PinModes mode, PinConfigs config, PinTypes type, uint32_t value );

/*!
 * \brief GPIO IRQ Initialization
 *
 * \param [IN] obj         Pointer to the GPIO object
 * \param [IN] irqMode     IRQ mode [NO_IRQ, IRQ_RISING_EDGE,
 *                                   IRQ_FALLING_EDGE, IRQ_RISING_FALLING_EDGE]
 * \param [IN] irqPriority IRQ priority [IRQ_VERY_LOW_PRIORITY, IRQ_LOW_PRIORITY
 *                                       IRQ_MEDIUM_PRIORITY, IRQ_HIGH_PRIORITY
 *                                       IRQ_VERY_HIGH_PRIORITY]
 * \param [IN] irqHandler  Callback function pointer
 */
void GpioSetInterrupt( Gpio_t *obj, IrqModes irqMode, IrqPriorities irqPriority, GpioIrqHandler *irqHandler );

/*!
 * \brief Removes the interrupt from the object
 *
 * \param [IN] obj Pointer to the GPIO object
 */
void GpioRemoveInterrupt( Gpio_t *obj );

/*!
 * \brief Writes the given value to the GPIO output
 *
 * \param [IN] obj   Pointer to the GPIO object
 * \param [IN] value New GPIO output value
 */
void GpioWrite( Gpio_t *obj, uint32_t value );

/*!
 * \brief Toggle the value to the GPIO output
 *
 * \param [IN] obj   Pointer to the GPIO object
 */
void GpioToggle( Gpio_t *obj );

/*!
 * \brief Reads the current GPIO input value
 *
 * \param [IN] obj Pointer to the GPIO object
 * \retval value   Current GPIO input value
 */
uint32_t GpioRead( Gpio_t *obj );

#endif // __GPIO_H__
