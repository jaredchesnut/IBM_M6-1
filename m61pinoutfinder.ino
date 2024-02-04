/**
  *****************************************************************************
  Module        ButtonMatrix
  @file         Example01_pressed.ino
  -----------------------------------------------------------------------------
  @brief        Example showing absolute basic button matrix usage of the
                isPressed() method.
  -----------------------------------------------------------------------------
  @author       Rene Richter
  @date         21.01.2024
  @modified     -
  @copyright    (c) 2023-2024 Rene Richter
  @license      This library is free software; you can redistribute it and/or
                modify it under the terms of the GNU Lesser General Public
                License as published by the Free Software Foundation; version
                2.1 of the License.

                This library is distributed in the hope that it will be useful,
                but WITHOUT ANY WARRANTY; without even the implied warranty of
                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
                See the GNU Lesser General Public License for more details.
  *****************************************************************************
*/


#include <Arduino.h>
#include "ButtonMatrix.h" /** Include this header in order to work with the button matrix */



/** Everything in the ButtonMatrix library is within this namespace */
using namespace RSys;


static const uint32_t c_uiMonitorBaud = 115200; // USB monitoring baud rate

// -------------
// Button matrix #jkc here's what I changed
// -------------


const uint8_t COLS = 18; /** Number of button matrix columns */
const uint8_t ROWS = 11; /** Number of button matrix rows */
//for Teensy 2.0++ - will be forced to move to something more modern, RPI2040?
uint8_t colPins[COLS] = {9, 45, 8, 17, 7, 16, 6, 15, 5, 14, 4, 13, 3, 12, 2, 11, 1, 10}; /** Button matrix column pins */
uint8_t rowPins[ROWS] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 0}; /** Button matrix row pins */

/** Button matrix button definitons  */
RSys::Button buttons[ROWS][COLS] = {
    { (0), (1), (2), (3), (4), (5), (6), (7), (8), (9), (10), (11), (12), (13), (14), (15), (16), (17) },
    { (18), (19), (20), (21), (22), (23), (24), (25), (26), (27), (28), (29), (30), (31), (32), (33), (34), (35) },
    { (36), (37), (38), (39), (40), (41), (42), (43), (44), (45), (46), (47), (48), (49), (50), (51), (52), (53) },
    { (54), (55), (56), (57), (58), (59), (60), (61), (62), (63), (64), (65), (66), (67), (68), (69), (70), (71) },
    { (72), (73), (74), (75), (76), (77), (78), (79), (80), (81), (82), (83), (84), (85), (86), (87), (88), (89) },
    { (90), (91), (92), (93), (94), (95), (96), (97), (98), (99), (100), (101), (102), (103), (104), (105), (106), (107) },
    { (108), (109), (110), (111), (112), (113), (114), (115), (116), (117), (118), (119), (120), (121), (122), (123), (124), (125) },
    { (126), (127), (128), (129), (130), (131), (132), (133), (134), (135), (136), (137), (138), (139), (140), (141), (142), (143) },
    { (144), (145), (146), (147), (148), (149), (150), (151), (152), (153), (154), (155), (156), (157), (158), (159), (160), (161) },
    { (162), (163), (164), (165), (166), (167), (168), (169), (170), (171), (172), (173), (174), (175), (176), (177), (178), (179) },
    { (180), (181), (182), (183), (184), (185), (186), (187), (188), (189), (190), (191), (192), (193), (194), (195), (196), (197) }
  };

ButtonMatrix matrix((Button*)buttons, rowPins, colPins, ROWS, COLS);


void setup()
{
    Serial.begin(c_uiMonitorBaud);
    
    matrix.init();  /** Initialize the ButtonMatrix*/
}


void loop()
{
    Button* pButton = NULL;

    // Get the number of buttons in the matrix
    const uint16_t numButtons = matrix.getNumButtons();

    // Here we are just querying

    // Make sure to update the matrix frequently. There is a scan interval that defaults to 20ms but can be adjusted by matrix.setScanInterval(..).
    // The update doesn't do anything if the scan interval has not yes elapsed (debouncing and mc load reduction)
    if (matrix.update())
    {  
        // There was a change in any of the buttons  

        // Scan all buttons, except the last one
        for (uint16_t idx = 0; idx < numButtons; idx++)
        {        
            pButton = matrix.getButton(idx);    
            if (pButton->isPressed())
            {
                // Button is pressed
               Serial.print("Button pressed: ");Serial.println(pButton->getNumber());

               // For a more sophisticated example see Example02_fell_rose_lp example!
            }             
        }
    }

}
