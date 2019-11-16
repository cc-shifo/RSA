
#include "./RSAEuro/global.h"

#include "./RSAEuro/rsaeuro.h"
#include "./RSAEuro/rsa.h"

#include <string.h>

//////////////////////////////////////////////////////////////////////////

typedef struct tagDESKey
{
	unsigned char szDesKey[24];
	unsigned char szDesIV[24];
} DESKey;

//////////////////////////////////////////////////////////////////////////

void DESKeyGenerate(unsigned char *pszDESKey, size_t nDESKeyLength)
{
	R_RANDOM_STRUCT randomStruct= { 0 };

	R_RandomCreate(&randomStruct);
	R_GenerateBytes(pszDESKey, nDESKeyLength, &randomStruct);
}

void DES3Update(int nEncrypt, unsigned char *pszKey, size_t nKeyLength, unsigned char *pszIV, size_t nIVLength, unsigned char *pszSrcText, size_t nSrcLength, unsigned char *pszDestText, size_t nDestLength)
{
	DES3_CBC_CTX CBCcontext	= { 0 };

	if (pszKey == NULL || nKeyLength != 24 || pszIV == NULL || nIVLength != 24) {
		return;
	}
	if (pszSrcText == NULL || (nSrcLength % 24) != 0) {
		return;
	}
	if (pszDestText == NULL || (nDestLength % 24) != 0) {
		return;
	}
	if (nDestLength != nSrcLength || nDestLength == 0) {
		return;
	}

	DES3_CBCInit(&CBCcontext, pszKey, pszIV, nEncrypt);

	for (int i = 0; i < nSrcLength; i += 24) {
		DES3_CBCUpdate(&CBCcontext, &(pszDestText[i]), &(pszSrcText[i]), 24);
	}
}

//////////////////////////////////////////////////////////////////////////

bool RSAKeyGenerate(R_RANDOM_STRUCT *randomStruct, R_RSA_PUBLIC_KEY *publicKey, R_RSA_PRIVATE_KEY *privateKey)
{
	R_RSA_PROTO_KEY protoKey = { MAX_RSA_MODULUS_BITS, 1, };

	bool ret = false;
	if (randomStruct == NULL || publicKey == NULL || privateKey == NULL) {
		goto Exit;
	}
	R_RandomCreate(randomStruct);
	if (R_GeneratePEMKeys(publicKey, privateKey, &protoKey, randomStruct) != 0) {
		goto Exit;
	}

	ret = true;
Exit:
	return ret;
}

//////////////////////////////////////////////////////////////////////////

void DemoDES()
{
	DESKey desKey = { 0 };
	DESKeyGenerate((unsigned char *) &desKey, sizeof(desKey));

	unsigned char szPlain[]	= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	size_t nBufferLength = sizeof(szPlain);
	while (nBufferLength % 24 != 0) {
		++nBufferLength;
	}
	unsigned char *pPlainBuffer = new unsigned char[nBufferLength];
	unsigned char *pCipherBuffer= new unsigned char[nBufferLength];

	memset(pPlainBuffer, 0, nBufferLength);
	memset(pCipherBuffer, 0, nBufferLength);

	//	Crypt
	memcpy(pPlainBuffer, szPlain, sizeof(szPlain));
	DES3Update(1, desKey.szDesKey, sizeof(desKey.szDesKey), desKey.szDesIV, sizeof(desKey.szDesIV), pPlainBuffer, nBufferLength, pCipherBuffer, nBufferLength);

	//	Decrypt
	memset(pPlainBuffer, 0, nBufferLength);
	DES3Update(0, desKey.szDesKey, sizeof(desKey.szDesKey), desKey.szDesIV, sizeof(desKey.szDesIV), pCipherBuffer, nBufferLength, pPlainBuffer, nBufferLength);

	delete []pPlainBuffer;
	delete []pCipherBuffer;

	pPlainBuffer = NULL;
	pCipherBuffer= NULL;
}

void DemoRSA()
{
	R_RANDOM_STRUCT randomStruct = { 0 };
	R_RSA_PUBLIC_KEY publicKey = { 0 };
	R_RSA_PRIVATE_KEY privateKey = { 0 };
	RSAKeyGenerate(&randomStruct, &publicKey, &privateKey);

	unsigned char szText[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned char szPlain[sizeof(szText)] = { 0 };
	unsigned char szCipher[MAX_RSA_MODULUS_LEN]	= { 0 };
	unsigned int nEncryptedLength = 0;
	memcpy(szPlain, szText, sizeof(szText));

	int ret = 0;
	ret = RSAPublicEncrypt(szCipher, &nEncryptedLength, szPlain, sizeof(szPlain), &publicKey, &randomStruct);
	memset(szPlain, 0, sizeof(szPlain));
	ret = RSAPrivateDecrypt(szPlain, &nEncryptedLength, szCipher, MAX_RSA_MODULUS_LEN, &privateKey);

	//////////////////////////////////////////////////////////////////////////

	ret = RSAPrivateEncrypt(szCipher, &nEncryptedLength, szPlain, sizeof(szPlain), &privateKey);
	memset(szPlain, 0, sizeof(szPlain));
	ret = RSAPublicDecrypt(szPlain, &nEncryptedLength, szCipher, MAX_RSA_MODULUS_LEN, &publicKey);
}

//////////////////////////////////////////////////////////////////////////

int main()
{
	DemoDES();
	DemoRSA();

	return 0;
}
