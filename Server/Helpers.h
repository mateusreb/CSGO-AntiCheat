#pragma once

namespace Helpers
{
	RandomPool& GlobalRNG()
	{
		static RandomPool randomPool;
		return randomPool;
	}

	void GenerateRSAKey(unsigned int keyLength, const char* privFilename, const char* pubFilename, const char* seed)
	{
		RandomPool randPool;
		randPool.IncorporateEntropy((byte*)seed, strlen(seed));

		RSAES_OAEP_SHA_Decryptor priv(randPool, keyLength);
		FileSink privFile(privFilename);
		priv.AccessMaterial().Save(privFile);
		privFile.MessageEnd();

		RSAES_OAEP_SHA_Encryptor pub(priv);
		FileSink pubFile(pubFilename);
		pub.AccessMaterial().Save(pubFile);
		pubFile.MessageEnd();
	}

	void RSAEncryptBytes(const char* pubFilename, const char* seed, byte* buffer, size_t bytes)
	{
		FileSource pubFile(pubFilename, true);
		RSAES_OAEP_SHA_Encryptor pub(pubFile);
		RandomPool randPool;
		randPool.IncorporateEntropy((byte*)seed, strlen(seed));
		ArraySource(buffer, true, new PK_EncryptorFilter(randPool, pub, new ArraySink(buffer, bytes)));
	}

	void RSADecryptBytes(const char* privFilename, byte* buffer, size_t bytes)
	{
		FileSource privFile(privFilename, true);
		RSAES_OAEP_SHA_Decryptor priv(privFile);
		ArraySource(buffer, true, new PK_DecryptorFilter(GlobalRNG(), priv, new ArraySink(buffer, bytes)));
	}

	template <typename T>
	bool Serealize(PROTOCOL_LIST protocol, void* out, T* in, size_t bytes)
	{
		PACKET_HEADER header;
		if (bytes > 0)
		{
			uint32_t myseed = 0;
			XXHash32 myhash(myseed);
			myhash.add(in, bytes);

			header.protocol = protocol;
			header.length = (uint32_t)bytes;
			header.checksum = myhash.hash();
			if (header.length > 0)
			{
				memcpy(out, &header, sizeof(PACKET_HEADER));
				memcpy((void*)((char*)out + sizeof(PACKET_HEADER)), in, header.length);
				return true;
			}
		}
		return false;
	}

	PACKET_HEADER DeserializeProtocol(void* in, size_t bytes)
	{
		PACKET_HEADER header;
		if (bytes > 0)
		{
			uint32_t myseed = 0;
			XXHash32 myhash(myseed);
			memcpy(&header, in, sizeof(PACKET_HEADER));			
			return header;
		}
		return { PROTOCOL_LIST::PROTOCOL_UNKNOWN, 0, 0 };
	}

	template <typename T>
	bool DeserializeMsg(PACKET_HEADER header, T* out, void* in, size_t bytes)
	{
		uint32_t myseed = 0;
		XXHash32 myhash(myseed);
		printf("Header: %X %X %i\n", header.protocol, header.checksum, header.length);
		memcpy(out, (const void*)((char*)in + sizeof(PACKET_HEADER)), bytes);
		myhash.add(out, bytes);
		printf("Hash: %X - %X\n", myhash.hash(), header.checksum);
		if (header.checksum == myhash.hash())
		{
			return true;
		}
		return false;
	}
}