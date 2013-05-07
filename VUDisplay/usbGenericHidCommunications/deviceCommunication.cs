//-----------------------------------------------------------------------------
//
//  deviceCommunication.cs
//
//  A class for communicating with Generic HID USB devices
//  Copyright (C) 2010 Simon Inns
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  Web:    http://www.waitingforfriday.com
//  Email:  simon.inns@gmail.com
//
//-----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;
using System.Threading;

// The following namespace allows debugging output (when compiled in debug mode)
using System.Diagnostics;

namespace usbGenericHidCommunications
    {
    public partial class usbGenericHidCommunication
        {
        #region outputToDeviceRegion

        /// <summary>
        /// writeRawReportToDevice - Writes a report to the device using interrupt transfer.
        /// Note: this method performs no checking on the buffer.  The first byte must 
        /// always be zero (or the write will fail!) and the second byte should be the
        /// command number for the USB device firmware.
        /// </summary>
        protected bool writeRawReportToDevice(Byte[] outputReportBuffer)
            {
            bool success = false;
            int numberOfBytesWritten = 0;

            // Make sure a device is attached
            if (!isDeviceAttached)
                {
                Debug.WriteLine("usbGenericHidCommunication:writeReportToDevice(): -> No device attached!");
                return success;
                }

            try
                {
                // Set an output report via interrupt to the device
                success = WriteFile(
                    deviceInformation.writeHandle,
                    outputReportBuffer,
                    outputReportBuffer.Length,
                    ref numberOfBytesWritten,
                    IntPtr.Zero);

                if (success) Debug.WriteLine("usbGenericHidCommunication:writeReportToDevice(): -> Write report succeeded");
                else Debug.WriteLine("usbGenericHidCommunication:writeReportToDevice(): -> Write report failed!");

                return success;
                }
            catch (Exception)
                {
                // An error - send out some debug and return failure
                Debug.WriteLine("usbGenericHidCommunication:writeReportToDevice(): -> EXCEPTION: When attempting to send an output report");
                return false;
                }    
            }
        #endregion

        #region inputFromDeviceRegion
        /// <summary>
        /// readRawReportFromDevice - Reads a raw report from the device with timeout handling
        /// Note: This method performs no checking on the buffer.  The first byte returned is
        /// usually zero, the second byte is the command that the USB firmware is replying to.
        /// The other 63 bytes are (possibly) data.
        /// 
        /// The maximum report size will be determind by the length of the inputReportBuffer.
        /// </summary>
        private bool readRawReportFromDevice(ref Byte[] inputReportBuffer, ref int numberOfBytesRead)
            {
            IntPtr eventObject = IntPtr.Zero;
            NativeOverlapped hidOverlapped = new NativeOverlapped();
            IntPtr nonManagedBuffer = IntPtr.Zero;
            IntPtr nonManagedOverlapped = IntPtr.Zero;
            Int32 result = 0;
            bool success;

            // Make sure a device is attached
            if (!isDeviceAttached)
                {
                Debug.WriteLine("usbGenericHidCommunication:readReportFromDevice(): -> No device attached!");
                return false;
                }

            try
                {
                // Prepare an event object for the overlapped ReadFile
                eventObject = CreateEvent(IntPtr.Zero, false, false, "");

                hidOverlapped.OffsetLow = 0;
                hidOverlapped.OffsetHigh = 0;
                hidOverlapped.EventHandle = eventObject;     

                // Allocate memory for the unmanaged input buffer and overlap structure.
                nonManagedBuffer = Marshal.AllocHGlobal(inputReportBuffer.Length);
                nonManagedOverlapped = Marshal.AllocHGlobal(Marshal.SizeOf(hidOverlapped));
                Marshal.StructureToPtr(hidOverlapped, nonManagedOverlapped, false);

                // Read the input report buffer
                Debug.WriteLine("usbGenericHidCommunication:readReportFromDevice(): -> Attempting to ReadFile");
                success = ReadFile(
                    deviceInformation.readHandle,
                    nonManagedBuffer,
                    inputReportBuffer.Length,
                    ref numberOfBytesRead,
                    nonManagedOverlapped);

                if (!success)
                    {
                    // We are now waiting for the FileRead to complete
                    Debug.WriteLine("usbGenericHidCommunication:readReportFromDevice(): -> ReadFile started, waiting for completion...");

                    // Wait a maximum of 3 seconds for the FileRead to complete
                    result = WaitForSingleObject(eventObject, 3000);

                    switch (result)
                        {
                        // Has the ReadFile completed successfully?
                        case (System.Int32)WAIT_OBJECT_0:
                            success = true;

                            // Get the number of bytes transferred
                            GetOverlappedResult(deviceInformation.readHandle, nonManagedOverlapped, ref numberOfBytesRead, false);

                            Debug.WriteLine(string.Format("usbGenericHidCommunication:readReportFromDevice(): -> ReadFile successful (overlapped) {0} bytes read", numberOfBytesRead));
                            break;

                        // Did the FileRead operation timeout?
                        case WAIT_TIMEOUT:
                            success = false;

                            // Cancel the ReadFile operation
                            CancelIo(deviceInformation.readHandle);
                            if (!deviceInformation.hidHandle.IsInvalid) deviceInformation.hidHandle.Close();
                            if (!deviceInformation.readHandle.IsInvalid) deviceInformation.readHandle.Close();
                            if (!deviceInformation.writeHandle.IsInvalid) deviceInformation.writeHandle.Close();

                            // Detach the USB device to try to get us back in a known state
                            detachUsbDevice();

                            Debug.WriteLine("usbGenericHidCommunication:readReportFromDevice(): -> ReadFile timedout! USB device detached");
                            break;

                        // Some other unspecified error has occurred?
                        default:
                            success = false;

                            // Cancel the ReadFile operation

                            // Detach the USB device to try to get us back in a known state
                            detachUsbDevice();

                            Debug.WriteLine("usbGenericHidCommunication:readReportFromDevice(): -> ReadFile unspecified error! USB device detached");
                            break;
                        }
                    }
                    if (success)
                        {
                        // Report receieved correctly, copy the unmanaged input buffer over to the managed buffer
                        Marshal.Copy(nonManagedBuffer, inputReportBuffer, 0, numberOfBytesRead);
                        Debug.WriteLine(string.Format("usbGenericHidCommunication:readReportFromDevice(): -> ReadFile successful {0} bytes read", numberOfBytesRead));
                        }
                }
            catch (Exception)
                {
                // An error - send out some debug and return failure
                Debug.WriteLine("usbGenericHidCommunication:readReportFromDevice(): -> EXCEPTION: When attempting to receive an input report");
                return false;
                }
            return success;
            }

        /// <summary>
        /// readSingleReportFromDevice - Reads a single report packet from the USB device.
        /// The size of the passed inputReportBuffer must be correct for the device, so
        /// this method checks the passed buffer's size against the input report size
        /// discovered by the device enumeration.
        /// </summary>
        /// <param name="inputReportBuffer"></param>
        /// <returns></returns>
        protected bool readSingleReportFromDevice(ref Byte[] inputReportBuffer)
            {
            bool success;
            int numberOfBytesRead = 0;

            // The size of our inputReportBuffer must be at least the same size as the input report.
            if (inputReportBuffer.Length != (int)deviceInformation.capabilities.inputReportByteLength)
                {
                // inputReportBuffer is not the right length!
                Debug.WriteLine(
                    "usbGenericHidCommunication:readSingleReportFromDevice(): -> ERROR: The referenced inputReportBuffer size is incorrect for the input report size!");
                return false;
                }

            // The readRawReportFromDevice method will fill the passed readBuffer or return false
            success = readRawReportFromDevice(ref inputReportBuffer, ref numberOfBytesRead);

            return success;
            }

        /// <summary>
        /// readMultipleReportsFromDevice - Attempts to retrieve multiple reports from the device in 
        /// a single read.  This action can be block the form execution if you request too much data.
        /// If you need more data from the device and want to avoid any blocking you will have to make
        /// multiple commands to the device and deal with the multiple requests and responses in your
        /// application.
        /// </summary>
        /// <param name="inputReportBuffer"></param>
        /// <param name="numberOfReports"></param>
        /// <returns></returns>
        protected bool readMultipleReportsFromDevice(ref Byte[] inputReportBuffer, int numberOfReports)
            {
            bool success = false;
            int numberOfBytesRead = 0;
            long pointerToBuffer = 0;

            // Define a temporary buffer for assembling partial data reads into the completed inputReportBuffer
            Byte[] temporaryBuffer = new Byte[inputReportBuffer.Length];

            // Range check the number of reports
            if (numberOfReports == 0)
                {
                Debug.WriteLine(
                    "usbGenericHidCommunication:readMultipleReportsFromDevice(): -> ERROR: You cannot request 0 reports!");
                return false;
                }

            if (numberOfReports > 128)
                {
                Debug.WriteLine(
                    "usbGenericHidCommunication:readMultipleReportsFromDevice(): -> ERROR: Reference application testing does not verify the code for more than 128 reports");
                return false;
                }

            // The size of our inputReportBuffer must be at least the same size as the input report multiplied by the number of reports requested.
            if (inputReportBuffer.Length != ((int)deviceInformation.capabilities.inputReportByteLength * numberOfReports))
                {
                // inputReportBuffer is not the right length!
                Debug.WriteLine(
                    "usbGenericHidCommunication:readMultipleReportsFromDevice(): -> ERROR: The referenced inputReportBuffer size is incorrect for the number of input reports requested!");
                return false;
                }

            // The readRawReportFromDevice method will fill the passed read buffer or return false
            while (pointerToBuffer != ((int)deviceInformation.capabilities.inputReportByteLength * numberOfReports))
                {
                Debug.WriteLine(
                    "usbGenericHidCommunication:readMultipleReportsFromDevice(): -> Reading from device...");
                success = readRawReportFromDevice(ref temporaryBuffer, ref numberOfBytesRead);

                // Was the read successful?
                if (!success)
                    {
                    return false;
                    }

                // Copy the received data into the referenced input buffer
                Array.Copy(temporaryBuffer, 0, inputReportBuffer, pointerToBuffer, (long)numberOfBytesRead);
                pointerToBuffer += (long)numberOfBytesRead;
                }

            return success;
            }

        #endregion
        }
    }
