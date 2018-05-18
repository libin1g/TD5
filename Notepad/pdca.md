# PDCA 
## TODO
1. ~~ACCESS增加Mainline Delegation点击后，车站弹框提示~~
2. ~~ACCESS模块在OCC增加弹框提示，提示当前失联车站列表~~
3. ~~REPORT之O&M文档更新~~
4. 修改TFS遗留bug
5. 用户可输入文本框文本校验排查
6. 检视模块代码，排查多点读/写IStringList是否存在内存泄漏并修改
7. 数据库存储过程生成报表逻辑重构


## BRAIN STORM
- rgb等颜色值选中后ToggleColoBkg切入切出应用该值背景色，附加ClearColoBkg/AddColoBkg函数，以及颜色选择器ColoTable


***
**实用骚操作**
1. @: 重复执行上一次Ex command
2. .  重复执行上一次normal command

**实用骚操作motion**
1. w e b 以word为单位移动，大写时认为一个空格间隔就是一个word，所以比小写移动快
2. 0  移动到当前行首  $ 移动到当前行尾
   ^  移动到当前行首的第一个word    g_ 移动到当前行最后一个word
3. (  以sentence为单位 反向移动
   )  以sentence为单位 正向移动
   {  以paragraph为单位 反向移动
   }  以paragraph为单位 正向移动
4. 在空白行敲viw可以迅速选择临近的空白字符
   在空白行敲dip可以迅速删除临近的空白行
5. 缩进时候使用 >8j   >}   <ap   =i} ==会很快

**实用骚操作Text Object motions/operation**
1. viw ---> visual inner word
   vaw ---> visual a/an word
   vi{或者vi} ---> visual inner a couple of {}
   vi(或者vi) ---> visual inner a couple of ()
   vis ---> visual inner sentence
   vas ---> visual a/an sentence

2. diw ---> delete inner word
   daw ---> delete a/an word
   dap ---> delete a/an paragraph
   dip ---> delete inner paragraph
   di{或者di} ---> delete inner a couple of {}
   da{或者di} ---> delete a/an a couple of {}

3. ciw ---> change inner word
   caw ---> change a/an word
   cap ---> change a/an paragraph
   cis ---> change inner sentences
   cas ---> change a/an sentences


**窗口操作**
1.	Ctrl-w K（把当前窗口移到最上边）/ k (激活当前窗口上面的窗口)
2.	Ctrl-w H（把当前窗口移到最左边）/ h (激活)
3.	Ctrl-w J（把当前窗口移到最下边）
4.	Ctrl-w L（把当前窗口移到最右边）
5.  滚动绑定: 两个窗口分别:set scb! 可以实现两个窗口同步滚动
6. Ctrl-w w  激活下一窗口, 窗口之间循环切换


**diff操作**
1. [c 移动到下一差异处
2. ]c 移动到上一差异处
3. dp 推送当前窗口当前差异处推送到另一文件以消除文件差异 diff put
4. do 拉亲取另一文件窗口当前差异处到本文件窗口以消除文件差异 diff get(不用dg因为dg已另作他用)
5. 如果希望手工修改某一行，可以使用通常的vim操作, 放弃最近一次修改用u。
6. 如在修改一个或两个文件之后，vimdiff会试图自动来重新比较文件，来实时反映比较结果。
7. 如果自动重新比较处理失败或存疑，需要手工(:diffupdate)来刷新比较结果.
8. :qa quit all
9. :wa write all
10. :wqa write, then quit all
11. :qa! force to quit all

**md**
- head
# h1
## h2
###### h6


- list
ul 无序列表 以-或*开头
ol 有序列表 以1. 2. ... N开头


- table
由|分割表格各单元格, 以:-:标记居左居中居右。

|Index|name|price|update date|
|:-:|:-|-:|:-:|
|1|apple|2.00|2018-05-08 10:49:00|
|2|phone|7000|2017-05-08 12:59:00|


- 特殊标记
1. 引用文字 以>开头，表示此段落为引用文字
2. 引用网络地址 [描述](网络url)
3. 引用图片 ![描述](图片url)
4. 字体黑体 以双星号包围要黑体显示的文字  **这字是黑体**
5. 字体斜体 以单星号包围要斜体显示的文字  *这里是斜体*
6. 横线分割 三个以上的*或者-独立一行
7. 标记代码 两个`包围要目标代码
8. 标记代码段 用三个```包围目标代码段

```
size_t LengthOfString(const char* pstr)
{
    size_t BytesOfCharacter(char firstByteOfCharacter);
    size_t nCount = 0;
    for (nCount = 0; *pstr; nCount++)
    {
        pstr += BytesOfCharacter(*pstr);
    }
    return nCount;
}

size_t BytesOfCharacter(char firstByteOfCharacter)
{
    size_t nCount = 0;
    for (nCount = 0; firstByteOfCharacter & 0x80; nCount++)
    {
        firstByteOfCharacter <<= 1; 
    }
    if (nCount > 6 || nCount < 2 )
    {
        nCount = 1;
    }
    return nCount;
}
```
