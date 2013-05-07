//-----------------------------------------------------------------------------
//
//  usbGenericHidCommunications.cs
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

using System.Collections;

// The following namespace allows debugging output (when compiled in debug mode)
using System.Diagnostics;

namespace usbGenericHidCommunications
    {
    /// <summary>
    /// USB Generic HID Communication class
    /// </summary>
    /// <remarks>This class provides communication and device handling events
    /// for USB devices which implement the generic HID protocol. It is
    /// designed to be inherited into a class which deals with a specific
    /// device firmware and is therefore defined as an abstract class.
    /// 
    /// This class definition contains the highest level parts of the
    /// class which is defined over a number of files</remarks>
    public partial class usbGenericHidCommunication
        {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>This constructor method creates an object for HID communication and attempts to find
        /// (and bind to) the USB device indicated by the passed VID (Vendor ID) and PID (Product ID) which
        /// should both be passed as unsigned integers.</remarks>
        public usbGenericHidCommunication(int vid, int pid)
            {
            Debug.WriteLine("usbGenericHidCommunication:usbGenericHidCommunication() -> Class constructor called");

            // Set the deviceAttached flag to false
            deviceInformation.deviceAttached = false;

            // Store the target device's VID and PID in the device attributes
            deviceInformation.targetVid = (UInt16)vid;
            deviceInformation.targetPid = (UInt16)pid;
            }

        /// <summary>
        /// Destructor
        /// </summary>
        /// <remarks>This method closes any open connections to the USB device and clears up any resources
        /// that have been consumed over the lifetime of the object.</remarks>
        ~usbGenericHidCommunication()
            {
            Debug.WriteLine("usbGenericHidCommunication:usbGenericHidCommunication() -> Class destructor called");

            // Detach the USB device (performs required clean up operations)
            detachUsbDevice();
            }

        /// <summary>
        /// deviceAttributesStructure is used to represent the details of the target USB device as the methods
        /// discover them so they can be reused by other methods when communicating with the device
        /// </summary>
        private struct deviceInformationStructure
            {
            public UInt16 targetVid;                // Our target device's VID
            public UInt16 targetPid;                // Our target device's PID
            public bool deviceAttached;             // Device attachment state flag
            public HIDD_ATTRIBUTES attributes;      // HID Attributes
            public HIDP_CAPS capabilities;          // HID Capabilities
            public SafeFileHandle readHandle;       // Read handle from the device
            public SafeFileHandle writeHandle;      // Write handle to the device
            public SafeFileHandle hidHandle;        // Handle used for communicating via hid.dll
            public String devicePathName;           // The device's path name
            public IntPtr deviceNotificationHandle; // The device's notification handle
            }

        /// <summary>
        /// deviceAttributes contains the discovered attributes of the target USB device
        /// </summary>
        private deviceInformationStructure deviceInformation;

        /// <summary>
        /// Detach the USB device
        /// </summary>
        /// <remarks>This method detaches the USB device and frees the read and write handles
        /// to the device.</remarks>
        private void detachUsbDevice()
            {
            Debug.WriteLine("usbGenericHidCommunication:detachUsbDevice() -> Method called");

            // Is a device currently attached?
            if (isDeviceAttached)
                {
                Debug.WriteLine("usbGenericHidCommunication:detachUsbDevice() -> Detaching device and closing file handles");
                // Set the device status to detached;
                isDeviceAttached = false;

                // Close the readHandle, writeHandle and hidHandle
                if (!deviceInformation.hidHandle.IsInvalid) deviceInformation.hidHandle.Close();
                if (!deviceInformation.readHandle.IsInvalid) deviceInformation.readHandle.Close();
                if (!deviceInformation.writeHandle.IsInvalid) deviceInformation.writeHandle.Close();

                // Throw an event
                onUsbEvent(EventArgs.Empty);
                }
            else Debug.WriteLine("usbGenericHidCommunication:detachUsbDevice() -> No device attached");
            }

        /// <summary>
        /// Is device attached?
        /// </summary>
        /// <remarks>This method is used to set (private) or test (public) the device attachment status</remarks>
        public bool isDeviceAttached
            {
            get
                {
                return deviceInformation.deviceAttached;
                }
            private set
                {
                deviceInformation.deviceAttached = value;
                }
            }
        }
    }
