//
// Created by Adebayo Olabode on 11/2/18.
//

#include "bip32_bip39.h"
/*
const uint8_t *fromhex(const char *str)
{
    static uint8_t buf[FROMHEX_MAXLEN];
    size_t len = strlen(str) / 2;
    if (len > FROMHEX_MAXLEN) len = FROMHEX_MAXLEN;
    for (size_t i = 0; i < len; i++) {
        uint8_t c = 0;
        if (str[i * 2] >= '0' && str[i*2] <= '9') c += (str[i * 2] - '0') << 4;
        if ((str[i * 2] & ~0x20) >= 'A' && (str[i*2] & ~0x20) <= 'F') c += (10 + (str[i * 2] & ~0x20) - 'A') << 4;
        if (str[i * 2 + 1] >= '0' && str[i * 2 + 1] <= '9') c += (str[i * 2 + 1] - '0');
        if ((str[i * 2 + 1] & ~0x20) >= 'A' && (str[i * 2 + 1] & ~0x20) <= 'F') c += (10 + (str[i * 2 + 1] & ~0x20) - 'A');
        buf[i] = c;
    }
    return buf;
}*/



const char *generateMnemonic(int strength){
    const char *mnemonic = mnemonic_generate(strength);
    return mnemonic  ;
}

void  generateBip39Seeed(const char *mnemonic,uint8_t seed[64],const char *passphrase){

    mnemonic_to_seed(mnemonic, passphrase, seed,0);

}

void print_hex(uint8_t *s) {
    size_t len = strlen((char*)s);
    for(size_t i = 0; i < len; i++) {
        printf("%02x", s[i]);
    }
    printf("\n");
}

/**
void generateBip32RootKey(uint8_t seed[64],char rootkey[112]){
    //uint32_t fingerprint = 0;
    //HDNode node;
    // this generates our bip32 root key
    //int length = strlen(seed);
     hdnode_from_seed(seed,64, SECP256K1_NAME, &node);
    hdnode_serialize_private(&node, fingerprint, VERSION_PRIVATE, rootkey, strlen(rootkey));
    printf("root key:%s\n",rootkey);


}*/