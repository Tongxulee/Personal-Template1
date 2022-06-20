#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./aes/aes_crypto.h"
#include "./sha/sha2.h"

#define MAX_NUM_A_LINE	60u
int main(int argc , char const* argv[])
{
	char encrypo_data[SHA256_DIGEST_LENGTH];
	char buff[100] = {0};
	char tmpbuff[60] = {0};
	char position = 0u;
	FILE* fp = fopen("./tmp.hex" , "r");
	while (fgets(tmpbuff , MAX_NUM_A_LINE , fp) != NULL)
	{
		uint8_t len = strlen(tmpbuff);
		memcpy(&buff[position] , tmpbuff , len);
		position += len;
	}
	fclose(fp);
	//printf("%s\n" , buff);
	for (uint8_t i = 0;i < MAX_NUM_A_LINE;i++)
	{
		printf("%X" , buff[i]);
	}
	printf("\n");
	printf("%s" , buff);
	SHA256(buff , 46 , encrypo_data);
	for (uint8_t i = 0;i < SHA256_DIGEST_LENGTH;i++)
	{
		printf("%X" , encrypo_data[i]);
	}
	/* code */
	return 0;
}
