# -*-coding:utf-8 -*-
import logging
import _thread
import gen_account   as ac
import get_bitcoin as bt

def write_file(pri, pub, btc_addr, btc_banlance):
    fo = open("btc.txt", "a+")
    fo.write("pri:"+ pri + "\npub:" + pub + "\naddress:" + btc_addr + "\nbalance:{}".format(btc_banlance))
    fo.close()

def notification(pri, pub, btc_addr, btc_banlance):
    print("pri: "+pri+"\npub: "+pub+"\nbtc_addr: "+btc_addr)
    print("balance:{}".format(btc_banlance))
    
    # 1.写文件通知
    write_file(pri, pub, btc_addr, btc_banlance)

if __name__ == "__main__":
    while 1:
        pass
        
    