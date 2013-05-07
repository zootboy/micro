using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace rgbBargraphDisplay
    {
    using usbGenericHidCommunications;

    class rgbBargraphDevice : usbGenericHidCommunication
        {
        // Class constructor - place any initialisation here
        public rgbBargraphDevice(int vid, int pid) : base(vid, pid)
            {
            // Set the RGB Led brightness to default
            rgbLedRedBrightness = new Byte[16];
            rgbLedGreenBrightness = new Byte[16];
            rgbLedBlueBrightness = new Byte[16];

            for (int ledNumber = 0; ledNumber < 16; ledNumber++)
                {
                rgbLedRedBrightness[ledNumber] = 0;
                rgbLedGreenBrightness[ledNumber] = 0;
                rgbLedBlueBrightness[ledNumber] = 0;
                }
            }

        // Arrays for holding the LED brightness values
        private byte[] rgbLedRedBrightness;
        private byte[] rgbLedGreenBrightness;
        private byte[] rgbLedBlueBrightness;

        // Method to set the LED brightness levels
        public void setLedBrightness(int ledNumber, byte red, byte green, byte blue)
            {
            // Here we just update the arrays, we don't write then to the device
            rgbLedRedBrightness[ledNumber] = red;
            rgbLedGreenBrightness[ledNumber] = green;
            rgbLedBlueBrightness[ledNumber] = blue;
            }

        // Method to write the LED brightness values to the device
        public void writeLedBrightness()
            {
            // Declare our output buffer
            Byte[] outputBuffer = new Byte[65];
 
            // Byte 0 must be set to 0
            outputBuffer[0] = 0;
 
            // Byte 1 must be set to our command
            outputBuffer[1] = 0x80;

            // Fill the rest of the buffer with the brightness data
            for (int ledNumber = 0; ledNumber < 16; ledNumber++)
                {
                outputBuffer[((3*ledNumber)+2)] = rgbLedRedBrightness[ledNumber];
                outputBuffer[((3*ledNumber)+3)] = rgbLedGreenBrightness[ledNumber];
                outputBuffer[((3*ledNumber)+4)] = rgbLedBlueBrightness[ledNumber];
                }

            // Perform the write command
            writeRawReportToDevice(outputBuffer);
            }

        // Method to set the LED fade off speed
        public void setLedFadeOffSpeed(int fadeOffSpeed)
            {
            // Range check 0 - 255
            if (fadeOffSpeed > 255) fadeOffSpeed = 255;

            // Declare our output buffer
            Byte[] outputBuffer = new Byte[65];

            // Byte 0 must be set to 0
            outputBuffer[0] = 0;

            // Byte 1 must be set to our command
            outputBuffer[1] = 0x81;

            // Fill the rest of the buffer with the brightness data
            for (int ledNumber = 0; ledNumber < 16; ledNumber++)
                {
                outputBuffer[ledNumber + 2] = (Byte)fadeOffSpeed;
                }

            // Perform the write command
            writeRawReportToDevice(outputBuffer);
            }
        }
    }
