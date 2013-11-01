### 编译步骤
1. download src
2. compressed src
3. set config 配置编译选项
   +  kernel 提供了默认的配置选项 i386 的
     可以使用他来作为一个基础的配置
     make defconfig

   + 对于不同的架构，kernel可提供了默认的配置
     e.g x86_64  make  ARCH=x86_64 defconfig

     在这个后会在根目录生成一个 .cofing 的文件

     然后在做一些自己的调整
     
    * README.txt Makefile 中有详细说明 
    * make menuconfig 基于ncurses的终端图形配置，需要ncurses
    * make gconfig    基于gtk    的终端图形配置, 需要gtk2.0 libglade2-dev
    * make kconfig    基于Qt     的终端图形配置, 需要Qt
    * **指定输出文件的目录**(可以不用）    make O=dir/path  如果使用的O那么所有的make命令都要使用 or export `KBUILD_OUTPUT=dir/path`

4.  make bzImage  

5. install 必须以root 来执行
    + 安装模块
        make modules_install
       会安装所有的模块到 /lib/module/kernel_version

    + 安装内核执行文件
         make install
         将会，检查内核文件是否编译成功
         将会把文件安装到/boot 目录
         bootloader 程序会更新可用内核列表
         安装完成


### make mrproper
        清理当前目录下的.config .o 文件

### make dep 

