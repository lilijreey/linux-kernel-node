linux kernel 编译
==============================
1. download src
2. compressed src

3. 配置内核
---------------------
   +  kernel 提供了默认的配置选项 i386 的
     可以使用他来作为一个基础的配置
     make defconfig

   + 对于不同的架构，kernel可提供了默认的配置
    arch/xxx/configs/ 下有各个平台的默认的配置文件;
     e.g x86_64  make  ARCH=x86_64 defconfig

     在这个后会在根目录生成一个 .cofing 的文件

     然后在做一些自己的调整
     
    * README.txt Makefile 中有详细说明 
    * make menuconfig 基于ncurses的终端图形配置，需要ncurses
    * make gconfig    基于gtk    的终端图形配置, 需要gtk2.0 libglade2-dev
    * make kconfig    基于Qt     的终端图形配置, 需要Qt
    * **指定输出文件的目录**(可以不用）    make O=dir/path  如果使用的O那么所有的make命令都要使用 or export `KBUILD_OUTPUT=dir/path`

2. 编译内核
-------------------------
make bzImage 
   生成 vmlinux
        System.map

make modules 编译内核模块
   生成 Module.symvers
        modules.builtin
        modules.order
        其他mod 文件

或者 make


3. 安装内核
------------------------
必须以root 来执行
    + 安装模块
        make modules_install
       会安装所有的模块到 /lib/module/kernel_version

    + 安装内核执行文件
         make install
         将会，检查内核文件是否编译成功
         将会把文件安装到/boot 目录
         bootloader 程序会更新可用内核列表
         安装完成

    +  (可选 安装kernel头文件)
       make headers_install 
 

4. 更新grub 一般不需要 make install 会自动更新
------------------------
update-grub

5. 重启 就好了

### 编译附加模块到内核
比如添加rtl8188cu(wifi 网卡) 驱动到linux
1. 下载原码

2. 把下载的原码加入内核树
-----------------------------
   cp rtl8192cu /kernel/drivers/net/wireless/
   修改wireless/ 下 Makefile 和 Kconfig 文件
     Makefile 文件中添加 obj-$(CONFIG_RTL8192CU) += rtl8192cu/
     Kconfig  文件中添加 source "drivers/net/wireless/rtl8192cu/Kconfig"



### /boot file详解 
* vmlinuz-3.2.0-38-generic
          是可执行的压缩内核

* config-3.2.0-29-generic 
        内核编译时的.config 文件

* System.map-3.2.0-29-generic
     内核符合映射表 通过 nm vmlinuz 产生

* initrd.img-3.2.0-29-generic
     initial ramdisk 的缩写  用来引导 kernel mount真正的文件系统
       是一个辅助工具
    使用 mkinitrd 工具创建 

* abi-3.2.0-38-generic


linux headers 
------------------------------------
默认情况下 把 /usr/src/linux-headers-3.2.0-35/include/linux/ 下的文件
mv 到 /usr/include/linux/ 下

make 选项
-----------------------------
make help 察看帮助
make mrproper 把原来编译产生的垃圾清除
make clean    类似于mrproper 保留.config
make dep 
