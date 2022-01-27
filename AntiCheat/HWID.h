#pragma once

#include <intrin.h>

__int16 getCpuHash() 
{
	int cpuinfo[4] = { 0, 0, 0, 0 };
	__cpuid(cpuinfo, 0);
	__int16 hash = 0;
	__int16* ptr = (__int16*)(&cpuinfo[0]);
	for (__int32 i = 0; i < 8; i++)
		hash += ptr[i];
	return hash;
}

DWORD GetPhysicalDriveSerialNumber(INT nDriveNumber, std::string& strSerialNumber)
{
	DWORD dwResult = NO_ERROR;
	std::string DrvNumber = "\\\\.\\PhysicalDrive" + std::to_string(nDriveNumber);
	HANDLE hDevice = CreateFileA(DrvNumber.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (INVALID_HANDLE_VALUE == hDevice)
		return GetLastError();

	STORAGE_PROPERTY_QUERY storagePropertyQuery;
	ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
	storagePropertyQuery.PropertyId = StorageDeviceProperty;
	storagePropertyQuery.QueryType = PropertyStandardQuery;

	STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
	DWORD dwBytesReturned = 0;

	if (!::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY), &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &dwBytesReturned, NULL))
	{
		dwResult = ::GetLastError();
		::CloseHandle(hDevice);
		return dwResult;
	}

	const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
	BYTE* pOutBuffer = new BYTE[dwOutBufferSize];
	ZeroMemory(pOutBuffer, dwOutBufferSize);

	if (!DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY), pOutBuffer, dwOutBufferSize, &dwBytesReturned, NULL))
	{
		dwResult = GetLastError();
		delete[]pOutBuffer;
		CloseHandle(hDevice);
		return dwResult;
	}
	STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
	DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
	if (dwSerialNumberOffset != 0)
	{
		strSerialNumber = std::string(reinterpret_cast<char*>(pOutBuffer + dwSerialNumberOffset));		
	}
	delete[]pOutBuffer;
	CloseHandle(hDevice);
	return dwResult;
}

std::string GetDriverSerial(INT nDriveNumber)
{
	std::string strSerialNumber;
	DWORD dwResult = GetPhysicalDriveSerialNumber(nDriveNumber, strSerialNumber);
	if (NO_ERROR == dwResult)
	{
		return strSerialNumber;
	}
	else
	{
		printf("ERROR HWID\n");
		return "";
	}
}