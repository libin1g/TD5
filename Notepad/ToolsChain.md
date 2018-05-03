# My Tools (Kits) Chain

## Debugging Tools for Windows 
1. Downloading refer to [website](http://www.windbg.org/)
2. 澄清：如果对Windows平台的软件开发做一划分，那么最先能掕出来说的是基于SDK的开发和基于WDK的开发。
   这些往往会涉及术语：
   - SDK指的是Software Developer Kit
   - WDK指的是Windows Driver Kit，相比较Windows之前的DDK，WDK基于Windows最新的驱动开发框架
   - 微软往往伴随着操作系统的发布、更新，去同步发布适配的SDK和WDK。微软的IDE(vs2010等)
     安装时可根据用户选择一并安装对应的SDK、WDK, IDE的发布也往往跟随着操作系统的发布、更新。
   - SDK或WDK安装包往往还提供了Debugging Tools for Windows供用户选择安装。但是更多的时候,
     开发者们更喜欢独立下载安装[Debugging Tools for Windows](https://developer.microsoft.com/en-us/windows/hardware/download-windbg). 

## 泄漏诊断工具 Leak Diagnosis Tool(LeakDiag)
   * 泄漏诊断或许还会用到Microsoft Detours, 她是一种在二进制机器代码级别上对现有代码进行修改或增强的解决方案。通过Microsoft
   Detours可以拦截二进制机器代码级别上的函数执行，然后提供自己的函数做以替换，也可以在调用原来函数之前增加一些代码。需要注意
   的是这个替换过程是在程序运行时进行的，而不是持久化的，是针对程序的进程实例的。*

## 进程浏览器 Process Explorer & 进程监视器 Process Monitor
   1. Process Explorer refer to [website](https://docs.microsoft.com/zh-cn/sysinternals/downloads/process-explorer)
   2. Process Monitor refer to [website](https://docs.microsoft.com/zh-cn/sysinternals/downloads/procmon)

## 网络协议分析器 Wireshark
   Wireshark是一个开源网络协议分析器，Wireshark既可以捕捉分析来自某个活跃网络的数据，也可以
   分析之前捕捉并保存下来的数据。Downloading refer to [website](https://www.wireshark.org/)


## GCC
