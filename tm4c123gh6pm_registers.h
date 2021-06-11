#ifndef TM4C123GH6PM_REGISTERS
#define TM4C123GH6PM_REGISTERS

/*****************************************************************************
PORTs 
*****************************************************************************/
#define PORTA           (0U)
#define PORTB           (1U)
#define PORTC           (2U)
#define PORTD           (3U)
#define PORTE           (4U)
#define PORTF           (5U)

#define GPIO_PORTA_BASE_ADDRESS   0x40004000
#define GPIO_PORTB_BASE_ADDRESS   0x40005000
#define GPIO_PORTC_BASE_ADDRESS   0x40006000
#define GPIO_PORTD_BASE_ADDRESS   0x40007000
#define GPIO_PORTE_BASE_ADDRESS   0x40024000
#define GPIO_PORTF_BASE_ADDRESS   0x40025000
  
#define GPIO_AFSEL_OFFSET         0x420
#define GPIO_DEN_OFFSET           0x51C
#define GPIO_DIR_OFFSET           0x400
#define GPIO_PCTL_OFFSET          0x52C
#define GPIO_GPIOAMSEL_OFFSET     0x528

/*****************************************************************************
GPIO registers (PORTA)
*****************************************************************************/
#define GPIO_PORTA_DATA_REG       (*((volatile uint32 *)0x400043FC))
#define GPIO_PORTA_DIR_REG        (*((volatile uint32 *)0x40004400))
#define GPIO_PORTA_AFSEL_REG      (*((volatile uint32 *)0x40004420))
#define GPIO_PORTA_PUR_REG        (*((volatile uint32 *)0x40004510))
#define GPIO_PORTA_PDR_REG        (*((volatile uint32 *)0x40004514))
#define GPIO_PORTA_DEN_REG        (*((volatile uint32 *)0x4000451C))
#define GPIO_PORTA_LOCK_REG       (*((volatile uint32 *)0x40004520))
#define GPIO_PORTA_CR_REG         (*((volatile uint32 *)0x40004524))
#define GPIO_PORTA_AMSEL_REG      (*((volatile uint32 *)0x40004528))
#define GPIO_PORTA_PCTL_REG       (*((volatile uint32 *)0x4000452C))

/* PORTA External Interrupts Registers */
#define GPIO_PORTA_IS_REG         (*((volatile uint32 *)0x40004404))
#define GPIO_PORTA_IBE_REG        (*((volatile uint32 *)0x40004408))
#define GPIO_PORTA_IEV_REG        (*((volatile uint32 *)0x4000440C))
#define GPIO_PORTA_IM_REG         (*((volatile uint32 *)0x40004410))
#define GPIO_PORTA_RIS_REG        (*((volatile uint32 *)0x40004414))
#define GPIO_PORTA_ICR_REG        (*((volatile uint32 *)0x4000441C))

/*****************************************************************************
GPIO registers (PORTB)
*****************************************************************************/
#define GPIO_PORTB_DATA_REG       (*((volatile uint32 *)0x400053FC))
#define GPIO_PORTB_DIR_REG        (*((volatile uint32 *)0x40005400))
#define GPIO_PORTB_AFSEL_REG      (*((volatile uint32 *)0x40005420))
#define GPIO_PORTB_PUR_REG        (*((volatile uint32 *)0x40005510))
#define GPIO_PORTB_PDR_REG        (*((volatile uint32 *)0x40005514))
#define GPIO_PORTB_DEN_REG        (*((volatile uint32 *)0x4000551C))
#define GPIO_PORTB_LOCK_REG       (*((volatile uint32 *)0x40005520))
#define GPIO_PORTB_CR_REG         (*((volatile uint32 *)0x40005524))
#define GPIO_PORTB_AMSEL_REG      (*((volatile uint32 *)0x40005528))
#define GPIO_PORTB_PCTL_REG       (*((volatile uint32 *)0x4000552C))

/*****************************************************************************
PORTB External Interrupts Registers */
/*****************************************************************************/
#define GPIO_PORTB_IS_REG         (*((volatile uint32 *)0x40005404))
#define GPIO_PORTB_IBE_REG        (*((volatile uint32 *)0x40005408))
#define GPIO_PORTB_IEV_REG        (*((volatile uint32 *)0x4000540C))
#define GPIO_PORTB_IM_REG         (*((volatile uint32 *)0x40005410))
#define GPIO_PORTB_RIS_REG        (*((volatile uint32 *)0x40005414))
#define GPIO_PORTB_ICR_REG        (*((volatile uint32 *)0x4000541C))

/*****************************************************************************
GPIO registers (PORTC)
*****************************************************************************/
#define GPIO_PORTC_DATA_REG       (*((volatile uint32 *)0x400063FC))
#define GPIO_PORTC_DIR_REG        (*((volatile uint32 *)0x40006400))
#define GPIO_PORTC_AFSEL_REG      (*((volatile uint32 *)0x40006420))
#define GPIO_PORTC_PUR_REG        (*((volatile uint32 *)0x40006510))
#define GPIO_PORTC_PDR_REG        (*((volatile uint32 *)0x40006514))
#define GPIO_PORTC_DEN_REG        (*((volatile uint32 *)0x4000651C))
#define GPIO_PORTC_LOCK_REG       (*((volatile uint32 *)0x40006520))
#define GPIO_PORTC_CR_REG         (*((volatile uint32 *)0x40006524))
#define GPIO_PORTC_AMSEL_REG      (*((volatile uint32 *)0x40006528))
#define GPIO_PORTC_PCTL_REG       (*((volatile uint32 *)0x4000652C))

/* PORTC External Interrupts Registers */
#define GPIO_PORTC_IS_REG         (*((volatile uint32 *)0x40006404))
#define GPIO_PORTC_IBE_REG        (*((volatile uint32 *)0x40006408))
#define GPIO_PORTC_IEV_REG        (*((volatile uint32 *)0x4000640C))
#define GPIO_PORTC_IM_REG         (*((volatile uint32 *)0x40006410))
#define GPIO_PORTC_RIS_REG        (*((volatile uint32 *)0x40006414))
#define GPIO_PORTC_ICR_REG        (*((volatile uint32 *)0x4000641C))

/*****************************************************************************
GPIO registers (PORTD)
*****************************************************************************/
#define GPIO_PORTD_DATA_REG       (*((volatile uint32 *)0x400073FC))
#define GPIO_PORTD_DIR_REG        (*((volatile uint32 *)0x40007400))
#define GPIO_PORTD_AFSEL_REG      (*((volatile uint32 *)0x40007420))
#define GPIO_PORTD_PUR_REG        (*((volatile uint32 *)0x40007510))
#define GPIO_PORTD_PDR_REG        (*((volatile uint32 *)0x40007514))
#define GPIO_PORTD_DEN_REG        (*((volatile uint32 *)0x4000751C))
#define GPIO_PORTD_LOCK_REG       (*((volatile uint32 *)0x40007520))
#define GPIO_PORTD_CR_REG         (*((volatile uint32 *)0x40007524))
#define GPIO_PORTD_AMSEL_REG      (*((volatile uint32 *)0x40007528))
#define GPIO_PORTD_PCTL_REG       (*((volatile uint32 *)0x4000752C))

/* PORTD External Interrupts Registers */
#define GPIO_PORTD_IS_REG         (*((volatile uint32 *)0x40007404))
#define GPIO_PORTD_IBE_REG        (*((volatile uint32 *)0x40007408))
#define GPIO_PORTD_IEV_REG        (*((volatile uint32 *)0x4000740C))
#define GPIO_PORTD_IM_REG         (*((volatile uint32 *)0x40007410))
#define GPIO_PORTD_RIS_REG        (*((volatile uint32 *)0x40007414))
#define GPIO_PORTD_ICR_REG        (*((volatile uint32 *)0x4000741C))

/*****************************************************************************
GPIO registers (PORTE)
*****************************************************************************/
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define GPIO_PORTE_DIR_REG        (*((volatile uint32 *)0x40024400))
#define GPIO_PORTE_AFSEL_REG      (*((volatile uint32 *)0x40024420))
#define GPIO_PORTE_PUR_REG        (*((volatile uint32 *)0x40024510))
#define GPIO_PORTE_PDR_REG        (*((volatile uint32 *)0x40024514))
#define GPIO_PORTE_DEN_REG        (*((volatile uint32 *)0x4002451C))
#define GPIO_PORTE_LOCK_REG       (*((volatile uint32 *)0x40024520))
#define GPIO_PORTE_CR_REG         (*((volatile uint32 *)0x40024524))
#define GPIO_PORTE_AMSEL_REG      (*((volatile uint32 *)0x40024528))
#define GPIO_PORTE_PCTL_REG       (*((volatile uint32 *)0x4002452C))

/* PORTE External Interrupts Registers */
#define GPIO_PORTE_IS_REG         (*((volatile uint32 *)0x40024404))
#define GPIO_PORTE_IBE_REG        (*((volatile uint32 *)0x40024408))
#define GPIO_PORTE_IEV_REG        (*((volatile uint32 *)0x4002440C))
#define GPIO_PORTE_IM_REG         (*((volatile uint32 *)0x40024410))
#define GPIO_PORTE_RIS_REG        (*((volatile uint32 *)0x40024414))
#define GPIO_PORTE_ICR_REG        (*((volatile uint32 *)0x4002441C))

/*****************************************************************************
GPIO registers (PORTF)
*****************************************************************************/
#define GPIO_PORTF_DATA_REG       (*((volatile uint32 *)0x400253FC))
#define GPIO_PORTF_DIR_REG        (*((volatile uint32 *)0x40025400))
#define GPIO_PORTF_AFSEL_REG      (*((volatile uint32 *)0x40025420))
#define GPIO_PORTF_PUR_REG        (*((volatile uint32 *)0x40025510))
#define GPIO_PORTF_PDR_REG        (*((volatile uint32 *)0x40025514))
#define GPIO_PORTF_DEN_REG        (*((volatile uint32 *)0x4002551C))
#define GPIO_PORTF_LOCK_REG       (*((volatile uint32 *)0x40025520))
#define GPIO_PORTF_CR_REG         (*((volatile uint32 *)0x40025524))
#define GPIO_PORTF_AMSEL_REG      (*((volatile uint32 *)0x40025528))
#define GPIO_PORTF_PCTL_REG       (*((volatile uint32 *)0x4002552C))

/* PORTF External Interrupts Registers */
#define GPIO_PORTF_IS_REG         (*((volatile uint32 *)0x40025404))
#define GPIO_PORTF_IBE_REG        (*((volatile uint32 *)0x40025408))
#define GPIO_PORTF_IEV_REG        (*((volatile uint32 *)0x4002540C))
#define GPIO_PORTF_IM_REG         (*((volatile uint32 *)0x40025410))
#define GPIO_PORTF_RIS_REG        (*((volatile uint32 *)0x40025414))
#define GPIO_PORTF_ICR_REG        (*((volatile uint32 *)0x4002541C))

#define SYSCTL_REGCGC2_REG        (*((volatile uint32 *)0x400FE108))


/*****************************************************************************
Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))

/*****************************************************************************
PLL Registers
*****************************************************************************/
#define SYSCTL_RIS_REG            (*((volatile uint32 *)0x400FE050))
#define SYSCTL_RCC_REG            (*((volatile uint32 *)0x400FE060))
#define SYSCTL_RCC2_REG           (*((volatile uint32 *)0x400FE070))

/*****************************************************************************
GPTs Registers 
*****************************************************************************/
#define SYSCTL_RCGCTIMER_REG        (*((volatile unsigned long *)0x400FE640)) // for Timer Clock generation
#define TIMER0_GPTMCFG_REG          (*((volatile unsigned long *)0x40030000))
#define TIMER0_GPTMTAMR_REG         (*((volatile unsigned long *)0x40030004))
#define TIMER0_GPTMTBMR_REG         (*((volatile unsigned long *)0x40030008))
#define TIMER0_GPTMCTL_REG          (*((volatile unsigned long *)0x4003000C))
#define TIMER0_GPTMICR_REG          (*((volatile unsigned long *)0x40030024))
#define TIMER0_GPTMTAR_REG          (*((volatile unsigned long *)0x40030048))
#define TIMER0_GPTMRIS_REG          (*((volatile unsigned long *)0x4003001C))


/*****************************************************************************
NVIC Registers
*****************************************************************************/
#define NVIC_PRI0_REG             (*((volatile uint32 *)0xE000E400))
#define NVIC_PRI1_REG             (*((volatile uint32 *)0xE000E404))
#define NVIC_PRI2_REG             (*((volatile uint32 *)0xE000E408))
#define NVIC_PRI3_REG             (*((volatile uint32 *)0xE000E40C))
#define NVIC_PRI4_REG             (*((volatile uint32 *)0xE000E410))
#define NVIC_PRI5_REG             (*((volatile uint32 *)0xE000E414))
#define NVIC_PRI6_REG             (*((volatile uint32 *)0xE000E418))
#define NVIC_PRI7_REG             (*((volatile uint32 *)0xE000E41C))
#define NVIC_PRI8_REG             (*((volatile uint32 *)0xE000E420))
#define NVIC_PRI9_REG             (*((volatile uint32 *)0xE000E424))
#define NVIC_PRI10_REG            (*((volatile uint32 *)0xE000E428))
#define NVIC_PRI11_REG            (*((volatile uint32 *)0xE000E42C))
#define NVIC_PRI12_REG            (*((volatile uint32 *)0xE000E430))
#define NVIC_PRI13_REG            (*((volatile uint32 *)0xE000E434))
#define NVIC_PRI14_REG            (*((volatile uint32 *)0xE000E438))
#define NVIC_PRI15_REG            (*((volatile uint32 *)0xE000E43C))
#define NVIC_PRI16_REG            (*((volatile uint32 *)0xE000E440))
#define NVIC_PRI17_REG            (*((volatile uint32 *)0xE000E444))
#define NVIC_PRI18_REG            (*((volatile uint32 *)0xE000E448))
#define NVIC_PRI19_REG            (*((volatile uint32 *)0xE000E44C))
#define NVIC_PRI20_REG            (*((volatile uint32 *)0xE000E450))
#define NVIC_PRI21_REG            (*((volatile uint32 *)0xE000E454))
#define NVIC_PRI22_REG            (*((volatile uint32 *)0xE000E458))
#define NVIC_PRI23_REG            (*((volatile uint32 *)0xE000E45C))
#define NVIC_PRI24_REG            (*((volatile uint32 *)0xE000E460))
#define NVIC_PRI25_REG            (*((volatile uint32 *)0xE000E464))
#define NVIC_PRI26_REG            (*((volatile uint32 *)0xE000E468))
#define NVIC_PRI27_REG            (*((volatile uint32 *)0xE000E46C))
#define NVIC_PRI28_REG            (*((volatile uint32 *)0xE000E470))
#define NVIC_PRI29_REG            (*((volatile uint32 *)0xE000E474))
#define NVIC_PRI30_REG            (*((volatile uint32 *)0xE000E478))
#define NVIC_PRI31_REG            (*((volatile uint32 *)0xE000E47C))
#define NVIC_PRI32_REG            (*((volatile uint32 *)0xE000E480))
#define NVIC_PRI33_REG            (*((volatile uint32 *)0xE000E484))
#define NVIC_PRI34_REG            (*((volatile uint32 *)0xE000E488))

#define NVIC_EN0_REG              (*((volatile uint32 *)0xE000E100))
#define NVIC_EN1_REG              (*((volatile uint32 *)0xE000E104))
#define NVIC_EN2_REG              (*((volatile uint32 *)0xE000E108))
#define NVIC_EN3_REG              (*((volatile uint32 *)0xE000E10C))
#define NVIC_EN4_REG              (*((volatile uint32 *)0xE000E110))
#define NVIC_DIS0_REG             (*((volatile uint32 *)0xE000E180))
#define NVIC_DIS1_REG             (*((volatile uint32 *)0xE000E184))
#define NVIC_DIS2_REG             (*((volatile uint32 *)0xE000E188))
#define NVIC_DIS3_REG             (*((volatile uint32 *)0xE000E18C))
#define NVIC_DIS4_REG             (*((volatile uint32 *)0xE000E190))

#define NVIC_SYSTEM_PRI1_REG      (*((volatile uint32 *)0xE000ED18))
#define NVIC_SYSTEM_PRI2_REG      (*((volatile uint32 *)0xE000ED1C))
#define NVIC_SYSTEM_PRI3_REG      (*((volatile uint32 *)0xE000ED20))
#define NVIC_SYSTEM_SYSHNDCTRL    (*((volatile uint32 *)0xE000ED24))


/*****************************************************************************
UART Registers
*****************************************************************************/
#define UART_RCGCUART_REG         (*((volatile uint32 *)0x400FE618))

#define UART0                     0x4000C000
#define UART1                     0x4000D000
#define UART2                     0x4000E000
#define UART3                     0x4000F000
#define UART4                     0x40010000
#define UART5                     0x40011000
#define UART6                     0x40012000
#define UART7                     0x40013000

#define UARTCTL_OFFSET            0x030
#define UARTIBRD_OFFSET           0x024
#define UARTFBRD_OFFSET           0x028
#define UARTLCRH_OFFSET           0x02C
#define UARTCC_OFFSET             0xFC8
#define UARTFR_OFFSET             0x018
#define UARTDR_OFFSET             0x000
#define UARTICR_OFFSET            0x044
#define UARTIM_OFFSET             0x038


#define UART0_UARTCTL_REG         (*((volatile uint32 *)0x4000C030))
#define UART1_UARTCTL_REG         (*((volatile uint32 *)0x4000D030))
#define UART2_UARTCTL_REG         (*((volatile uint32 *)0x4000E030))
#define UART3_UARTCTL_REG         (*((volatile uint32 *)0x4000F030))
#define UART4_UARTCTL_REG         (*((volatile uint32 *)0x40010030))
#define UART5_UARTCTL_REG         (*((volatile uint32 *)0x40011030))
#define UART6_UARTCTL_REG         (*((volatile uint32 *)0x40012030))
#define UART7_UARTCTL_REG         (*((volatile uint32 *)0x40013030))       

#define UART0_UARTIBRD_REG        (*((volatile uint32 *)0x4000C024))
#define UART1_UARTIBRD_REG        (*((volatile uint32 *)0x4000D024))
#define UART2_UARTIBRD_REG        (*((volatile uint32 *)0x4000E024))
#define UART3_UARTIBRD_REG        (*((volatile uint32 *)0x4000F024))
#define UART4_UARTIBRD_REG        (*((volatile uint32 *)0x40010024))
#define UART5_UARTIBRD_REG        (*((volatile uint32 *)0x40011024))
#define UART6_UARTIBRD_REG        (*((volatile uint32 *)0x40012024))
#define UART7_UARTIBRD_REG        (*((volatile uint32 *)0x40013024))

#define UART0_UARTFBRD_REG        (*((volatile uint32 *)0x4000C028))
#define UART1_UARTFBRD_REG        (*((volatile uint32 *)0x4000D028))
#define UART2_UARTFBRD_REG        (*((volatile uint32 *)0x4000E028))
#define UART3_UARTFBRD_REG        (*((volatile uint32 *)0x4000F028))
#define UART4_UARTFBRD_REG        (*((volatile uint32 *)0x40010028))
#define UART5_UARTFBRD_REG        (*((volatile uint32 *)0x40011028))
#define UART6_UARTFBRD_REG        (*((volatile uint32 *)0x40012028))
#define UART7_UARTFBRD_REG        (*((volatile uint32 *)0x40013028))

#define UART0_UARTLCRH_REG        (*((volatile uint32 *)0x4000C02C))
#define UART1_UARTLCRH_REG        (*((volatile uint32 *)0x4000D02C))
#define UART2_UARTLCRH_REG        (*((volatile uint32 *)0x4000E02C))
#define UART3_UARTLCRH_REG        (*((volatile uint32 *)0x4000F02C))
#define UART4_UARTLCRH_REG        (*((volatile uint32 *)0x4001002C))
#define UART5_UARTLCRH_REG        (*((volatile uint32 *)0x4001102C))
#define UART6_UARTLCRH_REG        (*((volatile uint32 *)0x4001202C))
#define UART7_UARTLCRH_REG        (*((volatile uint32 *)0x4001302C))

/*****************************************************************************
PWM Registers
*****************************************************************************/
#define SYSCTL_RCGCPWM_REG        (*((volatile unsigned long *)0x400FE640)) // for PWM Clock generation


/*****************************************************************************
PWM Registers
*****************************************************************************/
#define SYSCTL_RCGCPWM_REG        (*((volatile unsigned long *)0x400FE640)) // for PWM Clock generation
#define SYSCTL_PRPWM_REG          (*((volatile unsigned long *)0x400FEA40)) // for checking if the PWM is ready 
#define SYSCTL_SRPWM_REG          (*((volatile unsigned long *)0x400FE540)) //for reseting the PWM 
/*****************************************************************************/

/*****************************************************************************
PWM0 Registers
****************************************************************************/
#define PWM0_Add                0x40028000

#define PWM0_CTL_REG            (*((volatile uint32 *)0x40028000))
#define PWM0_ENABLE_R           (*((volatile uint32 *)0x40028008))
#define PWM0_0_CTL_R            (*((volatile uint32 *)0x40028040))
#define PWM0_0_GENA_R           (*((volatile uint32 *)0x40028060))
#define PWM0_0_GENB_R           (*((volatile uint32 *)0x40028064))
#define PWM0_0_LOAD_R           (*((volatile uint32 *)0x40028050))
#define PWM0_0_COUNT_R          (*((volatile uint32 *)0x40028054))
#define PWM0_0_CMPA_R           (*((volatile uint32 *)0x40028058))
#define PWM0_0_CMPB_R           (*((volatile uint32 *)0x4002805C))
#define PWM0_1_CTL_R            (*((volatile uint32 *)0x40028080))
#define PWM0_1_GENA_R           (*((volatile uint32 *)0x400280A0))
#define PWM0_1_GENB_R           (*((volatile uint32 *)0x400280A4))
#define PWM0_1_LOAD_R           (*((volatile uint32 *)0x40028090))
#define PWM0_1_COUNT_R          (*((volatile uint32 *)0x40028094))
#define PWM0_1_CMPA_R           (*((volatile uint32 *)0x40028098))
#define PWM0_1_CMPB_R           (*((volatile uint32 *)0x4002809C))
#define PWM0_2_CTL_R            (*((volatile uint32 *)0x400280C0))
#define PWM0_2_GENA_R           (*((volatile uint32 *)0x400280E0))
#define PWM0_2_GENB_R           (*((volatile uint32 *)0x400280E4))
#define PWM0_2_LOAD_R           (*((volatile uint32 *)0x400280D0))
#define PWM0_2_COUNT_R          (*((volatile uint32 *)0x400280D4))
#define PWM0_2_CMPA_R           (*((volatile uint32 *)0x400280D8))
#define PWM0_2_CMPB_R           (*((volatile uint32 *)0x400280DC))
#define PWM0_3_CTL_R            (*((volatile uint32 *)0x40028100))
#define PWM0_3_GENA_R           (*((volatile uint32 *)0x40028120))
#define PWM0_3_GENB_R           (*((volatile uint32 *)0x40028124))
#define PWM0_3_LOAD_R           (*((volatile uint32 *)0x40028110))
#define PWM0_3_COUNT_R          (*((volatile uint32 *)0x40028114))
#define PWM0_3_CMPA_R           (*((volatile uint32 *)0x40028118))
#define PWM0_3_CMPB_R           (*((volatile uint32 *)0x4002811C))


/*****************************************************************************
PWM1 Registers
*****************************************************************************/
#define PWM1_Add                0x40029000

#define PWM1_CTL_REG            (*((volatile uint32 *)0x40029000))
#define PWM1_ENABLE_R           (*((volatile uint32 *)0x40029008))
#define PWM1_0_CTL_R            (*((volatile uint32 *)0x40029040))
#define PWM1_0_GENA_R           (*((volatile uint32 *)0x40029060))
#define PWM1_0_GENB_R           (*((volatile uint32 *)0x40029064))
#define PWM1_0_LOAD_R           (*((volatile uint32 *)0x40029050))
#define PWM1_0_COUNT_R          (*((volatile uint32 *)0x40029054))
#define PWM1_0_CMPA_R           (*((volatile uint32 *)0x40029058))
#define PWM1_0_CMPB_R           (*((volatile uint32 *)0x4002905C))
#define PWM1_1_CTL_R            (*((volatile uint32 *)0x40029080))
#define PWM1_1_GENA_R           (*((volatile uint32 *)0x400290A0))
#define PWM1_1_GENB_R           (*((volatile uint32 *)0x400290A4))
#define PWM1_1_LOAD_R           (*((volatile uint32 *)0x40029090))
#define PWM1_1_COUNT_R          (*((volatile uint32 *)0x40029094))
#define PWM1_1_CMPA_R           (*((volatile uint32 *)0x40029098))
#define PWM1_1_CMPB_R           (*((volatile uint32 *)0x4002909C))
#define PWM1_2_CTL_R            (*((volatile uint32 *)0x400290C0))
#define PWM1_2_GENA_R           (*((volatile uint32 *)0x400290E0))
#define PWM1_2_GENB_R           (*((volatile uint32 *)0x400290E4))
#define PWM1_2_LOAD_R           (*((volatile uint32 *)0x400290D0))
#define PWM1_2_COUNT_R          (*((volatile uint32 *)0x400280D4))
#define PWM1_2_CMPA_R           (*((volatile uint32 *)0x400290D8))
#define PWM1_2_CMPB_R           (*((volatile uint32 *)0x400290DC))
#define PWM1_3_CTL_R            (*((volatile uint32 *)0x40029100))
#define PWM1_3_GENA_R           (*((volatile uint32 *)0x40029120))
#define PWM1_3_GENB_R           (*((volatile uint32 *)0x40029124))
#define PWM1_3_LOAD_R           (*((volatile uint32 *)0x40029110))
#define PWM1_3_COUNT_R          (*((volatile uint32 *)0x40028114))
#define PWM1_3_CMPA_R           (*((volatile uint32 *)0x40029118))
#define PWM1_3_CMPB_R           (*((volatile uint32 *)0x4002911C))
/*****************************************************************************
EEPROM Registers
*****************************************************************************/
#define EEPROM_BASE_ADDRESS           ((volatile uint32 *)0x00020000)
#define EEPROM_RCGCEEPROM_REG        (*((volatile uint32 *)0x400FE658))
#define EEPROM_EEDONE_REG            (*((volatile uint32 *)0x400AF018))
#define EEPROM_EESUPP_REG            (*((volatile uint32 *)0x400AF01C))
#define EEPROM_SREEPROM_REG          (*((volatile uint32 *)0x400FE558))
#define EEPROM_FMA_REG        (*((volatile uint32 *)0x400FD000))
#define EEPROM_FMD_REG        (*((volatile uint32 *)0x400FD004))
#define EEPROM_FMC_REG        (*((volatile uint32 *)0x400FD008))
#define EEPROM_BLOCK_REG        (*((volatile uint32 *)0x400AF004))
#define EEPROM_BOOTCFG_REG     (*((volatile uint32 *)0x400FE1D0))

#endif
