/** 
 * @mainpage
 * @section Introduction
 * Tasked with designing and building a machine with an embedded computer, 
 * several sensors, a custom circuit board, one or more actuators, a control 
 * system, and digital communication, we decided to build an automated 
 * soda/beer can opener. The premise being that tabs can be difficult to get 
 * under without sufficiently long nails. Additionally, both soda and beer are 
 * classic, kick-you-feet-up and relax beverages, so why not make the experience 
 * of drinking your favorite pop hassle free with a machine that opens it for you?
 *  The automated can opener aims to address the needs of the casual beer/soda 
 * drinker looking for a novel and effortless can opening experience to begin their 
 * relaxing drink. The device includes several sensors, necessary for safety and 
 * function, that communicate with an onboard micro-controller. Connected via a 
 * custom PCB, the micro-controller processes data from the sensors to dictate the 
 * motor movements required to position and open the can.
 * 
 * Given the limited scope and timeframe of this one quarter class, we wanted to 
 * create the base mechanisms for the can opener with reach goals including a 
 * mountable and working can opening mechanism, display with details about the can, 
 * and an auto-loading mechanism. 
 * 
 * 
 * On this site, we are hosting the documentation for all of our code
 * 
 * @section Demo
 * \htmlonly
 * <iframe width="560" height="315" src="https://www.youtube.com/embed/Jv3bKP2x2E8" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
 * \endhtmlonly
 * 
 * @section Tasks
 * These are the tasks that are used for our FreeRTOS operating system.
 * 
 * FreeRTOS used from @b https://github.com/stm32duino/STM32FreeRTOS
 * 
 * - taskEncoder.h
 * - taskLimitSwitch.h
 * - taskMoveMachine.h
 * - taskPhotoInterrupt.h
 * - taskTemp.h
 * - taskWriteToDisplay.h
 * 
 * @section Classes
 * These classes represent the custom drivers that we wrote for this project (and one from
 * Professor Ridgely in @b https://github.com/spluttflob/ME507-Support - thank you for that)
 * 
 * - LimitSwitch
 * - MotorDriver
 * - StepperDriver
 * - TempSensor
 * - STM32Encoder - from Prof. Ridgely
 * 
 * 
 * @author Ben Bons, Hunter Morse, Kyle Van Housen
 * 
 * @date Fall 2021
 * 
 * @paragraph Attributions
 * Style from @b https://github.com/kcwongjoe/doxygen_theme_flat_design under the MIT license
 **/