#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./aes/aes_crypto.h"
#include "./sha/sha2.h"

#define MAX_NUM_A_LINE	(1024)

void AES_CBC_Test(void);

int main(int argc , char const* argv[])
{
	uint8_t encrypo_data[SHA256_DIGEST_LENGTH];
	uint8_t buff[MAX_NUM_A_LINE] = {0};
	uint8_t tmpbuff[60] = {0};
	uint8_t position = 0u;
	uint16_t i = 0;
	SHA256_CTX c;
	FILE* fp = fopen("./tmp.hex" , "rb");
	FILE* fp2 = fopen("./FVC2cal.hex" , "rb");
	SHA256_Init(&c);

	while (!feof(fp2))
	{
		unsigned int nCount = fread(buff , 1 , MAX_NUM_A_LINE , fp2);
		if (ferror(fp2))
		{
			printf("\nAn error occurred when accessing the file\n");
			fclose(fp2);
			return 0;
		}
		SHA256_Update(&c , buff , nCount);
		printf("count: %d  readbyte: %d\n" , i++ , nCount);
	}
	printf("hash dowm!\n");
	SHA256_Final(encrypo_data , &c);
	printf("hash final!\n");
	memset(&c , 0 , sizeof(c));
	fclose(fp2);
	//printf("%s\n" , buff);
	for (uint8_t i = 0;i < SHA256_DIGEST_LENGTH;i++)
	{
		printf("%X" , encrypo_data[i]);
	}
	AES_CBC_Test();
	/* code */
	return 0;
}

void AES_CBC_Test(void)
{
	uint8_t key[16] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x61,0x62,0x63,0x64,0x65,0x66};
	uint8_t iv[16] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30};

	uint8_t* msg = "0123456789abcdef";
	uint8_t encrypo_data[SHA256_DIGEST_LENGTH];
	uint8_t encrypt_MAC[16];
	int MAClen = 16;
	SHA256(msg , 16 , encrypo_data);
	aes_encrypt_cbc(key , 16 , iv , msg , 16 , encrypt_MAC , &MAClen);
	printf("\n**********CBC Test start**********\n");
	//after encrypto maclen is set to 32
	for (uint8_t i = 0; i < 16;i++)
	{
		printf("%X" , encrypt_MAC[i]);
	}
	printf("\n**********CBC Test end**********\n");
}