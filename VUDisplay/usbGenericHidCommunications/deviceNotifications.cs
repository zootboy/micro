//-----------------------------------------------------------------------------
//
//  deviceNotifications.cs
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

using System.Windows.Forms;
using System.Runtime.InteropServices;

// The following namespace allows debugging output (when compiled in debug mode)
using System.Diagnostics;

namespace usbGenericHidCommunications
    {
    /// <summary>
    /// This partial class contains the methods required for detecting when
    /// the USB device is attached or detached.
    /// </summary>
    public partial class usbGenericHidCommunication
        {

        /// <summary>
        /// Create a delegate for the USB event handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public delegate void usbEventsHandler(object sender, EventArgs e);

        /// <summary>
        /// Define the event
        /// </summary>
        public event usbEventsHandler usbEvent;

        /// <summary>
        /// The usb event thrower
        /// </summary>
        /// <param name="e"></param>
        protected virtual void onUsbEvent(EventArgs e)
            {
            if (usbEvent != null)
                {
                Debug.WriteLine("usbGenericHidCommunications:onUsbEvent() -> Throwing a USB event to a listener");
                usbEvent(this, e);
                }
            else Debug.WriteLine("usbGenericHidCommunications:onUsbEvent() -> Attempted to throw a USB event, but no one was listening");
            }

        /// <summary>
        /// isNotificationForTargetDevice - Compares the target devices pathname against the
        /// pathname of the device which caused the event message
        /// </summary>
        private Boolean isNotificationForTargetDevice(Message m)
            {
            Int32 stringSize;

            try
                {
                DEV_BROADCAST_DEVICEINTERFACE_1 devBroadcastDeviceInterface = new DEV_BROADCAST_DEVICEINTERFACE_1();
                DEV_BROADCAST_HDR devBroadcastHeader = new DEV_BROADCAST_HDR();

                Marshal.PtrToStructure(m.LParam, devBroadcastHeader);

                // Is the notification event concerning a device interface?
                if ((devBroadcastHeader.dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE))
                    {
                    // Get the device path name of the affected device
                    stringSize = System.Convert.ToInt32((devBroadcastHeader.dbch_size - 32) / 2);    
                    devBroadcastDeviceInterface.dbcc_name = new Char[stringSize + 1];
                    Marshal.PtrToStructure(m.LParam, devBroadcastDeviceInterface);
                    String deviceNameString = new String(devBroadcastDeviceInterface.dbcc_name, 0, stringSize);

                    // Compare the device name with our target device's pathname
                    if ((String.Compare(deviceNameString, deviceInformation.devicePathName, true) == 0)) return true;
                    else return false;
                    }
                }
            catch (Exception)
                {
                Debug.WriteLine("usbGenericHidCommunication:isNotificationForTargetDevice() -> EXCEPTION: An unknown exception has occured!");
                return false;
                }
            return false;
            }

        /// <summary>
        /// registerForDeviceNotification - registers the window (identified by the windowHandle) for 
        /// device notification messages from Windows
        /// </summary>
        public Boolean registerForDeviceNotifications(IntPtr windowHandle)
            {
            Debug.WriteLine("usbGenericHidCommunication:registerForDeviceNotifications() -> Method called");

            // A DEV_BROADCAST_DEVICEINTERFACE header holds information about the request.
            DEV_BROADCAST_DEVICEINTERFACE devBroadcastDeviceInterface = new DEV_BROADCAST_DEVICEINTERFACE();
            IntPtr devBroadcastDeviceInterfaceBuffer = IntPtr.Zero;
            Int32 size = 0;

            // Get the required GUID
            System.Guid systemHidGuid = new Guid();
            HidD_GetHidGuid(ref systemHidGuid);

            try
                {
                // Set the parameters in the DEV_BROADCAST_DEVICEINTERFACE structure.
                size = Marshal.SizeOf(devBroadcastDeviceInterface);
                devBroadcastDeviceInterface.dbcc_size = size;
                devBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
                devBroadcastDeviceInterface.dbcc_reserved = 0;
                devBroadcastDeviceInterface.dbcc_classguid = systemHidGuid;

                devBroadcastDeviceInterfaceBuffer = Marshal.AllocHGlobal(size);
                Marshal.StructureToPtr(devBroadcastDeviceInterface, devBroadcastDeviceInterfaceBuffer, true);

                // Register for notifications and store the returned handle
                deviceInformation.deviceNotificationHandle = RegisterDeviceNotification(windowHandle, devBroadcastDeviceInterfaceBuffer, DEVICE_NOTIFY_WINDOW_HANDLE);
                Marshal.PtrToStructure(devBroadcastDeviceInterfaceBuffer, devBroadcastDeviceInterface);

                if ((deviceInformation.deviceNotificationHandle.ToInt32() == IntPtr.Zero.ToInt32()))
                    {
                    Debug.WriteLine("usbGenericHidCommunication:registerForDeviceNotifications() -> Notification registration failed");
                    return false;
                    }
                else
                    {
                    Debug.WriteLine("usbGenericHidCommunication:registerForDeviceNotifications() -> Notification registration succeded");
                    return true;
                    }
                }
            catch (Exception)
                {
                Debug.WriteLine("usbGenericHidCommunication:registerForDeviceNotifications() -> EXCEPTION: An unknown exception has occured!");
                }
            finally
                {
                // Free the memory allocated previously by AllocHGlobal.
                if (devBroadcastDeviceInterfaceBuffer != IntPtr.Zero)
                    Marshal.FreeHGlobal(devBroadcastDeviceInterfaceBuffer);
                }
            return false;
            }

        /// <summary>
        /// handleDeviceNotificationMessages - this method examines any windows devices messages that are
        /// received to check if they are relevant to our target USB device.  If so the method takes the 
        /// correct action dependent on the message type.
        /// </summary>
        /// <param name="m"></param>
        public void handleDeviceNotificationMessages(Message m)
            {
            //Debug.WriteLine("usbGenericHidCommunication:handleDeviceNotificationMessages() -> Method called");
            
            // Make sure this is a device notification
            if (m.Msg != WM_DEVICECHANGE) return;

            Debug.WriteLine("usbGenericHidCommunication:handleDeviceNotificationMessages() -> Device notification received");

            try
                {
                switch (m.WParam.ToInt32())
                    {
                    // Device attached
                    case DBT_DEVICEARRIVAL:
                        Debug.WriteLine("usbGenericHidCommunication:handleDeviceNotificationMessages() -> New device attached");
                        // If our target device is not currently attached, this could be our device, so we attempt to find it.
                        if (!isDeviceAttached)
                            {
                            findTargetDevice();
                            onUsbEvent(EventArgs.Empty); // Generate an event
                            }
                        break;

                    // Device removed
                    case DBT_DEVICEREMOVECOMPLETE:
                        Debug.WriteLine("usbGenericHidCommunication:handleDeviceNotificationMessages() -> A device has been removed");

                        // Was this our target device?  
                        if (isNotificationForTargetDevice(m))
                            {
                            // If so detach the USB device.
                            Debug.WriteLine("usbGenericHidCommunication:handleDeviceNotificationMessages() -> The target USB device has been removed - detaching...");
                            detachUsbDevice();
                            onUsbEvent(EventArgs.Empty); // Generate an event
                            }
                        break;

                    // Other message
                    default:
                        Debug.WriteLine("usbGenericHidCommunication:handleDeviceNotificationMessages() -> Unknown notification message");
                        break;
                    }
                }
            catch (Exception)
                {
                Debug.WriteLine("usbGenericHidCommunication:handleDeviceNotificationMessages() -> EXCEPTION: An unknown exception has occured!");
                } 
            }

        }
    }
