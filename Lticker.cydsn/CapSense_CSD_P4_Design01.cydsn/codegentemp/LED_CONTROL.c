/*******************************************************************************
* File Name: LED_CONTROL.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the LED_CONTROL
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LED_CONTROL.h"
#include "CyLib.h"

uint8 LED_CONTROL_initVar = 0u;


/*******************************************************************************
* Function Name: LED_CONTROL_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default LED_CONTROL configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (LED_CONTROL__QUAD == LED_CONTROL_CONFIG)
        LED_CONTROL_CONTROL_REG =
        (((uint32)(LED_CONTROL_QUAD_ENCODING_MODES     << LED_CONTROL_QUAD_MODE_SHIFT))       |
         ((uint32)(LED_CONTROL_CONFIG                  << LED_CONTROL_MODE_SHIFT)));
    #endif  /* (LED_CONTROL__QUAD == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG)
        LED_CONTROL_CONTROL_REG =
        (((uint32)(LED_CONTROL_PWM_STOP_EVENT          << LED_CONTROL_PWM_STOP_KILL_SHIFT))    |
         ((uint32)(LED_CONTROL_PWM_OUT_INVERT          << LED_CONTROL_INV_OUT_SHIFT))         |
         ((uint32)(LED_CONTROL_PWM_OUT_N_INVERT        << LED_CONTROL_INV_COMPL_OUT_SHIFT))     |
         ((uint32)(LED_CONTROL_PWM_MODE                << LED_CONTROL_MODE_SHIFT)));

        #if (LED_CONTROL__PWM_PR == LED_CONTROL_PWM_MODE)
            LED_CONTROL_CONTROL_REG |=
            ((uint32)(LED_CONTROL_PWM_RUN_MODE         << LED_CONTROL_ONESHOT_SHIFT));

            LED_CONTROL_WriteCounter(LED_CONTROL_PWM_PR_INIT_VALUE);
        #else
            LED_CONTROL_CONTROL_REG |=
            (((uint32)(LED_CONTROL_PWM_ALIGN           << LED_CONTROL_UPDOWN_SHIFT))          |
             ((uint32)(LED_CONTROL_PWM_KILL_EVENT      << LED_CONTROL_PWM_SYNC_KILL_SHIFT)));
        #endif  /* (LED_CONTROL__PWM_PR == LED_CONTROL_PWM_MODE) */

        #if (LED_CONTROL__PWM_DT == LED_CONTROL_PWM_MODE)
            LED_CONTROL_CONTROL_REG |=
            ((uint32)(LED_CONTROL_PWM_DEAD_TIME_CYCLE  << LED_CONTROL_PRESCALER_SHIFT));
        #endif  /* (LED_CONTROL__PWM_DT == LED_CONTROL_PWM_MODE) */

        #if (LED_CONTROL__PWM == LED_CONTROL_PWM_MODE)
            LED_CONTROL_CONTROL_REG |=
            ((uint32)LED_CONTROL_PWM_PRESCALER         << LED_CONTROL_PRESCALER_SHIFT);
        #endif  /* (LED_CONTROL__PWM == LED_CONTROL_PWM_MODE) */
    #endif  /* (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__TIMER == LED_CONTROL_CONFIG)
        LED_CONTROL_CONTROL_REG =
        (((uint32)(LED_CONTROL_TC_PRESCALER            << LED_CONTROL_PRESCALER_SHIFT))   |
         ((uint32)(LED_CONTROL_TC_COUNTER_MODE         << LED_CONTROL_UPDOWN_SHIFT))      |
         ((uint32)(LED_CONTROL_TC_RUN_MODE             << LED_CONTROL_ONESHOT_SHIFT))     |
         ((uint32)(LED_CONTROL_TC_COMP_CAP_MODE        << LED_CONTROL_MODE_SHIFT)));
    #endif  /* (LED_CONTROL__TIMER == LED_CONTROL_CONFIG) */

    /* Set values from customizer to CTRL1 */
    #if (LED_CONTROL__QUAD == LED_CONTROL_CONFIG)
        LED_CONTROL_TRIG_CONTROL1_REG  =
        (((uint32)(LED_CONTROL_QUAD_PHIA_SIGNAL_MODE   << LED_CONTROL_COUNT_SHIFT))       |
         ((uint32)(LED_CONTROL_QUAD_INDEX_SIGNAL_MODE  << LED_CONTROL_RELOAD_SHIFT))      |
         ((uint32)(LED_CONTROL_QUAD_STOP_SIGNAL_MODE   << LED_CONTROL_STOP_SHIFT))        |
         ((uint32)(LED_CONTROL_QUAD_PHIB_SIGNAL_MODE   << LED_CONTROL_START_SHIFT)));
    #endif  /* (LED_CONTROL__QUAD == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG)
        LED_CONTROL_TRIG_CONTROL1_REG  =
        (((uint32)(LED_CONTROL_PWM_SWITCH_SIGNAL_MODE  << LED_CONTROL_CAPTURE_SHIFT))     |
         ((uint32)(LED_CONTROL_PWM_COUNT_SIGNAL_MODE   << LED_CONTROL_COUNT_SHIFT))       |
         ((uint32)(LED_CONTROL_PWM_RELOAD_SIGNAL_MODE  << LED_CONTROL_RELOAD_SHIFT))      |
         ((uint32)(LED_CONTROL_PWM_STOP_SIGNAL_MODE    << LED_CONTROL_STOP_SHIFT))        |
         ((uint32)(LED_CONTROL_PWM_START_SIGNAL_MODE   << LED_CONTROL_START_SHIFT)));
    #endif  /* (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__TIMER == LED_CONTROL_CONFIG)
        LED_CONTROL_TRIG_CONTROL1_REG  =
        (((uint32)(LED_CONTROL_TC_CAPTURE_SIGNAL_MODE  << LED_CONTROL_CAPTURE_SHIFT))     |
         ((uint32)(LED_CONTROL_TC_COUNT_SIGNAL_MODE    << LED_CONTROL_COUNT_SHIFT))       |
         ((uint32)(LED_CONTROL_TC_RELOAD_SIGNAL_MODE   << LED_CONTROL_RELOAD_SHIFT))      |
         ((uint32)(LED_CONTROL_TC_STOP_SIGNAL_MODE     << LED_CONTROL_STOP_SHIFT))        |
         ((uint32)(LED_CONTROL_TC_START_SIGNAL_MODE    << LED_CONTROL_START_SHIFT)));
    #endif  /* (LED_CONTROL__TIMER == LED_CONTROL_CONFIG) */

    /* Set values from customizer to INTR */
    #if (LED_CONTROL__QUAD == LED_CONTROL_CONFIG)
        LED_CONTROL_SetInterruptMode(LED_CONTROL_QUAD_INTERRUPT_MASK);
    #endif  /* (LED_CONTROL__QUAD == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG)
        LED_CONTROL_SetInterruptMode(LED_CONTROL_PWM_INTERRUPT_MASK);
    #endif  /* (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__TIMER == LED_CONTROL_CONFIG)
        LED_CONTROL_SetInterruptMode(LED_CONTROL_TC_INTERRUPT_MASK);
    #endif  /* (LED_CONTROL__TIMER == LED_CONTROL_CONFIG) */

    /* Set other values from customizer */
    #if (LED_CONTROL__TIMER == LED_CONTROL_CONFIG)
        LED_CONTROL_WritePeriod(LED_CONTROL_TC_PERIOD_VALUE );

        #if (LED_CONTROL__COUNT_DOWN == LED_CONTROL_TC_COUNTER_MODE)
            LED_CONTROL_WriteCounter(LED_CONTROL_TC_PERIOD_VALUE );
        #endif  /* (LED_CONTROL__COUNT_DOWN == LED_CONTROL_TC_COUNTER_MODE) */

        #if (LED_CONTROL__COMPARE == LED_CONTROL_TC_COMP_CAP_MODE)
            LED_CONTROL_WriteCompare(LED_CONTROL_TC_COMPARE_VALUE);

            #if (1u == LED_CONTROL_TC_COMPARE_SWAP)
                LED_CONTROL_SetCompareSwap(1u);
                LED_CONTROL_WriteCompareBuf(LED_CONTROL_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == LED_CONTROL_TC_COMPARE_SWAP) */
        #endif  /* (LED_CONTROL__COMPARE == LED_CONTROL_TC_COMP_CAP_MODE) */
    #endif  /* (LED_CONTROL__TIMER == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG)
        LED_CONTROL_WritePeriod(LED_CONTROL_PWM_PERIOD_VALUE );
        LED_CONTROL_WriteCompare(LED_CONTROL_PWM_COMPARE_VALUE);

        #if (1u == LED_CONTROL_PWM_COMPARE_SWAP)
            LED_CONTROL_SetCompareSwap(1u);
            LED_CONTROL_WriteCompareBuf(LED_CONTROL_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == LED_CONTROL_PWM_COMPARE_SWAP) */

        #if (1u == LED_CONTROL_PWM_PERIOD_SWAP)
            LED_CONTROL_SetPeriodSwap(1u);
            LED_CONTROL_WritePeriodBuf(LED_CONTROL_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == LED_CONTROL_PWM_PERIOD_SWAP) */

        /* Set values from customizer to CTRL2 */
        #if (LED_CONTROL__PWM_PR == LED_CONTROL_PWM_MODE)
            LED_CONTROL_TRIG_CONTROL2_REG =
                    (LED_CONTROL_CC_MATCH_NO_CHANGE    |
                    LED_CONTROL_OVERLOW_NO_CHANGE      |
                    LED_CONTROL_UNDERFLOW_NO_CHANGE);
        #else
            #if (LED_CONTROL__LEFT == LED_CONTROL_PWM_ALIGN)
                LED_CONTROL_TRIG_CONTROL2_REG = LED_CONTROL_PWM_MODE_LEFT;
            #endif  /* ( LED_CONTROL_PWM_LEFT == LED_CONTROL_PWM_ALIGN) */

            #if (LED_CONTROL__RIGHT == LED_CONTROL_PWM_ALIGN)
                LED_CONTROL_WriteCounter(LED_CONTROL_PWM_PERIOD_VALUE);
                LED_CONTROL_TRIG_CONTROL2_REG = LED_CONTROL_PWM_MODE_RIGHT;
            #endif  /* ( LED_CONTROL_PWM_RIGHT == LED_CONTROL_PWM_ALIGN) */

            #if (LED_CONTROL__CENTER == LED_CONTROL_PWM_ALIGN)
                LED_CONTROL_TRIG_CONTROL2_REG = LED_CONTROL_PWM_MODE_CENTER;
            #endif  /* ( LED_CONTROL_PWM_CENTER == LED_CONTROL_PWM_ALIGN) */

            #if (LED_CONTROL__ASYMMETRIC == LED_CONTROL_PWM_ALIGN)
                LED_CONTROL_TRIG_CONTROL2_REG = LED_CONTROL_PWM_MODE_ASYM;
            #endif  /* (LED_CONTROL__ASYMMETRIC == LED_CONTROL_PWM_ALIGN) */
        #endif  /* (LED_CONTROL__PWM_PR == LED_CONTROL_PWM_MODE) */
    #endif  /* (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG) */
}


/*******************************************************************************
* Function Name: LED_CONTROL_Enable
********************************************************************************
*
* Summary:
*  Enables the LED_CONTROL.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    LED_CONTROL_BLOCK_CONTROL_REG |= LED_CONTROL_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG)
        #if (0u == LED_CONTROL_PWM_START_SIGNAL_PRESENT)
            LED_CONTROL_TriggerCommand(LED_CONTROL_MASK, LED_CONTROL_CMD_START);
        #endif /* (0u == LED_CONTROL_PWM_START_SIGNAL_PRESENT) */
    #endif /* (LED_CONTROL__PWM_SEL == LED_CONTROL_CONFIG) */

    #if (LED_CONTROL__TIMER == LED_CONTROL_CONFIG)
        #if (0u == LED_CONTROL_TC_START_SIGNAL_PRESENT)
            LED_CONTROL_TriggerCommand(LED_CONTROL_MASK, LED_CONTROL_CMD_START);
        #endif /* (0u == LED_CONTROL_TC_START_SIGNAL_PRESENT) */
    #endif /* (LED_CONTROL__TIMER == LED_CONTROL_CONFIG) */
}


/*******************************************************************************
* Function Name: LED_CONTROL_Start
********************************************************************************
*
* Summary:
*  Initializes the LED_CONTROL with default customizer
*  values when called the first time and enables the LED_CONTROL.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_CONTROL_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time LED_CONTROL_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the LED_CONTROL_Start() routine.
*
*******************************************************************************/
void LED_CONTROL_Start(void)
{
    if (0u == LED_CONTROL_initVar)
    {
        LED_CONTROL_Init();
        LED_CONTROL_initVar = 1u;
    }

    LED_CONTROL_Enable();
}


/*******************************************************************************
* Function Name: LED_CONTROL_Stop
********************************************************************************
*
* Summary:
*  Disables the LED_CONTROL.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_BLOCK_CONTROL_REG &= (uint32)~LED_CONTROL_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the LED_CONTROL. This function is used when
*  configured as a generic LED_CONTROL and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the LED_CONTROL to operate in
*   Values:
*   - LED_CONTROL_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - LED_CONTROL_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - LED_CONTROL_MODE_QUAD - Quadrature decoder
*         - LED_CONTROL_MODE_PWM - PWM
*         - LED_CONTROL_MODE_PWM_DT - PWM with dead time
*         - LED_CONTROL_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_MODE_MASK;
    LED_CONTROL_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - LED_CONTROL_MODE_X1 - Counts on phi 1 rising
*         - LED_CONTROL_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - LED_CONTROL_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_QUAD_MODE_MASK;
    LED_CONTROL_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - LED_CONTROL_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - LED_CONTROL_PRESCALE_DIVBY2    - Divide by 2
*         - LED_CONTROL_PRESCALE_DIVBY4    - Divide by 4
*         - LED_CONTROL_PRESCALE_DIVBY8    - Divide by 8
*         - LED_CONTROL_PRESCALE_DIVBY16   - Divide by 16
*         - LED_CONTROL_PRESCALE_DIVBY32   - Divide by 32
*         - LED_CONTROL_PRESCALE_DIVBY64   - Divide by 64
*         - LED_CONTROL_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_PRESCALER_MASK;
    LED_CONTROL_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the LED_CONTROL runs
*  continuously or stops when terminal count is reached.  By default the
*  LED_CONTROL operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_ONESHOT_MASK;
    LED_CONTROL_CONTROL_REG |= ((uint32)((oneShotEnable & LED_CONTROL_1BIT_MASK) <<
                                                               LED_CONTROL_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetPWMMode(uint32 modeMask)
{
    LED_CONTROL_TRIG_CONTROL2_REG = (modeMask & LED_CONTROL_6BIT_MASK);
}



/*******************************************************************************
* Function Name: LED_CONTROL_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_PWM_SYNC_KILL_MASK;
    LED_CONTROL_CONTROL_REG |= ((uint32)((syncKillEnable & LED_CONTROL_1BIT_MASK)  <<
                                               LED_CONTROL_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_PWM_STOP_KILL_MASK;
    LED_CONTROL_CONTROL_REG |= ((uint32)((stopOnKillEnable & LED_CONTROL_1BIT_MASK)  <<
                                                         LED_CONTROL_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_PRESCALER_MASK;
    LED_CONTROL_CONTROL_REG |= ((uint32)((deadTime & LED_CONTROL_8BIT_MASK) <<
                                                          LED_CONTROL_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - LED_CONTROL_INVERT_LINE   - Inverts the line output
*         - LED_CONTROL_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_INV_OUT_MASK;
    LED_CONTROL_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: LED_CONTROL_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_WriteCounter(uint32 count)
{
    LED_CONTROL_COUNTER_REG = (count & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 LED_CONTROL_ReadCounter(void)
{
    return (LED_CONTROL_COUNTER_REG & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - LED_CONTROL_COUNT_UP       - Counts up
*     - LED_CONTROL_COUNT_DOWN     - Counts down
*     - LED_CONTROL_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - LED_CONTROL_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_UPDOWN_MASK;
    LED_CONTROL_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_WritePeriod(uint32 period)
{
    LED_CONTROL_PERIOD_REG = (period & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 LED_CONTROL_ReadPeriod(void)
{
    return (LED_CONTROL_PERIOD_REG & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_RELOAD_CC_MASK;
    LED_CONTROL_CONTROL_REG |= (swapEnable & LED_CONTROL_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_WritePeriodBuf(uint32 periodBuf)
{
    LED_CONTROL_PERIOD_BUF_REG = (periodBuf & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 LED_CONTROL_ReadPeriodBuf(void)
{
    return (LED_CONTROL_PERIOD_BUF_REG & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_CONTROL_REG &= (uint32)~LED_CONTROL_RELOAD_PERIOD_MASK;
    LED_CONTROL_CONTROL_REG |= ((uint32)((swapEnable & LED_CONTROL_1BIT_MASK) <<
                                                            LED_CONTROL_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_WriteCompare(uint32 compare)
{
    #if (LED_CONTROL_CY_TCPWM_V2)
        uint32 currentMode;
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */

    #if (LED_CONTROL_CY_TCPWM_V2)
        currentMode = ((LED_CONTROL_CONTROL_REG & LED_CONTROL_UPDOWN_MASK) >> LED_CONTROL_UPDOWN_SHIFT);

        if (LED_CONTROL__COUNT_DOWN == currentMode)
        {
            LED_CONTROL_COMP_CAP_REG = ((compare + 1u) & LED_CONTROL_16BIT_MASK);
        }
        else if (LED_CONTROL__COUNT_UP == currentMode)
        {
            LED_CONTROL_COMP_CAP_REG = ((compare - 1u) & LED_CONTROL_16BIT_MASK);
        }
        else
        {
            LED_CONTROL_COMP_CAP_REG = (compare & LED_CONTROL_16BIT_MASK);
        }
    #else
        LED_CONTROL_COMP_CAP_REG = (compare & LED_CONTROL_16BIT_MASK);
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 LED_CONTROL_ReadCompare(void)
{
    #if (LED_CONTROL_CY_TCPWM_V2)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */

    #if (LED_CONTROL_CY_TCPWM_V2)
        currentMode = ((LED_CONTROL_CONTROL_REG & LED_CONTROL_UPDOWN_MASK) >> LED_CONTROL_UPDOWN_SHIFT);

        if (LED_CONTROL__COUNT_DOWN == currentMode)
        {
            regVal = ((LED_CONTROL_COMP_CAP_REG - 1u) & LED_CONTROL_16BIT_MASK);
        }
        else if (LED_CONTROL__COUNT_UP == currentMode)
        {
            regVal = ((LED_CONTROL_COMP_CAP_REG + 1u) & LED_CONTROL_16BIT_MASK);
        }
        else
        {
            regVal = (LED_CONTROL_COMP_CAP_REG & LED_CONTROL_16BIT_MASK);
        }
        return (regVal);
    #else
        return (LED_CONTROL_COMP_CAP_REG & LED_CONTROL_16BIT_MASK);
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: LED_CONTROL_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_WriteCompareBuf(uint32 compareBuf)
{
    #if (LED_CONTROL_CY_TCPWM_V2)
        uint32 currentMode;
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */

    #if (LED_CONTROL_CY_TCPWM_V2)
        currentMode = ((LED_CONTROL_CONTROL_REG & LED_CONTROL_UPDOWN_MASK) >> LED_CONTROL_UPDOWN_SHIFT);

        if (LED_CONTROL__COUNT_DOWN == currentMode)
        {
            LED_CONTROL_COMP_CAP_BUF_REG = ((compareBuf + 1u) & LED_CONTROL_16BIT_MASK);
        }
        else if (LED_CONTROL__COUNT_UP == currentMode)
        {
            LED_CONTROL_COMP_CAP_BUF_REG = ((compareBuf - 1u) & LED_CONTROL_16BIT_MASK);
        }
        else
        {
            LED_CONTROL_COMP_CAP_BUF_REG = (compareBuf & LED_CONTROL_16BIT_MASK);
        }
    #else
        LED_CONTROL_COMP_CAP_BUF_REG = (compareBuf & LED_CONTROL_16BIT_MASK);
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 LED_CONTROL_ReadCompareBuf(void)
{
    #if (LED_CONTROL_CY_TCPWM_V2)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */

    #if (LED_CONTROL_CY_TCPWM_V2)
        currentMode = ((LED_CONTROL_CONTROL_REG & LED_CONTROL_UPDOWN_MASK) >> LED_CONTROL_UPDOWN_SHIFT);

        if (LED_CONTROL__COUNT_DOWN == currentMode)
        {
            regVal = ((LED_CONTROL_COMP_CAP_BUF_REG - 1u) & LED_CONTROL_16BIT_MASK);
        }
        else if (LED_CONTROL__COUNT_UP == currentMode)
        {
            regVal = ((LED_CONTROL_COMP_CAP_BUF_REG + 1u) & LED_CONTROL_16BIT_MASK);
        }
        else
        {
            regVal = (LED_CONTROL_COMP_CAP_BUF_REG & LED_CONTROL_16BIT_MASK);
        }
        return (regVal);
    #else
        return (LED_CONTROL_COMP_CAP_BUF_REG & LED_CONTROL_16BIT_MASK);
    #endif /* (LED_CONTROL_CY_TCPWM_V2) */
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 LED_CONTROL_ReadCapture(void)
{
    return (LED_CONTROL_COMP_CAP_REG & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 LED_CONTROL_ReadCaptureBuf(void)
{
    return (LED_CONTROL_COMP_CAP_BUF_REG & LED_CONTROL_16BIT_MASK);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LED_CONTROL_TRIG_LEVEL     - Level
*     - LED_CONTROL_TRIG_RISING    - Rising edge
*     - LED_CONTROL_TRIG_FALLING   - Falling edge
*     - LED_CONTROL_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_TRIG_CONTROL1_REG &= (uint32)~LED_CONTROL_CAPTURE_MASK;
    LED_CONTROL_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LED_CONTROL_TRIG_LEVEL     - Level
*     - LED_CONTROL_TRIG_RISING    - Rising edge
*     - LED_CONTROL_TRIG_FALLING   - Falling edge
*     - LED_CONTROL_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_TRIG_CONTROL1_REG &= (uint32)~LED_CONTROL_RELOAD_MASK;
    LED_CONTROL_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LED_CONTROL_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LED_CONTROL_TRIG_LEVEL     - Level
*     - LED_CONTROL_TRIG_RISING    - Rising edge
*     - LED_CONTROL_TRIG_FALLING   - Falling edge
*     - LED_CONTROL_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_TRIG_CONTROL1_REG &= (uint32)~LED_CONTROL_START_MASK;
    LED_CONTROL_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LED_CONTROL_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LED_CONTROL_TRIG_LEVEL     - Level
*     - LED_CONTROL_TRIG_RISING    - Rising edge
*     - LED_CONTROL_TRIG_FALLING   - Falling edge
*     - LED_CONTROL_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_TRIG_CONTROL1_REG &= (uint32)~LED_CONTROL_STOP_MASK;
    LED_CONTROL_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LED_CONTROL_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - LED_CONTROL_TRIG_LEVEL     - Level
*     - LED_CONTROL_TRIG_RISING    - Rising edge
*     - LED_CONTROL_TRIG_FALLING   - Falling edge
*     - LED_CONTROL_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_TRIG_CONTROL1_REG &= (uint32)~LED_CONTROL_COUNT_MASK;
    LED_CONTROL_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << LED_CONTROL_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - LED_CONTROL_CMD_CAPTURE    - Trigger Capture command
*     - LED_CONTROL_CMD_RELOAD     - Trigger Reload command
*     - LED_CONTROL_CMD_STOP       - Trigger Stop command
*     - LED_CONTROL_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    LED_CONTROL_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LED_CONTROL_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the LED_CONTROL.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - LED_CONTROL_STATUS_DOWN    - Set if counting down
*     - LED_CONTROL_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 LED_CONTROL_ReadStatus(void)
{
    return ((LED_CONTROL_STATUS_REG >> LED_CONTROL_RUNNING_STATUS_SHIFT) |
            (LED_CONTROL_STATUS_REG & LED_CONTROL_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - LED_CONTROL_INTR_MASK_TC       - Terminal count mask
*     - LED_CONTROL_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetInterruptMode(uint32 interruptMask)
{
    LED_CONTROL_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: LED_CONTROL_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - LED_CONTROL_INTR_MASK_TC       - Terminal count mask
*     - LED_CONTROL_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 LED_CONTROL_GetInterruptSourceMasked(void)
{
    return (LED_CONTROL_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: LED_CONTROL_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - LED_CONTROL_INTR_MASK_TC       - Terminal count mask
*     - LED_CONTROL_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 LED_CONTROL_GetInterruptSource(void)
{
    return (LED_CONTROL_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: LED_CONTROL_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - LED_CONTROL_INTR_MASK_TC       - Terminal count mask
*     - LED_CONTROL_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_ClearInterrupt(uint32 interruptMask)
{
    LED_CONTROL_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: LED_CONTROL_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - LED_CONTROL_INTR_MASK_TC       - Terminal count mask
*     - LED_CONTROL_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void LED_CONTROL_SetInterrupt(uint32 interruptMask)
{
    LED_CONTROL_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
