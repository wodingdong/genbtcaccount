
#include <stdint.h>
#include "bip32.h"
#include "curves.h"
#include "cash_addr.h"
#include "address.h"
#include "base58.h"
#include "bip32_bip39.h"
#include "base32_bch.h"
#include "ripemd160.h"
#include "bech32.h"

#include "getbtc.h"

// ‘§¥¶¿Ì
int pre_process_mnemonic(char  *mnemonic, char  *passphrase, uint8_t* bip39_seed)
{
	if (mnemonic_check(mnemonic)) {
		generateBip39Seeed(mnemonic, bip39_seed, passphrase);
		return CODE_SUCCESS;
	}
	else {
		return CODE_FAILSE;
	}
}

void get_version_pri_pub(int i, int *Purpose, uint32_t* v_pri, uint32_t* v_pub)
{
	// 44
	if (i == TYPE_1)
	{
		*Purpose = 44;
		*v_pri = VERSION_XPRIVATE;
		*v_pub = VERSION_XPUBLIC;
	}
	else if (i == TYPE_3)
	{
		*Purpose = 49;
		*v_pri = VERSION_BIP49_XPRIVATE;
		*v_pub = VERSION_BIP49_XPUBLIC;
	}
	else if (i == TYPE_bc)
	{
		*Purpose = 84;
		*v_pri = VERSION_BIP84_XPRIVATE;
		*v_pub = VERSION_BIP84_XPUBLIC;
	}
}

int hdnode_serialize(HDNode* node, uint8_t* bip39_seed, int Purpose, int Coin, uint32_t v_pri, uint32_t v_pub)
{
	char rootkey[112];
	uint32_t fingerprint = 0;
	//HDNode node;
	int r = hdnode_from_seed(bip39_seed, 64, SECP256K1_NAME, node);
	if (r != 1) {
		return CODE_FAILSE;
	}

	r = hdnode_serialize_private(node, fingerprint, v_pri, rootkey, sizeof(rootkey));
	if (r <= 0) {
		printf("hdnode_serialize_private failed (%d).", r);
		return CODE_FAILSE;
	}

	hdnode_private_ckd_prime(node, Purpose);
	hdnode_private_ckd_prime(node, Coin);
	hdnode_private_ckd_prime(node, 0);
	fingerprint = hdnode_fingerprint(node);
	hdnode_private_ckd(node, 0);

	//get xpub
	hdnode_fill_public_key(node);
	hdnode_serialize_public(node, fingerprint, v_pub, rootkey, sizeof(rootkey));
	if (r <= 0) {
		printf("hdnode_serialize_public failed (%d).", r);
		return CODE_FAILSE;
	}
	// memcpy(xpub, rootkey, strlen(rootkey));

	memset(rootkey, 0, sizeof(rootkey));
	hdnode_serialize_private(node, fingerprint, v_pri, rootkey, sizeof(rootkey));
	if (r <= 0) {
		printf("hdnode_serialize_private failed (%d).", r);
		return CODE_FAILSE;
	}
	//memcpy(xprv, rootkey, strlen(rootkey));

	//gener man address
	hdnode_private_ckd(node, 0);
	hdnode_fill_public_key(node);

	hdnode_serialize_public(node, fingerprint, v_pub, rootkey, sizeof(rootkey));
	if (r <= 0) {
		printf("hdnode_serialize_public failed (%d).", r);
		return -1;
	}

	return CODE_SUCCESS;

}

// bc1µÿ÷∑
void get_btc_address_bc(uint8_t* pubkey, char* addr)
{
	uint8_t addresshash[128] = { 0 };
	hasher_Raw(HASHER_SHA2_RIPEMD, pubkey, 33, addresshash);

	segwit_addr_encode(addr, "bc", 0, addresshash, 20);
}


void get_btc_address_1(uint8_t* pubkey, char* addr)
{
	ecdsa_get_address(pubkey, 0, HASHER_SHA2_RIPEMD, HASHER_SHA2D, addr, 35);
}

void get_btc_address_3(uint8_t* pubkey, char* addr)
{
	ecdsa_get_address_segwit_p2sh(pubkey, 5, HASHER_SHA2_RIPEMD, HASHER_SHA2D, addr, 35);
}

void get_btc_address(int addr_type, uint8_t* pubkey, char* addr)
{
	if (TYPE_1 == addr_type)
	{
		get_btc_address_1(pubkey, addr);
	}
	else if (TYPE_3 == addr_type)
	{
		get_btc_address_3(pubkey, addr);
	}
	else if (TYPE_bc == addr_type)
	{
		get_btc_address_bc(pubkey, addr);
	}
}

int gen_btc_account(const char* mnemonic, const char* passphrase, btc_account* accoun)
{
	uint8_t bip39_seed[64];
	pre_process_mnemonic(mnemonic, passphrase, bip39_seed);

	int Purpose = 0;
	int Coin = 0;
	uint32_t v_pri = 0;
	uint32_t v_pub = 0;
	for (int i = TYPE_1;i < TYPE_LAST;i++)
	{
		HDNode node;
		memzero(&node, sizeof(HDNode));
		v_pri = 0;
		v_pub = 0;
		get_version_pri_pub(i, &Purpose, &v_pri, &v_pub);
		if (CODE_FAILSE == hdnode_serialize(&node, bip39_seed, Purpose, Coin, v_pri, v_pub))
		{
			return CODE_FAILSE;
		}

		ecdsa_get_wif(node.private_key, 0x80, HASHER_SHA2D, accoun[i].pri, 53);
		get_btc_address(i, node.public_key, accoun[i].addr);
	}

	return CODE_SUCCESS;
}


int gen_mnemonic(int len, char* mnemonic)
{
	int check_len = 0;
	if (len!=12 && len!=15 && len!=18 && len!=21 &&len != 24)
	{
		return CODE_FAILSE;
	}

	switch (len)
	{
	case 12:
		check_len = 4;	break;
	case 15:
		check_len = 5;	break;
	case 18:
		check_len = 6;	break;
	case 21:
		check_len = 7;	break;
	case 24:
		check_len = 8;	break;
	}

	char* mn = mnemonic_generate(len * 11 - check_len);
	if (!mn)
	{
		return CODE_FAILSE;
	}

	memcpy(mnemonic, mn, strlen(mn) + 1);

	return CODE_SUCCESS;
}