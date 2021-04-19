# cmake最低版本要求
cmake_minimum_required (VERSION 3.10)

# 项目名称
project (genbtcaddr)

# 添加源文件
aux_source_directory(. DIR_LIB_SRCS)
# 将目录下的源文件也包含进来
aux_source_directory(aes DIR_LIB_SRCS)
aux_source_directory(ed25519-donna DIR_LIB_SRCS)

# 头文件要包含的目录
include_directories(aes)
include_directories(ed25519-donna)

# 指定生成目标
add_library(genbtcaddr SHARED ${DIR_LIB_SRCS})
