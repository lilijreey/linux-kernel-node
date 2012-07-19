### 编译步骤
1. download src
2. compressed src
3. set config 配置编译选项
    * README.txt Makefile 中有详细说明 
    * make menuconfig 基于ncurses的终端图形配置，需要ncurses
    * make gconfig    基于gtk    的终端图形配置, 需要gtk2.0 libglade2-dev
    * make kconfig    基于Qt     的终端图形配置, 需要Qt
    * **指定输出文件的目录**(可以不用）    make O=dir/path  如果使用的O那么所有的make命令都要使用 or export `KBUILD_OUTPUT=dir/path`
4.  make bzImage  

### make mrproper
        清理当前目录下的.config .o 文件

### make dep 
