/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuWait.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : Wait
**     Version     : Component 01.091, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-01-30, 15:10, # CodeGen: 729
**     Abstract    :
**          Implements busy waiting routines.
**     Settings    :
**          Component name                                 : McuWait
**          Manual Clock Values                            : Disabled
**          Delay100usFunction                             : Delay100US
**          RTOS                                           : Enabled
**            RTOS                                         : McuRTOS
**          Watchdog                                       : Disabled
**     Contents    :
**         Wait10Cycles   - void McuWait_Wait10Cycles(void);
**         Wait100Cycles  - void McuWait_Wait100Cycles(void);
**         WaitCycles     - void McuWait_WaitCycles(uint32_t cycles);
**         WaitLongCycles - void McuWait_WaitLongCycles(uint32_t cycles);
**         Waitms         - void McuWait_Waitms(uint32_t ms);
**         Waitus         - void McuWait_Waitus(uint32_t us);
**         Waitns         - void McuWait_Waitns(uint32_t ns);
**         WaitOSms       - void McuWait_WaitOSms(void);
**         Init           - void McuWait_Init(void);
**         Deinit         - void McuWait_Deinit(void);
**
** * Copyright (c) 2013-2021, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file McuWait.h
** @version 01.00
** @brief
**          Implements busy waiting routines.
*/         
/*!
**  @addtogroup McuWait_module McuWait module documentation
**  @{
*/         

#ifndef __McuWait_H
#define __McuWait_H

/* MODULE McuWait. */
#include "McuLib.h" /* SDK and API used */
#include "McuWaitconfig.h" /* configuration */
#if McuLib_CONFIG_CPU_IS_ESP32
  #include "rom/ets_sys.h"
#endif

/* other includes needed */
#if McuWait_CONFIG_USE_RTOS_WAIT
  /* include RTOS header files */
  #include "McuRTOS.h"
  #if McuLib_CONFIG_CPU_IS_ESP32
    #include "freertos/FreeRTOS.h" /* for vTaskDelay() */
    #include "freertos/task.h"
  #else
    #include "FreeRTOS.h" /* for vTaskDelay() */
    #include "task.h"
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
  #define McuWait_INSTR_CLOCK_HZ       CPU_CORE_CLK_HZ /* for Kinetis, use core clock as base for instruction execution */
#else
  extern uint32_t SystemCoreClock; /* clock frequency variable defined system_<device>.h of the SDK */
  #define McuWait_INSTR_CLOCK_HZ       SystemCoreClock  /* core clock frequency in Hz */
#endif
#define McuWait_NofCyclesMs(ms, hz)  ((ms)*((hz)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define McuWait_NofCyclesUs(us, hz)  ((us)*(((hz)/1000)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define McuWait_NofCyclesNs(ns, hz)  (((ns)*(((hz)/1000)/1000))/1000) /* calculates the needed cycles based on bus clock frequency */

#define McuWait_WAIT_C(cycles) \
     ( (cycles)<=10 ? \
          McuWait_Wait10Cycles() \
        : McuWait_WaitCycles(cycles) \
      )                                      /*!< wait for some cycles */


void McuWait_Wait10Cycles(void);
/*
** ===================================================================
**     Method      :  Wait10Cycles (component Wait)
**
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void McuWait_Wait100Cycles(void);
/*
** ===================================================================
**     Method      :  Wait100Cycles (component Wait)
**
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void McuWait_WaitCycles(uint32_t cycles);
/*
** ===================================================================
**     Method      :  WaitCycles (component Wait)
**
**     Description :
**         Wait for a specified number of CPU cycles.
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

void McuWait_Waitms(uint32_t ms);
/*
** ===================================================================
**     Method      :  Waitms (component Wait)
**
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#if McuLib_CONFIG_CPU_IS_ESP32
  #define McuWait_Waitus(us)  esp_rom_delay_us(us)
#else
  #define McuWait_Waitus(us)  \
        /*lint -save -e(505,506,522) Constant value Boolean, Redundant left argument to comma. */\
       (  ((McuWait_NofCyclesUs((us),McuWait_INSTR_CLOCK_HZ)==0)||(us)==0) ? \
          (void)0 : \
          ( ((us)/1000)==0 ? (void)0 : McuWait_Waitms(((us)/1000))) \
          , (McuWait_NofCyclesUs(((us)%1000), McuWait_INSTR_CLOCK_HZ)==0) ? (void)0 : \
            McuWait_WAIT_C(McuWait_NofCyclesUs(((us)%1000), McuWait_INSTR_CLOCK_HZ)) \
       /*lint -restore */\
       )
#endif
/*
** ===================================================================
**     Method      :  Waitus (component Wait)
**
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#define McuWait_Waitns(ns)  \
        /*lint -save -e(505,506,522) Constant value Boolean, Redundant left argument to comma. */\
       (  ((McuWait_NofCyclesNs((ns), McuWait_INSTR_CLOCK_HZ)==0)||(ns)==0) ? \
          (void)0 : \
          McuWait_Waitus((ns)/1000) \
          , (McuWait_NofCyclesNs((ns)%1000, McuWait_INSTR_CLOCK_HZ)==0) ? \
              (void)0 : \
              McuWait_WAIT_C(McuWait_NofCyclesNs(((ns)%1000), McuWait_INSTR_CLOCK_HZ)) \
       /*lint -restore */\
       )
/*
** ===================================================================
**     Method      :  Waitns (component Wait)
**
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/

#if McuWait_CONFIG_USE_RTOS_WAIT
  /* use FreeRTOS API, but only if scheduler is running */
  #define McuWait_WaitOSms(ms) xTaskGetSchedulerState()==taskSCHEDULER_RUNNING ? vTaskDelay(pdMS_TO_TICKS(ms)) : McuWait_Waitms(ms)
#else
  #define McuWait_WaitOSms(ms)  McuWait_Waitms(ms) /* use normal wait */
#endif
/*
** ===================================================================
**     Method      :  WaitOSms (component Wait)
**
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void McuWait_WaitLongCycles(uint32_t cycles);
/*
** ===================================================================
**     Method      :  WaitLongCycles (component Wait)
**
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

void McuWait_Init(void);
/*
** ===================================================================
**     Method      :  Init (component Wait)
**
**     Description :
**         Driver initialization routine.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void McuWait_Deinit(void);
/*
** ===================================================================
**     Method      :  Deinit (component Wait)
**
**     Description :
**         Driver de-initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END McuWait. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __McuWait_H */
/*!
** @}
*/
