#include <stdio.h>
#include "getbtc.h"


int main()
{
	char mnemonic[256] = { 0 };
	const char* passphrase = "";
	char pri[256] = { 0 };
	char address[256] = { 0 };
	btc_account account[3] = { 0 };

	if (CODE_FAILSE == gen_mnemonic(15, mnemonic))
	{
		return -1;
	}

	printf("mnemonic:%s\n", mnemonic);

	if (CODE_FAILSE == gen_btc_account(mnemonic, passphrase, account))
	{
		return -1;
	}

	for (int i = TYPE_1;i < TYPE_LAST;i++)
	{
		printf("i:%d\npri:%s\naddr:%s\n", i, account[i].pri, account[i].addr);
	}


	system("pause");

	return 0;
}