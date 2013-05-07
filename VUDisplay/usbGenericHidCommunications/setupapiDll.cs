//-----------------------------------------------------------------------------
//
//  setupapiDll.cs
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
    /// setupapiDll - Internal class containing the API definitions required for interoperability
    /// with the setupapi.dll.  Primarily this provides methods for device discovery and 
    /// identification.
    /// </summary>
    public partial class usbGenericHidCommunication
        {
        // from setupapi.h
        internal const Int32 DIGCF_PRESENT = 2;
        internal const Int32 DIGCF_DEVICEINTERFACE = 0X10;

        internal struct SP_DEVICE_INTERFACE_DATA
            {
            internal Int32 cbSize;
            internal System.Guid InterfaceClassGuid;
            internal Int32 Flags;
            internal IntPtr Reserved;
            }

        //internal struct SP_DEVICE_INTERFACE_DETAIL_DATA
        //    {
        //    internal Int32 cbSize;
        //    internal String DevicePath;
        //    }

        //internal struct SP_DEVINFO_DATA
        //    {
        //    internal Int32 cbSize;
        //    internal System.Guid ClassGuid;
        //    internal Int32 DevInst;
        //    internal Int32 Reserved;
        //    }

        [DllImport("setupapi.dll", SetLastError = true)]
        internal static extern Int32 SetupDiCreateDeviceInfoList(
            ref System.Guid ClassGuid,
            Int32 hwndParent
            );

        [DllImport("setupapi.dll", SetLastError = true)]
        internal static extern Int32 SetupDiDestroyDeviceInfoList(
            IntPtr DeviceInfoSet
            );

        [DllImport("setupapi.dll", SetLastError = true)]
        internal static extern Boolean SetupDiEnumDeviceInterfaces(
            IntPtr DeviceInfoSet,
            IntPtr DeviceInfoData,
            ref System.Guid InterfaceClassGuid,
            Int32 MemberIndex,
            ref SP_DEVICE_INTERFACE_DATA DeviceInterfaceData
            );

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        internal static extern IntPtr SetupDiGetClassDevs(
            ref System.Guid ClassGuid,
            IntPtr Enumerator,
            IntPtr hwndParent,
            Int32 Flags
            );

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        internal static extern Boolean SetupDiGetDeviceInterfaceDetail(
            IntPtr DeviceInfoSet,
            ref SP_DEVICE_INTERFACE_DATA DeviceInterfaceData,
            IntPtr DeviceInterfaceDetailData,
            Int32 DeviceInterfaceDetailDataSize,
            ref Int32 RequiredSize,
            IntPtr DeviceInfoData);
        }
    }
