#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./aes/aes_crypto.h"
#include "./sha/sha2.h"

#define MAX_NUM_A_LINE	(1024)
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
	/* code */
	return 0;
}
