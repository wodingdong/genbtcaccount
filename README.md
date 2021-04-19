# genbtcaccount

穷举助记词，使用C程序生成助记词，以及生成对应的私钥和地址，生成是三种地址(1开头地址，3开头地址，bc开头地址)。使用python调用C的程序，将对地址到[blockchain](https://www.blockchain.com/explorer)上去查余额，若有余额，则记下当前的私钥和地址信息。

```
b'social cricket gold tent mandate join gather kick toddler trash vibrant liquid'
b''
L1E3pdz7iE68JEFRZLFAiXX1rjdLwFfC6LEwrtCwMNkPftRSyK4n
1FtLyyZNxMPbFGGNPSe3dpkKahRDRiE6Jq
balance:0.00000000
*******************continue find!*******************
L1H2WpE5RHQ5HrJfacwyJ2kvRz2Bx1mmKCauaDGqMdSoU1MiiG8C
3DDmEBR6KjrAE3EqNcuSNTobxPK5giGKGG
balance:0.00000000
*******************continue find!*******************
L4f1BkxDYsY5bxXvLT5a2Fw3XFaEpZ3wJuLuBriMFH6GatCv8KcP
bc1qkntgl3aujc6aenmxgdmmh7j8y5ah6jq2dt0way
balance:0.00000000
*******************continue find!*******************
```



------

注意：此程序仅供研究和学习