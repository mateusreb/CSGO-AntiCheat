#pragma once

class PacketBuffer
{
public:
	size_t m_ReadPosition;
	size_t m_WritePosition;
	std::vector<uint8_t> m_Buffer;

	PacketBuffer(uint32_t initializeSize) : m_WritePosition(0), m_ReadPosition(0), m_Buffer(initializeSize, 0)
	{
		m_ReadPosition = 0;
		m_WritePosition = 0;
	}

	bool Read(void* buffer, size_t length)
	{
		if (buffer && length)
		{
			memcpy(buffer, &m_Buffer[m_ReadPosition], length);
			m_ReadPosition += length;
			return true;
		}
		return false;
	}

	bool Write(const void* buffer, size_t length)
	{
		if (buffer && length)
		{
			memcpy(&m_Buffer[m_WritePosition], buffer, length);
			m_WritePosition += length;
			return true;
		}
		return false;
	}

	~PacketBuffer()
	{
		m_ReadPosition = 0;
		m_WritePosition = 0;
		m_Buffer.clear();
	}
};