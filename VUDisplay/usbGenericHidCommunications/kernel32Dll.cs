//-----------------------------------------------------------------------------
//
//  kernel32Dll.cs
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

namespace usbGenericHidCommunications
    {
    /// <summary>
    /// kernel32Dll - Internal class containing the API definitions required for interoperability
    /// with the kernel32.dll.  Primarily this provides file operation methods required for
    /// sending and receiving data from Windows' USB generic HID driver.
    /// </summary>
    public partial class usbGenericHidCommunication
        {
        internal const Int32 FILE_FLAG_OVERLAPPED = 0x40000000;
        internal const Int32 FILE_SHARE_READ = 1;
        internal const Int32 FILE_SHARE_WRITE = 2;
        internal const UInt32 GENERIC_READ = 0x80000000;
        internal const UInt32 GENERIC_WRITE = 0x40000000;
        internal const Int32 INVALID_HANDLE_VALUE = -1;
        internal const Int32 OPEN_EXISTING = 3;
        internal const Int32 WAIT_TIMEOUT = 0x102;
        internal const Int32 WAIT_OBJECT_0 = 0;

        [StructLayout(LayoutKind.Sequential)]
        internal class SECURITY_ATTRIBUTES
            {
            internal Int32 nLength;
            internal Int32 lpSecurityDescriptor;
            internal Int32 bInheritHandle;
            }

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern Int32 CancelIo(
            SafeFileHandle hFile
            );

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        internal static extern IntPtr CreateEvent(
            IntPtr SecurityAttributes,
            Boolean bManualReset,
            Boolean bInitialState,
            String lpName
            );

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        internal static extern SafeFileHandle CreateFile(
            String lpFileName,
            UInt32 dwDesiredAccess,
            Int32 dwShareMode,
            IntPtr lpSecurityAttributes,
            Int32 dwCreationDisposition,
            Int32 dwFlagsAndAttributes,
            Int32 hTemplateFile
            );

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        internal static extern Boolean GetOverlappedResult(
            SafeFileHandle hFile,
            IntPtr lpOverlapped,
            ref Int32 lpNumberOfBytesTransferred,
            Boolean bWait
            );

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern Boolean ReadFile(
            SafeFileHandle hFile,
            IntPtr lpBuffer,
            Int32 nNumberOfBytesToRead,
            ref Int32 lpNumberOfBytesRead,
            IntPtr lpOverlapped
            );

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern Int32 WaitForSingleObject(
            IntPtr hHandle,
            Int32 dwMilliseconds);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern Boolean WriteFile(
            SafeFileHandle hFile,
            Byte[] lpBuffer,
            Int32 nNumberOfBytesToWrite,
            ref Int32 lpNumberOfBytesWritten,
            IntPtr lpOverlapped
            );
        }
    }
