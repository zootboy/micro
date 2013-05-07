//-----------------------------------------------------------------------------
//
//  hidDll.cs
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

using Microsoft.Win32.SafeHandles;
using System.Runtime.InteropServices;

// The following namespace allows debugging output (when compiled in debug mode)
using System.Diagnostics;

namespace usbGenericHidCommunications
    {
    /// <summary>
    /// hidDll - Partial class containing the API definitions required for interoperability
    /// with the hdd.dll API from the Windows Driver Kit (WDK).  Primarily this provides
    /// methods for communicating with Windows' USB generic HID driver.
    /// </summary>
    public partial class usbGenericHidCommunication
        {
        // API declarations for hid.dll, taken from hidpi.h (part of the 
        // Windows Driver Kit (WDK

        internal const Int16 HidP_Input = 0;
        internal const Int16 HidP_Output = 1;
        internal const Int16 HidP_Feature = 2;

        [StructLayout(LayoutKind.Sequential)]
        internal struct HIDD_ATTRIBUTES
            {
            internal Int32 size;
            internal UInt16 vendorId;
            internal UInt16 productId;
            internal UInt16 versionNumber;
            }

        internal struct HIDP_CAPS
            {
            internal Int16 usage;
            internal Int16 usagePage;
            internal Int16 inputReportByteLength;
            internal Int16 outputReportByteLength;
            internal Int16 featureReportByteLength;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 17)]
            internal Int16[] reserved;
            internal Int16 numberLinkCollectionNodes;
            internal Int16 numberInputButtonCaps;
            internal Int16 numberInputValueCaps;
            internal Int16 numberInputDataIndices;
            internal Int16 numberOutputButtonCaps;
            internal Int16 numberOutputValueCaps;
            internal Int16 numberOutputDataIndices;
            internal Int16 numberFeatureButtonCaps;
            internal Int16 numberFeatureValueCaps;
            internal Int16 numberFeatureDataIndices;
            }

        //internal struct HidP_Value_Caps
        //    {
        //    internal Int16 usagePage;
        //    internal Byte reportID;
        //    internal Int32 isAlias;
        //    internal Int16 bitField;
        //    internal Int16 linkCollection;
        //    internal Int16 linkUsage;
        //    internal Int16 linkUsagePage;
        //    internal Int32 isRange;
        //    internal Int32 isStringRange;
        //    internal Int32 isDesignatorRange;
        //    internal Int32 isAbsolute;
        //    internal Int32 hasNull;
        //    internal Byte reserved;
        //    internal Int16 bitSize;
        //    internal Int16 reportCount;
        //    internal Int16 reserved2;
        //    internal Int16 reserved3;
        //    internal Int16 reserved4;
        //    internal Int16 reserved5;
        //    internal Int16 reserved6;
        //    internal Int32 logicalMin;
        //    internal Int32 logicalMax;
        //    internal Int32 physicalMin;
        //    internal Int32 physicalMax;
        //    internal Int16 usageMin;
        //    internal Int16 usageMax;
        //    internal Int16 stringMin;
        //    internal Int16 stringMax;
        //    internal Int16 designatorMin;
        //    internal Int16 designatorMax;
        //    internal Int16 dataIndexMin;
        //    internal Int16 dataIndexMax;
        //    }

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_FlushQueue(
            SafeFileHandle HidDeviceObject
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_FreePreparsedData(
            IntPtr PreparsedData
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_GetAttributes(
            SafeFileHandle HidDeviceObject,
            ref HIDD_ATTRIBUTES Attributes
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_GetFeature(
            SafeFileHandle HidDeviceObject,
            Byte[] lpReportBuffer,
            Int32 ReportBufferLength
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_GetInputReport(
            SafeFileHandle HidDeviceObject,
            Byte[] lpReportBuffer,
            Int32 ReportBufferLength);

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern void HidD_GetHidGuid(
            ref System.Guid HidGuid
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_GetNumInputBuffers(
            SafeFileHandle HidDeviceObject,
            ref Int32 NumberBuffers
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_GetPreparsedData(
            SafeFileHandle HidDeviceObject,
            ref IntPtr PreparsedData
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_SetFeature(
            SafeFileHandle HidDeviceObject,
            Byte[] lpReportBuffer,
            Int32 ReportBufferLength);

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_SetNumInputBuffers(
            SafeFileHandle HidDeviceObject,
            Int32 NumberBuffers
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_SetOutputReport(
            SafeFileHandle HidDeviceObject,
            Byte[] lpReportBuffer,
            Int32 ReportBufferLength
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Int32 HidP_GetCaps(
            IntPtr PreparsedData,
            ref HIDP_CAPS Capabilities
            );

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Int32 HidP_GetValueCaps(
            Int32 ReportType,
            Byte[] ValueCaps,
            ref Int32 ValueCapsLength,
            IntPtr PreparsedData
            );
        }
    }
