# 进程管理和调度的笔记  


### 进程切换
*    **中断**的优先级最高.

### 命名空间

### 进程组
*    作用: 简化里向组的所有成员发送信号的操作.用管道连接的进程包含在一个组中.

### 会话
*    用于终端的设计.

### 进程复制
*   linux实现了3个用于进程复制的函数
    1.   **fork** 一个重量级的调用。建立了父进程的一个完整副本。使用copy-on-write技术.
    2.   **vfork** 类似与fork，但是**不会创建父进程的数据副本**.相反父子进程共享数据. 并且**在子进程退出或开始前内核保证父进程处于阻塞状态**.
        也就是说,不管哪个进程改变了数据,父子都会看到.这和fork不一样.fork会立即创建子进程自己的数据副本).  
        __vfork__ 重要用于立即调用exec系列加载新程序的情况.
        __由于fork使用了copy-on-write 技术vfork不在有优势,应避免使用__. 
    3.   **clone** 产生线程.
*    do_fork上面的三个系统调用都使用do_fork实现


### COW copy-on-write

### exec  

##内核级别的process 

* `task_struct 进程描述符结构<linux/sched.h>`
   kernel 使用 `task_struct`  来关于进程，这个结构包含了一个进程
      的所有信息

*  进程状态 state 共有10种
   <script language=c>
   #define TASK_RUNNING		0       //	"R (running)",		/*   0 */
   #define TASK_INTERRUPTIBLE	1       //	"S (sleeping)",		/*   1 */
   #define TASK_UNINTERRUPTIBLE	2   //	"D (disk sleep)",	/*   2 */
   #define __TASK_STOPPED		4       //	"T (stopped)",		/*   4 */
   #define __TASK_TRACED		8       //	"t (tracing stop)",	/*   8 */
   #define EXIT_ZOMBIE	     	16      //	"Z (zombie)",		/*  16 */
   #define EXIT_DEAD		    32      //	"X (dead)",		/*  32 */
   #define TASK_DEAD	     	64      //	"x (dead)",		/*  64 */
   #define TASK_WAKEKILL		12      //	"K (wakekill)",		/* 128 */
   #define TASK_WAKING	     	256     //	"W (waking)",		/* 256 */
   </script>

* Linux 中所有的process都在一个树中，最顶层的process是 `init_task`
  `init_task` 自身是静态分配的, `init_task.parent 指向自己`

* 进程通过 `all_thread_info` 来分配内核栈

* `thread_info` 
   内核中对线程的表示， 定义是体系相关的
   `task_struck->stack 成员指向当前运行的线程 
     #define task_thread_info(task)	((struct thread_info *)(task)->stack)

## 内核线程
* 创建内核线程
  kthread_create 必须由其他内核线程创建
    新创建的线程不会主动运行，除非现世调用 wake_up_process()

* kthread_stop 

* 删除进程描述符 task_struct;
  do_exit() 后线程状态为EXIT_ZOMBIE
  线程终止后并不会清理内核堆栈 thread_info, task_struct 结构，会保留他们
  以被父进程处理。 所以只有在父进程wait后或明确通知内核不关心后才会
  删除task_struct. release_task()
  
## 进程调度
* O1 算法 
   在2.6.23 以前
   分公平但是对交互式应用的支持不足

* CFS 完全公平算法
  RSDL Rotating Staircase Deadline scheduler
  2.6.23 后代替了O1算法
  Linux 使用CPU的使用比来调度进程, 比如有10个进程，每个进程应该使用%10
   的CPU，但是实际中有的进程当前CPU使用率少于%10，他就会立即抢占，比他多的进程

