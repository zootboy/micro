using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using CoreAudioApi;

namespace rgbBargraphDisplay
    {
    public partial class Form1 : Form
        {

        public bool serAttach = false;

        public Form1()
            {
            InitializeComponent();


            this.usbToolStripStatusLabel.Text = "RGB Bargraph Device Detached";

            // Serial stuff.
            try
            {
                //serSerialPort.PortName = "COM10";
                serSerialPort.Open();
                serAttach = true;
                this.usbToolStripStatusLabel.Text = "Serial port device attached.";

            }
            catch (Exception exe)
            {
                //MessageBox.Show("ERROR: " + exe);
                serAttach = false;
                this.usbToolStripStatusLabel.Text = "Serial port device not found...";

            }

            // Initialise the status strip text
            //this.usbToolStripStatusLabel.Text = "RGB Bargraph Device Detached";

            // Create the USB reference device object (passing VID and PID)
            theRgbBargraphDevice = new rgbBargraphDevice(0x04D8, 0x0100);

            // Register for device change notifications
            theRgbBargraphDevice.registerForDeviceNotifications(this.Handle);

            // Add a listener for usb events
            theRgbBargraphDevice.usbEvent +=
                new rgbBargraphDevice.usbEventsHandler(usbEvent_receiver);

            // Perform an initial search for the target device
            theRgbBargraphDevice.findTargetDevice();

            // Initialise the core audio API
            MMDeviceEnumerator devEnum = new MMDeviceEnumerator();
            defaultDevice = devEnum.GetDefaultAudioEndpoint(EDataFlow.eRender, ERole.eMultimedia);

            // Set the starting value for the LED fade off speed
            theRgbBargraphDevice.setLedFadeOffSpeed((int)ledFadeOffSpeedTrackBar.Value);
            }

        // Create an instance of the USB device
        private rgbBargraphDevice theRgbBargraphDevice;

        // Create an instance of the default audio device
        private MMDevice defaultDevice;

        // Callback method for WndProc
        protected override void WndProc(ref Message m)
            {
            // Pass the message to our message handler
            theRgbBargraphDevice.handleDeviceNotificationMessages(m);

            // Pass the message on to the base WndProc
            base.WndProc(ref m);
            }

        // Listener for USB events
        private void usbEvent_receiver(object o, EventArgs e)
            {
            // Check the status of the USB device and update the form accordingly
            if (theRgbBargraphDevice.isDeviceAttached)
                {
                // Device is attached, do tasks here
                this.usbToolStripStatusLabel.Text = "RGB Bargraph Device Attached";
                }
            else
                {
                // Device is detached, do tasks here
                this.usbToolStripStatusLabel.Text = "RGB Bargraph Device Detached";
                }
            }

        // Globals for bar levels
        Int64 oldBarLevel = 0;
        Int64 currentBarLevel = 0;
        
        Int64 oldLeftBarLevel = 0;
        Int64 currentLeftBarLevel = 0;
        Int64 oldRightBarLevel = 0;
        Int64 currentRightBarLevel = 0;
        
        Int64 dampingCounter = 0;

        private void displayUpdateTimer_Tick(object sender, EventArgs e)
            {
            // Variables for storing the volume level percentages
            Int64 leftVolumeLevelPercent;
            Int64 rightVolumeLevelPercent;
            Int64 averageVolumeLevelPercent;

            // Variables for storing the volume level decibels
            Int64 leftVolumeLevelDecibels;
            Int64 rightVolumeLevelDecibels;
            Int64 averageVolumeLevelDecibels;

            // Read the current volume levels
            leftVolumeLevelPercent = Convert.ToInt64(defaultDevice.AudioMeterInformation.PeakValues[0] * 100);
            rightVolumeLevelPercent = Convert.ToInt64(defaultDevice.AudioMeterInformation.PeakValues[1] * 100);

            // Calculate the average
            averageVolumeLevelPercent = (leftVolumeLevelPercent + rightVolumeLevelPercent) / 2;

            // Convert the volume levels to decibels
            leftVolumeLevelDecibels = convertPercentToDecibels(leftVolumeLevelPercent);
            rightVolumeLevelDecibels = convertPercentToDecibels(rightVolumeLevelPercent);
            averageVolumeLevelDecibels = convertPercentToDecibels(averageVolumeLevelPercent);

            // Write the volume and decibel levels to the form labels
            this.leftVolumeLabel.Text = Convert.ToString(leftVolumeLevelPercent);
            this.rightVolumeLabel.Text = Convert.ToString(rightVolumeLevelPercent);
            this.leftDecibelLabel.Text = Convert.ToString(leftVolumeLevelDecibels);
            this.rightDecibelLabel.Text = Convert.ToString(rightVolumeLevelDecibels);

            // Single 16 LED bar representing the average peak of both L and R channels
            if (displayTypeRadioButton1.Checked == true)
                {
                // Calculate the bar position
                currentBarLevel = convertDecibelsToBargraphPosition(averageVolumeLevelDecibels);

                if (displayDamperTrackBar.Value > 0)
                    {
                    if (oldBarLevel > currentBarLevel)
                        {
                        if (dampingCounter == displayDamperTrackBar.Value) currentBarLevel = oldBarLevel - 1;
                        else currentBarLevel = oldBarLevel;
                        }
                    }

                oldBarLevel = currentBarLevel;

                // Update the fade down counter
                dampingCounter++;
                if (dampingCounter > displayDamperTrackBar.Value) dampingCounter = 0;

                // Output the average volume level to the bargraph display
                int redLevelDifference;
                int greenLevelDifference;
                int blueLevelDifference;

                redLevelDifference = (endColourButton.BackColor.R - startColourButton.BackColor.R) / (16 - PeakColourLengthTrackBar.Value);
                greenLevelDifference = (endColourButton.BackColor.G - startColourButton.BackColor.G) / (16 - PeakColourLengthTrackBar.Value);
                blueLevelDifference = (endColourButton.BackColor.B - startColourButton.BackColor.B) / (16 - PeakColourLengthTrackBar.Value);

                for (int ledNumber = 0; ledNumber < 16; ledNumber++)
                    {
                    if (ledNumber < currentBarLevel)
                        {
                        // Set the LED to the correct colour
                        if (ledNumber < (16 - PeakColourLengthTrackBar.Value))
                            {
                            outputLedInformation(ledNumber,
                                (Byte)(startColourButton.BackColor.R + (redLevelDifference * ledNumber)),
                                (Byte)(startColourButton.BackColor.G + (greenLevelDifference * ledNumber)),
                                (Byte)(startColourButton.BackColor.B + (blueLevelDifference * ledNumber)));
                            }
                        else
                            {
                            outputLedInformation(ledNumber,
                                (Byte)endColourButton.BackColor.R,
                                (Byte)endColourButton.BackColor.G,
                                (Byte)endColourButton.BackColor.B);
                            }
                        }
                    else outputLedInformation(ledNumber, 0, 0, 0); // LED is off
                    }
                }

            // Two 8 LED bars showing the L and R peak values
            if (displayTypeRadioButton2.Checked == true || displayTypeRadioButton3.Checked == true)
                {
                // Calculate the bar positions
                currentLeftBarLevel = convertDecibelsToBargraphPosition(leftVolumeLevelDecibels) / 2;
                currentRightBarLevel = convertDecibelsToBargraphPosition(rightVolumeLevelDecibels) / 2;

                if (displayDamperTrackBar.Value > 0)
                    {
                    if (oldLeftBarLevel > currentLeftBarLevel)
                        {
                        if (dampingCounter == displayDamperTrackBar.Value) currentLeftBarLevel = oldLeftBarLevel - 1;
                        else currentLeftBarLevel = oldLeftBarLevel;
                        }

                    if (oldRightBarLevel > currentRightBarLevel)
                        {
                        if (dampingCounter == displayDamperTrackBar.Value) currentRightBarLevel = oldRightBarLevel - 1;
                        else currentRightBarLevel = oldRightBarLevel;
                        }
                    }

                oldLeftBarLevel = currentLeftBarLevel;
                oldRightBarLevel = currentRightBarLevel;

                // Update the fade down counter
                dampingCounter++;
                if (dampingCounter > displayDamperTrackBar.Value) dampingCounter = 0;

                // Output the average volume level to the bargraph display
                int redLevelDifference;
                int greenLevelDifference;
                int blueLevelDifference;

                redLevelDifference = (endColourButton.BackColor.R - startColourButton.BackColor.R) / (8 - (PeakColourLengthTrackBar.Value / 2));
                greenLevelDifference = (endColourButton.BackColor.G - startColourButton.BackColor.G) / (8 - (PeakColourLengthTrackBar.Value / 2));
                blueLevelDifference = (endColourButton.BackColor.B - startColourButton.BackColor.B) / (8 - (PeakColourLengthTrackBar.Value / 2));

                int positionCounter = 0;

                if (displayTypeRadioButton2.Checked == true)
                    {
                    for (int ledNumber = 7; ledNumber >= 0; ledNumber--)
                        {
                        if (positionCounter < currentLeftBarLevel)
                            {
                            // Set the LED to the correct colour
                            if (positionCounter < (8 - (PeakColourLengthTrackBar.Value / 2)))
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)(startColourButton.BackColor.R + (redLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.G + (greenLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.B + (blueLevelDifference * positionCounter)));
                                }
                            else
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)endColourButton.BackColor.R,
                                    (Byte)endColourButton.BackColor.G,
                                    (Byte)endColourButton.BackColor.B);
                                }
                            }
                        else outputLedInformation(ledNumber, 0, 0, 0); // LED is off

                        positionCounter++;
                        }

                    positionCounter = 0;
                    for (int ledNumber = 8; ledNumber < 16; ledNumber++)
                        {
                        if (positionCounter < currentRightBarLevel)
                            {
                            // Set the LED to the correct colour
                            if (positionCounter < (8 - (PeakColourLengthTrackBar.Value / 2)))
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)(startColourButton.BackColor.R + (redLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.G + (greenLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.B + (blueLevelDifference * positionCounter)));
                                }
                            else
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)endColourButton.BackColor.R,
                                    (Byte)endColourButton.BackColor.G,
                                    (Byte)endColourButton.BackColor.B);
                                }
                            }
                        else outputLedInformation(ledNumber, 0, 0, 0); // LED is off

                        positionCounter++;
                        }
                    }
                else
                    {
                    for (int ledNumber = 0; ledNumber < 8; ledNumber++)
                        {
                        if (positionCounter < currentLeftBarLevel)
                            {
                            // Set the LED to the correct colour
                            if (positionCounter < (8 - (PeakColourLengthTrackBar.Value / 2)))
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)(startColourButton.BackColor.R + (redLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.G + (greenLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.B + (blueLevelDifference * positionCounter)));
                                }
                            else
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)endColourButton.BackColor.R,
                                    (Byte)endColourButton.BackColor.G,
                                    (Byte)endColourButton.BackColor.B);
                                }
                            }
                        else outputLedInformation(ledNumber, 0, 0, 0); // LED is off

                        positionCounter++;
                        }

                    positionCounter = 0;
                    for (int ledNumber = 15; ledNumber > 7; ledNumber--)
                        {
                        if (positionCounter < currentRightBarLevel)
                            {
                            // Set the LED to the correct colour
                            if (positionCounter < (8 - (PeakColourLengthTrackBar.Value / 2)))
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)(startColourButton.BackColor.R + (redLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.G + (greenLevelDifference * positionCounter)),
                                    (Byte)(startColourButton.BackColor.B + (blueLevelDifference * positionCounter)));
                                }
                            else
                                {
                                outputLedInformation(ledNumber,
                                    (Byte)endColourButton.BackColor.R,
                                    (Byte)endColourButton.BackColor.G,
                                    (Byte)endColourButton.BackColor.B);
                                }
                            }
                        else outputLedInformation(ledNumber, 0, 0, 0); // LED is off

                        positionCounter++;
                        }
                    }
                }

            // Send the USB command to the device
            //theRgbBargraphDevice.writeLedBrightness();
            
            // Do Serial stuff and get single LED values.
            long leftLvl = convertDecibelsToBargraphPosition(leftVolumeLevelDecibels);
            long rightLvl = convertDecibelsToBargraphPosition(rightVolumeLevelDecibels);
            int avg = (int)((leftLvl + rightLvl) / 4.0); // Div by 4 to get out of 8.

            byte[] buffer = new byte[1];
            buffer[0] = 0x00;
            if (avg >= 1) buffer[0] |= (1 << 0);
            if (avg >= 2) buffer[0] |= (1 << 1);
            if (avg >= 3) buffer[0] |= (1 << 2);
            if (avg >= 4) buffer[0] |= (1 << 3);
            if (avg >= 5) buffer[0] |= (1 << 4);
            if (avg >= 6) buffer[0] |= (1 << 5);
            if (avg >= 7) buffer[0] |= (1 << 6);
            if (avg >= 8) buffer[0] |= (1 << 7);

            if (serAttach)
            {
                try
                {

                    serSerialPort.Write(buffer, 0, buffer.Length);
                }
                catch (Exception ex)
                {
                    serAttach = false;
                    try { serSerialPort.Dispose(); }
                    catch (Exception exf) { }
                    this.usbToolStripStatusLabel.Text = "Serial port device not found...";


                }
            }
            else
            {
                try { serSerialPort.Open(); serAttach = true; this.usbToolStripStatusLabel.Text = "Serial port device attached."; }
                catch (Exception ef) { serAttach = false; this.usbToolStripStatusLabel.Text = "Serial port device not found..."; }
            }

            }

        // This method takes a decibel value and converts it to a bargraph position 0-16
        private Int64 convertDecibelsToBargraphPosition(Int64 decibels)
            {
            // Here we just allocate a dB value to each of the 16 leds, if you are a serious audio person
            // this won't be enough, but if you're like me, just play around until it looks cool :)
            
            if (decibels == 0) return 16;
            if (decibels > -1) return 15;
            if (decibels > -2) return 14;
            if (decibels > -2) return 13;
            if (decibels > -3) return 12;
            if (decibels > -4) return 11;
            if (decibels > -5) return 10;
            if (decibels > -7) return 9;
            if (decibels > -8) return 8;
            if (decibels > -10) return 7;
            if (decibels > -12) return 6;
            if (decibels > -12) return 5;
            if (decibels > -16) return 4;
            if (decibels > -16) return 3;
            if (decibels > -18) return 2;
            if (decibels > -22) return 1;

            return 0;
            }

        // This method converts the % peak level to dBs from -96 (negative infinity) to 0 dBs
        // It uses a simple trendline average based on the figures provided by
        // http://www.execulink.com/~impact/audio_scale.htm
        private Int64 convertPercentToDecibels(Int64 percent)
            {
            Double decibels = -96;
            if (percent > 0) decibels = 8.686 * Math.Log(percent) - 40;
            return (Int64)decibels;
            }

        // Output the led information
        private void outputLedInformation(int ledNumber, byte red, byte green, byte blue)
            {
            // Update the bargraph settings
            theRgbBargraphDevice.setLedBrightness(ledNumber, red, green, blue);

            // Update the windows form display
            switch (ledNumber)
                {
                case 0:
                    this.led1Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 1:
                    this.led2Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 2:
                    this.led3Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 3:
                    this.led4Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 4:
                    this.led5Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 5:
                    this.led6Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 6:
                    this.led7Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 7:
                    this.led8Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 8:
                    this.led9Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 9:
                    this.led10Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 10:
                    this.led11Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 11:
                    this.led12Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 12:
                    this.led13Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 13:
                    this.led14Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 14:
                    this.led15Label.BackColor = Color.FromArgb(red, green, blue);
                    break;

                case 15:
                    this.led16Label.BackColor = Color.FromArgb(red, green, blue);
                    break;
                }
            }

        private void displayDampingRateStaticLabel_Click(object sender, EventArgs e)
            {

            }

        // The display trackbar has been moved
        private void displayDamperTrackBar_Scroll(object sender, EventArgs e)
            {
            // Update the track bar's label
            displayDampingRateLabel.Text = Convert.ToString(displayDamperTrackBar.Value);
            }

        private void ledFadeOffSpeedTrackBar_Scroll(object sender, EventArgs e)
            {
            // Update the track bar's label
            ledFadeOffSpeedLabel.Text = Convert.ToString(ledFadeOffSpeedTrackBar.Value);

            // Write the new value to the USB device
            theRgbBargraphDevice.setLedFadeOffSpeed((int)ledFadeOffSpeedTrackBar.Value);
            }

        // The main form is closing, clear the bargraph display
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
            {
            for (int ledNumber = 0; ledNumber < 16; ledNumber++) outputLedInformation(ledNumber, 0, 0, 0);

            // Send the USB command to the device
            theRgbBargraphDevice.writeLedBrightness();

            byte[] buff = new byte[1];
            buff[0] = 0x00;

            try
            {
                serSerialPort.Write(buff, 0, 1);
                serSerialPort.Close();
            }
            catch (Exception fu)
            {
            }
            }

        private void startColourButton_Click(object sender, EventArgs e)
            {
            // Show the colour selection dialogue
            if (startColourDialog.ShowDialog() != DialogResult.Cancel) startColourButton.BackColor = startColourDialog.Color;
            }

        private void endColourButton_Click(object sender, EventArgs e)
            {
            // Show the colour selection dialogue
            if (endColourDialog.ShowDialog() != DialogResult.Cancel) endColourButton.BackColor = endColourDialog.Color;
            }

        private void PeakColourLengthTrackBar_Scroll(object sender, EventArgs e)
            {
            // Update the track bar's label
            peakColourLengthLabel.Text = Convert.ToString(PeakColourLengthTrackBar.Value);
            }

        private void displayTypeRadioButton1_CheckedChanged(object sender, EventArgs e)
            {
            // Display type has changed, reset all the display counters and levels
            oldLeftBarLevel = 0;
            currentLeftBarLevel = 0;
            oldRightBarLevel = 0;
            currentRightBarLevel = 0;

            oldBarLevel = 0;
            currentBarLevel = 0;

            dampingCounter = 0;
            }

        }
    }
