# 个人学习Linux内核的笔记。

* process-mng.md 
    内核进程笔记
* kernel-compiler.md 
    编译内核笔记
* device.md 
    驱动笔记

### 生成文档
*    make pdfdocs
*    make psdocs
*    make htmldocs
*    make mandocs

### 编译kernel所需的工具
*   Documentation/Changes

### Linux 虚拟TK
   LXC

Qus.
-----------------------------
1. 内核和用户空间是如何相互访问的
   copy_from_user, copy_to_user


Kernel Marco
-----------------------------
* #define __user __attribute__((noderef, address_space(1)))
  gcc __attribute__ 中没有noderef这个属性
  在kernel中这个Sparse工具识别这个属性
  __user 用来修饰一个变量，这个变量必须是非解引用的 no dereference = noderef
  而且变量所在空间必须是1 address_space(1).
  Sparse 工具把程序空间分为3部分，
   0 表示normal 即普通空间，即内核空间
   1 用户空间，
   2 设备地址映射空间，如设备寄存器在kernel中的映射空间
  上面的这写属性只有当系统安装了Sparse 这个工具并且编译时调用才起作用

* #define __safe __attribute__((safe))
  当函数的参数是指针但是有没有检查是否为NULL时，可以使用__safe修饰，
  意思是这个指针肯定不为NULL
    e.g.
   int test( struct a * __safe a, struct b * __safe b) {
    return a->a + b->b; }

boot.md linux 系统引导

grub/  grub 笔记
module/ kernl 模块 学习笔记

内核基础工具
--------------------------------
* |list_head| <include/linux/list.h>
    通用链表工具 <see> list.c

* |hlist_head| |list_node| <include/linux/list.h>
    通用hash表, 使用附加链表解决key冲突，
    hlist_head 是hash表中的项（entry) 如果有冲突则
    在hlist_head -> hlist_node. <see> hlist.c
               

Documentation/CodingStyle 表述的内核的编程风格
scripts/checkpatch.pl 提供了一个检查代码风格的脚本;


并发控制 parllet
------------------------------------------
每中机制都有他的适用前提，有缺点
* 中断屏蔽
  local_irq_disable
  local_irq_endable
    只能关闭和打开本CPU的中断，不能解决SMP的互斥

* 自旋锁
  spinlock_t lock;
  spin_lock_init(lock)

  lock
  spin_lock(lock)
  spin_trylock(lock) -> bool
  spin_unlock(lock)

* spin_lock_irq = spin_lock + lock_irq_disable

* 读写锁
  rwlock_t 

* seqlock 顺序锁
   ????

* RCU Read-Copy-Update
  适用于读多写少
  有很好的伸缩性
  对被RCU保护的结构，读操作不需要获得任何锁就可以访问他
  写操作，需要先Copy一个副本，然后对副本进行修改，最后使用一个
  回调机制在适当的时机把指向原来数据的指针重新指向新的被修改的数据。
  这个时机就是所有引用该数据的CPU都退出对共享数据的操作。
  + 有点： 读操作几乎没有什么开销，不需要锁，不使用原子指令
  + 缺点： 写操作的开销很大
  + RCU不能替代rwlock，因为如果写比较多时，
      对读者的性能提高不能弥补写者导致的损失。
     rcu_read_lock()
     rcu_read_lock_hb()
     rcu_read_unlock()
	..

   ????

内核提供的原子操作
--------------------------------------------
* integet atomic op
	atomic_set
	atomic_read
	atomic_add
	atomic_sub
	...
	atomic_op_return


* bit atomic op
  void set_bit(bit, void *addr)
  void chear_bit(bit, void *addr)
  void change_bit(bit, addr)
  test_bit(bit, void *addr)
  test_and_op_bit

Kernel Debug
-----------------------------------------------
*几个调试选项 在kernel hacking 菜单中
=======

内核延迟
-----------------------------------------------
* 短延迟
void ndelay(nsecs)
void udelay(usecs)
void mdelay(msecs)
	本质上的让CPU忙等待

void msleep(msecs) 睡眠
void ssleep(msecs) 睡眠 不能被打断
   msleep_interruptible 可以被打断

* 长延迟
  schedule_timeout
  long schedule_timeout(signed long timeout);
  long schedule_timeout_interruptible(signed long timeout);
  long schedule_timeout_killable(signed long timeout);
  long schedule_timeout_uninterruptible(signed long timeout);

Linux memory 管理
--------------------------------
* 内核空间
  被划分为多个区域
  +  保留区域FIXADDR_TOP 开始到4GB
  +  专用区域  FIXADDR_STAET ~ FIXADDR_TOP
  +  高端区域  PKMAP_BASE ~ FIXADDR_STAET
  +  vmalloc 分配区域 VMALLOC_START ~ VMALLOC_END
  +  物理映射区

* 内核空间动态内存申请 
  kmalloc/2, __get_free_pages,
     申请的内存在物理内存上连续，和物理地址的转换关系简单
     GFP_KERNE
     GFP_ATOMIC
  kfree/1
   
  vmalloc 子啊 vmalloc中分配，物理地址不一定连续, 和物理地址
       的转化关系比较负责
  
