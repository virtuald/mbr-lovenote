/*
    Copyright (C) 2007 Dustin Spicuzza

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	

	This code does the work. Enough said. :p
*/

#include "stdafx.h"

#include "Resource.h"
#include <WinIoCtl.h>
#include <strsafe.h>

void ShowError(LPTSTR lpszFunction);

/*

	Thanks to http://www.codeguru.com/Cpp/W-P/system/misc/article.php/c5765/ for
	the original reading/writing code

*/

void write_message(char message[], DWORD length){

	int i;
	HANDLE hDrive;
	HGLOBAL res;
	DWORD ioRet;
	LPVOID ptr;

	char oldMbr[512];
	char newMbr[512];

	ZeroMemory(oldMbr,512);
	ZeroMemory(newMbr,512);

	hDrive = CreateFile(_T("\\\\.\\PhysicalDrive0"),GENERIC_ALL,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,NULL,NULL);

	if(!hDrive){

		ShowError(_T("Opening drive"));
		return;
	}

	// replacement for exceptions.. heh
	while (true){

		// if disk is writable..
		if(!DeviceIoControl(hDrive,IOCTL_DISK_IS_WRITABLE,NULL,0,NULL,0,&ioRet,NULL)){
			ShowError(_T("Checking to see if disk is writable"));
			break;
		}

		// read old MBR
		SetFilePointer(hDrive,0,NULL,FILE_BEGIN);
		if (!ReadFile(hDrive,&oldMbr,512,&ioRet,NULL)){
			ShowError(_T("Initial MBR Read"));
			break;
		}

		// read new MBR
		if (!(res = LoadResource(NULL,FindResource(NULL,MAKEINTRESOURCE(IDR_MBR1),_T("MBR"))))){
			ShowError(_T("Reading MBR resource"));
			break;
		}

		if (!(ptr = LockResource(res))){
			ShowError(_T("Getting MBR resource data"));
			break;
		}

		// put it into a nicer buffer
		memcpy(newMbr,ptr,512);

		// fixup the new MBR
		memcpy(newMbr + 0x01b0, oldMbr + 0x01b0, 0x40);

		// ensure the old MBR is not ours, check ID bytes -- that could really screw things up
		for (i = 2;i < 10;i++)
			if (newMbr[i] != oldMbr[i])
				break;

		// they're the same, so don't overwrite
		if (i != 512){
		
			// write old mbr first
			SetFilePointer(hDrive,512,0,FILE_BEGIN);
			if (!WriteFile(hDrive,&oldMbr,512,&ioRet,NULL)){
				ShowError(_T("Writing old MBR"));
				break;
			}

			// write new mbr next
			SetFilePointer(hDrive,0,0,FILE_BEGIN);
			if (!WriteFile(hDrive,&newMbr,512,&ioRet,NULL)){
				ShowError(_T("Writing new MBR"));
				break;
			}
		}

		// write message last, you MUST round it to 512, or it fails
		SetFilePointer(hDrive,1024,0,FILE_BEGIN);
		if (!WriteFile(hDrive,message,((length+1) / 512)*512 + 512,&ioRet,NULL)){
			ShowError(_T("Writing message"));
			break;
		}

		MessageBox(NULL,_T("Success!"),_T(""),MB_OK);

		// done
		break;
	}

	CloseHandle(hDrive);

}


// this is from MSDN

void ShowError(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}