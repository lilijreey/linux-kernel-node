linux 系统引导
================================

1. 当系统上电或复位时， CPU会吧PC寄存器设置为 *0xFFF0* 
   并从该地址执行指令。 在PC机上该地址位于BIOS中

2. BIOS 按照COMS 中的设定来查找可引导的设备，(就是bios中的boot 选项)
    若是从硬盘引导， BIOS会将硬盘上的MBR 加载到RAM中， 然后将控制权
       让给MBR

3. 主引导程序会查找并加载从引导程序，
  Qus. GRUB 是从引导程序吗？

4. 从引导程序加载linux内核和可选的RAM磁盘(/boot/initrd.img-3.2.0-38-generic),
   并将控制权交给linux内核

5. kernel(/boot/vmlinuz-3.2.0-38-generic) 自解压部kernel
   `start() -> startup_32() -> start_kernel() -> cpu_idle()
    

Bootloader
==================================
能做系统上电或复位的时候一某中方式执行
能将U盘， 磁盘， 光盘， Flash SD 网卡 等介质中的
操作系统加载到RAM，并把控制权交给OS

常见的linux Bootloader 有 LILO,GRUB,U-Boot 等


## GRUB
GRUB 设备命名规则
 (xdn[,m]) 
 xd 代表磁盘类型， e.g fd, hd
 n 是BIOS的编号顺序，从0开始，
 m 代表分区号，从0开始
  e.g (fd0)
      (hd0,1)

* 安装GRUB到磁盘
  grub-install '(hd0)'

  或者在 grub shell 中
    root (hd0,0)
    setup (hd0)

* 当GRUB找不到配置文件时，开机后会进入grub shell
  这时可以使用
  1 root device
  2 kernel filename [optin]
  3 initrd filename
  4 boot
  来主动引导启动

	set root='hd0,msdos6'
	linux	/boot/vmlinuz-3.8.0-32-generic root=UUID=f47d093a-c297-49f2-ab23-c34c9fe6c98d ro   quiet splash $vt_handoff
	initrd	/boot/initrd.img-3.8.0-32-generic
