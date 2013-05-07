//-----------------------------------------------------------------------------
//
//  deviceDiscovery.cs
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

// The following namespace allows debugging output (when compiled in debug mode)
using System.Diagnostics;

namespace usbGenericHidCommunications
    {
    public partial class usbGenericHidCommunication
        {
        /// <summary>
        /// Find all devices with the HID GUID attached to the system
        /// </summary>
        /// <remarks>This method searches for all devices that have the correct HID GUID and
        /// returns an array of matching device paths</remarks>
        private bool findHidDevices(ref String[] listOfDevicePathNames, ref int numberOfDevicesFound)
            {
            Debug.WriteLine("usbGenericHidCommunication:findHidDevices() -> Method called");
            // Detach the device if it's currently attached
            if (isDeviceAttached) detachUsbDevice();

            // Initialise the internal variables required for performing the search
            Int32 bufferSize = 0;
            IntPtr detailDataBuffer = IntPtr.Zero;
            Boolean deviceFound;
            IntPtr deviceInfoSet = new System.IntPtr();
            Boolean lastDevice = false;
            Int32 listIndex = 0;
            SP_DEVICE_INTERFACE_DATA deviceInterfaceData = new SP_DEVICE_INTERFACE_DATA();
            Boolean success;

            // Get the required GUID
            System.Guid systemHidGuid = new Guid();
            HidD_GetHidGuid(ref systemHidGuid);
            Debug.WriteLine(string.Format("usbGenericHidCommunication:findHidDevices() -> Fetched GUID for HID devices ({0})", systemHidGuid.ToString()));

            try
                {
                // Here we populate a list of plugged-in devices matching our class GUID (DIGCF_PRESENT specifies that the list
                // should only contain devices which are plugged in)
                Debug.WriteLine("usbGenericHidCommunication:findHidDevices() -> Using SetupDiGetClassDevs to get all devices with the correct GUID");
                deviceInfoSet = SetupDiGetClassDevs(ref systemHidGuid, IntPtr.Zero, IntPtr.Zero, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

                // Reset the deviceFound flag and the memberIndex counter
                deviceFound = false;
                listIndex = 0;

                deviceInterfaceData.cbSize = Marshal.SizeOf(deviceInterfaceData);

                // Look through the retrieved list of class GUIDs looking for a match on our interface GUID
                do
                    {
                    //Debug.WriteLine("usbGenericHidCommunication:findHidDevices() -> Enumerating devices");
                    success = SetupDiEnumDeviceInterfaces
                        (deviceInfoSet,
                        IntPtr.Zero,
                        ref systemHidGuid,
                        listIndex,
                        ref deviceInterfaceData);

                    if (!success)
                        {
                        //Debug.WriteLine("usbGenericHidCommunication:findHidDevices() -> No more devices left - giving up");
                        lastDevice = true;
                        }
                    else
                        {
                        // The target device has been found, now we need to retrieve the device path so we can open
                        // the read and write handles required for USB communication

                        // First call is just to get the required buffer size for the real request
                        success = SetupDiGetDeviceInterfaceDetail
                            (deviceInfoSet,
                            ref deviceInterfaceData,
                            IntPtr.Zero,
                            0,
                            ref bufferSize,
                            IntPtr.Zero);

                        // Allocate some memory for the buffer
                        detailDataBuffer = Marshal.AllocHGlobal(bufferSize);
                        Marshal.WriteInt32(detailDataBuffer, (IntPtr.Size == 4) ? (4 + Marshal.SystemDefaultCharSize) : 8);

                        // Second call gets the detailed data buffer
                        //Debug.WriteLine("usbGenericHidCommunication:findHidDevices() -> Getting details of the device");
                        success = SetupDiGetDeviceInterfaceDetail
                            (deviceInfoSet,
                            ref deviceInterfaceData,
                            detailDataBuffer,
                            bufferSize,
                            ref bufferSize,
                            IntPtr.Zero);

                        // Skip over cbsize (4 bytes) to get the address of the devicePathName.
                        IntPtr pDevicePathName = new IntPtr(detailDataBuffer.ToInt32() + 4);

                        // Get the String containing the devicePathName.
                        listOfDevicePathNames[listIndex] = Marshal.PtrToStringAuto(pDevicePathName);

                        //Debug.WriteLine(string.Format("usbGenericHidCommunication:findHidDevices() -> Found matching device (memberIndex {0})", memberIndex));
                        deviceFound = true;
                        }
                    listIndex = listIndex + 1;
                    }
                while (!((lastDevice == true)));
                }
            catch (Exception)
                {
                // Something went badly wrong... output some debug and return false to indicated device discovery failure
                Debug.WriteLine("usbGenericHidCommunication:findHidDevices() -> EXCEPTION: Something went south whilst trying to get devices with matching GUIDs - giving up!");
                return false;
                }
            finally
                {
                // Clean up the unmanaged memory allocations
                if (detailDataBuffer != IntPtr.Zero)
                    {
                    // Free the memory allocated previously by AllocHGlobal.
                    Marshal.FreeHGlobal(detailDataBuffer);
                    }

                if (deviceInfoSet != IntPtr.Zero)
                    {
                    SetupDiDestroyDeviceInfoList(deviceInfoSet);
                    }
                }

            if (deviceFound)
                {
                Debug.WriteLine(string.Format("usbGenericHidCommunication:findHidDevices() -> Found {0} devices with matching GUID", listIndex - 1));
                numberOfDevicesFound = listIndex - 2;
                }
            else Debug.WriteLine("usbGenericHidCommunication:findHidDevices() -> No matching devices found");

            return deviceFound;
            }

        /// <summary>
        /// Find the target device based on the VID and PID
        /// </summary>
        /// <remarks>This method used the 'findHidDevices' to fetch a list of attached HID devices
        /// then it searches through the list looking for a HID device with the correct VID and
        /// PID</remarks>
        public void findTargetDevice()
            {
            Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Method called");

            bool deviceFoundByGuid = false;
            String[] listOfDevicePathNames = new String[128]; // 128 is the maximum number of USB devices allowed on a single host
            int listIndex = 0;
            bool success = false;
            bool isDeviceDetected;
            int numberOfDevicesFound = 0;

            try
                {
                // Reset the device detection flag
                isDeviceDetected = false;

                // Get all the devices with the correct HID GUID
                deviceFoundByGuid = findHidDevices(ref listOfDevicePathNames, ref numberOfDevicesFound);

                if (deviceFoundByGuid)
                    {
                    Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Devices with matching GUID found...");
                    listIndex = 0;

                    do
                        {
                        Debug.WriteLine(string.Format("usbGenericHidCommunication:findTargetDevice() -> Performing CreateFile to listIndex {0}", listIndex));
                        deviceInformation.hidHandle = CreateFile(listOfDevicePathNames[listIndex], 0, FILE_SHARE_READ | FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, 0);

                        if (!deviceInformation.hidHandle.IsInvalid)
                            {
                            deviceInformation.attributes.size = Marshal.SizeOf(deviceInformation.attributes);
                            success = HidD_GetAttributes(deviceInformation.hidHandle, ref deviceInformation.attributes);

                            if (success)
                                {
                                Debug.WriteLine(string.Format("usbGenericHidCommunication:findTargetDevice() -> Found device with VID {0}, PID {1} and Version number {2}",
                                    Convert.ToString(deviceInformation.attributes.vendorId, 16),
                                    Convert.ToString(deviceInformation.attributes.productId, 16),
                                    Convert.ToString(deviceInformation.attributes.versionNumber, 16)));

                                //  Do the VID and PID of the device match our target device?
                                if ((deviceInformation.attributes.vendorId == deviceInformation.targetVid) &&
                                    (deviceInformation.attributes.productId == deviceInformation.targetPid))
                                    {
                                    // Matching device found
                                    Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Device with matching VID and PID found!");
                                    isDeviceDetected = true;

                                    // Store the device's pathname in the device information
                                    deviceInformation.devicePathName = listOfDevicePathNames[listIndex];
                                    }
                                else
                                    {
                                    // Wrong device, close the handle
                                    Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Device didn't match... Continuing...");
                                    isDeviceDetected = false;
                                    deviceInformation.hidHandle.Close();
                                    }
                                }
                            else
                                {
                                //  Something went rapidly south...  give up!
                                Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Something bad happened - couldn't fill the HIDD_ATTRIBUTES, giving up!");
                                isDeviceDetected = false;
                                deviceInformation.hidHandle.Close();
                                }
                            }

                        //  Move to the next device, or quit if there are no more devices to examine
                        listIndex++;
                        }
                    while (!((isDeviceDetected || (listIndex == numberOfDevicesFound + 1))));
                    }

                // If we found a matching device then we need discover more details about the attached device
                // and then open read and write handles to the device to allow communication
                if (isDeviceDetected)
                    {
                    // Query the HID device's capabilities (primarily we are only really interested in the 
                    // input and output report byte lengths as this allows us to validate information sent
                    // to and from the device does not exceed the devices capabilities.
                    //
                    // We could determine the 'type' of HID device here too, but since this class is only
                    // for generic HID communication we don't care...
                    queryDeviceCapabilities();

                    if (success)
                        {
                        // Open the readHandle to the device
                        Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Opening a readHandle to the device");
                        deviceInformation.readHandle = CreateFile(
                            deviceInformation.devicePathName,
                            GENERIC_READ,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            IntPtr.Zero, OPEN_EXISTING,
                            FILE_FLAG_OVERLAPPED,
                            0);

                        // Did we open the readHandle successfully?
                        if (deviceInformation.readHandle.IsInvalid)
                            {
                            Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Unable to open a readHandle to the device!");
                            }
                        else
                            {
                            Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Opening a writeHandle to the device");
                            deviceInformation.writeHandle = CreateFile(
                                deviceInformation.devicePathName,
                                GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                IntPtr.Zero,
                                OPEN_EXISTING,
                                0,
                                0);

                            // Did we open the writeHandle successfully?
                            if (deviceInformation.writeHandle.IsInvalid)
                                {
                                Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> Unable to open a writeHandle to the device!");

                                // Attempt to close the writeHandle
                                deviceInformation.writeHandle.Close();
                                }
                            else
                                {
                                // Device is now discovered and ready for use, update the status
                                isDeviceAttached = true;
                                onUsbEvent(EventArgs.Empty); // Throw an event
                                }
                            }
                        }
                    }
                else
                    {
                    //  The device wasn't detected.
                    Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> No matching device found!");
                    }
                }
            catch (Exception)
                {
                Debug.WriteLine("usbGenericHidCommunication:findTargetDevice() -> EXCEPTION: Unknown - device not found");
                isDeviceDetected = false;
                }
            }

        /// <summary>
        /// queryDeviceCapabilities - Used the hid.dll function to query the capabilities
        /// of the target device.
        /// </summary>
        private void queryDeviceCapabilities()
            {
            IntPtr preparsedData = new System.IntPtr();
            Int32 result = 0;
            Boolean success = false;

            try
                {
                // Get the preparsed data from the HID driver
                success = HidD_GetPreparsedData(deviceInformation.hidHandle, ref preparsedData);

                // Get the HID device's capabilities
                result = HidP_GetCaps(preparsedData, ref deviceInformation.capabilities);
                if ((result != 0))
                    {
                    Debug.WriteLine("usbGenericHidCommunication:queryDeviceCapabilities() -> Device query results:");
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Usage: {0}",
                        Convert.ToString(deviceInformation.capabilities.usage, 16)));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Usage Page: {0}",
                        Convert.ToString(deviceInformation.capabilities.usagePage, 16)));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Input Report Byte Length: {0}",
                        deviceInformation.capabilities.inputReportByteLength));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Output Report Byte Length: {0}", 
                        deviceInformation.capabilities.outputReportByteLength));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Feature Report Byte Length: {0}",
                        deviceInformation.capabilities.featureReportByteLength));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Link Collection Nodes: {0}", 
                        deviceInformation.capabilities.numberLinkCollectionNodes));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Input Button Caps: {0}",
                        deviceInformation.capabilities.numberInputButtonCaps));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Input Value Caps: {0}", 
                        deviceInformation.capabilities.numberInputValueCaps));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Input Data Indices: {0}", 
                        deviceInformation.capabilities.numberInputDataIndices));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Output Button Caps: {0}", 
                        deviceInformation.capabilities.numberOutputButtonCaps));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Output Value Caps: {0}",
                        deviceInformation.capabilities.numberOutputValueCaps));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Output Data Indices: {0}", 
                        deviceInformation.capabilities.numberOutputDataIndices));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Feature Button Caps: {0}", 
                        deviceInformation.capabilities.numberFeatureButtonCaps));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Feature Value Caps: {0}", 
                        deviceInformation.capabilities.numberFeatureValueCaps));
                    Debug.WriteLine(string.Format("usbGenericHidCommunication:queryDeviceCapabilities() ->     Number of Feature Data Indices: {0}", 
                        deviceInformation.capabilities.numberFeatureDataIndices));
                    }
                }
            catch (Exception)
                {
                // Something went badly wrong... this shouldn't happen, so we throw an exception
                Debug.WriteLine("usbGenericHidCommunication:queryDeviceCapabilities() -> EXECEPTION: An unrecoverable error has occurred!");
                throw;
                }
            finally
                {
                // Free up the memory before finishing
                if (preparsedData != IntPtr.Zero)
                    {
                    success = HidD_FreePreparsedData(preparsedData);
                    }
                }
            }      
        }
    }
