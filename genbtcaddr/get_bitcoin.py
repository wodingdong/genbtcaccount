# -*-coding:utf-8 -*-
import requests

def is_zero_balance(balance):
    balance_float = 0.0
    if isinstance(balance, str):
        print("balance:{}".format(balance))
        if len(balance) > 0:
            balance_float = float(balance)
    else:
        balance_float = balance
    
    return balance_float > 0

def get_bitcoin_balance(address):
    # 拼接链接
    url = "".join(["https://www.blockchain.com/btc/address/", address])
    response = requests.get(url)
    key_word = "The current value of this address is"
    key_len = len(key_word)
    text = response.text
    index = text.find(key_word)
    short = text[index:index+100]
    btc = short.find("BTC")
    
    btc_banlance = short[key_len+1:btc-1]
    
    return btc_banlance

if __name__ == "__main__":
    try:
        # address = "3JZHLAKwc291dnxjwLyDDfnmQkbTNwC7PX"
        # address = "bc1qcn6xjvfy6uqyqqnzmwxeqqtnk9cmtcpummn8la"
        address = "bc1qeysmlpayh0pqe4xuv6prllww8549sdy8754eyt6ks5tdnzhv2qwq3nktw6"
        btc_banlance = get_bitcoin_balance(address)
        
        if is_zero_balance(btc_banlance):
            print("find valide adress:" + address)
        else:
            print("continu find!")
    
    except Exception as err:
        print("error, " + err)





