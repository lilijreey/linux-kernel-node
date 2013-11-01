

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
