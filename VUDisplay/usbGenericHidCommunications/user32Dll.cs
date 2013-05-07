//-----------------------------------------------------------------------------
//
//  user32Dll.cs
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

namespace usbGenericHidCommunications
    {
    /// <summary>
    /// user32Dll - Internal class containing the API definitions required for interoperability
    /// with the user32.dll.  Primarily this provides methods for erceiving event notifications
    /// which are used to alert the application when devices are added and removed from the 
    /// system.
    /// </summary>
    public partial class usbGenericHidCommunication
        {
        // from dbt.h
        internal const Int32 DBT_DEVICEARRIVAL = 0x8000;
        internal const Int32 DBT_DEVICEREMOVECOMPLETE = 0x8004;
        internal const Int32 DBT_DEVTYP_DEVICEINTERFACE = 5;
        internal const Int32 DBT_DEVTYP_HANDLE = 6;
        internal const Int32 DEVICE_NOTIFY_ALL_INTERFACE_CLASSES = 4;
        internal const Int32 DEVICE_NOTIFY_SERVICE_HANDLE = 1;
        internal const Int32 DEVICE_NOTIFY_WINDOW_HANDLE = 0;
        internal const Int32 WM_DEVICECHANGE = 0x219;

        [StructLayout(LayoutKind.Sequential)]
        internal class DEV_BROADCAST_DEVICEINTERFACE
            {
            internal Int32 dbcc_size;
            internal Int32 dbcc_devicetype;
            internal Int32 dbcc_reserved;
            internal Guid dbcc_classguid;
            internal Int16 dbcc_name;
            }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        internal class DEV_BROADCAST_DEVICEINTERFACE_1
            {
            internal Int32 dbcc_size;
            internal Int32 dbcc_devicetype;
            internal Int32 dbcc_reserved;
            [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.U1, SizeConst = 16)]
            internal Byte[] dbcc_classguid;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 255)]
            internal Char[] dbcc_name;
            }

        [StructLayout(LayoutKind.Sequential)]
        internal class DEV_BROADCAST_HDR
            {
            internal Int32 dbch_size;
            internal Int32 dbch_devicetype;
            internal Int32 dbch_reserved;
            }

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        internal static extern IntPtr RegisterDeviceNotification(
            IntPtr hRecipient,
            IntPtr NotificationFilter, 
            Int32 Flags
            );

        [DllImport("user32.dll", SetLastError = true)]
        internal static extern Boolean UnregisterDeviceNotification(
            IntPtr Handle
            );
        }
    }
