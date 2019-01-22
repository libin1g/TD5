# Quickidx
## 1. MD
- bold character like this: **md**
- head as following:
# h1
## h2
###### h6


- list, include unordered list/ordered list 
```
ul 无序列表 以-或*开头
ol 有序列表 以1. 2. ... N开头
```

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


## 2. Vi's language composed of three simple concepts "Count + Operator + Motion"
**Count** si optional and often overlooked: 
  A computer doesn't mind mindless repetition, but you should!
  Why hit a button *thirty* times when you can just say "30"?
**Operator** is one of a few familiar commands:
```
 _____                         _____                          _____
|| c ||                       || d ||                        || y ||
||___||  change               ||___||  delete                ||___||  yank
|/___\|                       |/___\|                        |/___\|
```
**Motion** is the really clever bit.  Bill Joy realized that text is intrinsically structured into 
```
                      words
                      lines,
                    sentences,
                    paragraphs,
                      blocks,
                       etc.
```
If this is how people percieve text, then so should their editor! Just about anything that moves the cursor counts as a *motion*:
```
                     marks,
                regular expressions,
                  h j k l of course,
                 and so much more!
```

---
**motion**
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

**Text Object motions**
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
---

**其他操作**
1. @: 重复执行上一次Ex command
2. .  重复执行上一次normal command
2. After the 'expandtab' option is set, all the new tab characters entered will be changed to spaces. This will not affect the existing tab characters. To change all the existing tab characters to match the current tab settings, use: `retab` 

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




## 3. Fuzzy open file in buffer
There is a super sweet feature in Vim whereby you can fuzzy find your files using **/*, e.g.:
`:vs **/*<partial file name><Tab>`
This will search the current directory and all directories below it for filenames containing your partial search. This can be used with ` :e, :sp, :vsp `.

If there are multiple possible matches, you can see the options you have available by setting this in your ` .vimrc `:
Show file options above the command line
`set wildmenu`
For more information, run ` :h 'wildmenu' `.

You’ll probably also want to exclude certain file types and directories from this fuzzy finding, so you can stick these in your ` .vimrc `:

Don't offer to open certain files/directories
```
set wildignore+=*.bmp,*.gif,*.ico,*.jpg,*.png,*.ico
set wildignore+=*.pdf,*.psd
set wildignore+=node_modules/*,bower_components/*
```
Now we’re at a point where I don’t need to look through any directories: if I know I want to open my _components.buttons.scss file I just need to do:

`:vs **/*butto<Tab>`

Vim will go off and find this for me, and if there are multiple possible matches it will also neatly display them all for me.

## 4. gf
When your cursor is over a path to a different file gf (go to file) will open the file but in the same window.

Add this to your ~/.vimrc:
" `gf` opens file under cursor in a new vertical split
` nnoremap gf :vertical wincmd f<CR> `
When your cursor is over a path to a different file, hitting `gf` (go to file) will open it in a new split window. 
This helps you quickly explore the project based on its depedencies.


## 5. Do something for each item in your list - argument list
If you want to perform the search in a project tree (a directory/folder), you can use vim's argument list command.
Simply open vim and then use the :args command to populate the argument list. You can pass in multiple filenames or even globs.
For example: ` :args **/*.cpp `
the command will recursively search the current directory for cpp files. Notice that this is also like opening vim with vim **/*.cpp
You can even use the shell's find command to get a list of all files in the current directory by running:
```
:args `find ./ -type cpp` 
```
You can view the current args list by running :args by itself. If you want to add or delete files from the list, you can use the :argadd or the :argdelete commands respectively.

Once you're happy with the list, now you can use vim's powerful :argdo command which runs a command for every file in the argument list :argdo %s/search/replace/gc
Here are some tips for searching (based on some of the comments):

* Use a word boundary if you wanted to search for "foo" but not "foo_bar". Use the \< and \> constructs around the search pattern like so: :argdo %s/\<search\>/foobar/g
* Use a /c search flag if you want Vim to ask for confirmation before replacing a search term.
* Use a /e search flag if you want to skip the "pattern not found" errors.
* You can also choose to save the file after performing the search: :argdo %s/search/replace/g | update. Here, :update is used because it will only save the file if it has changed.

## 6. Do something for each item in your list - buffer list
Open buffers
If you already have buffers open you want to do the search/replace on, you can use :bufdo, which runs a command for every file in your buffer list (:ls).

The command is very similar to `:argdo:  :bufdo %s/search/replace/g `

Similar to ` :argdo ` and ` :bufdo `, there is ` :windo ` and ` :tabdo ` that act on windows and tabs respectively. They are less often used but still useful to know.



## 7. vimgrep

Let's say we have a simple project structure like this:
```
cwd-----info
  |       +---age.txt
  +-----greeting.txt
```
age.txt looks like:
  Sam's age is 25.
greeting.txt looks like:
  Hello, may name is Sam, and Sam is my name.

Let's say we want to replace all occurences of Sam with Bob. Here's what we would do:

1. Set working directory

Make sure Vim's current working directory is the root of the project (won't show you how to do this here).

2. Find files that contain 'Sam'

Use Vim's vimgrep command to search for all occurences of Sam within the project (note: the **/* searches in all files recursively)

` :vimgrep /Sam/gj **/*  `
This will populate the quickfix list with all instances of Sam. 
If you want to view the quickfix list, you can use the Vim command :copen 

3. Substitute within all files that contain 'Sam'

Now we want to run Vim's substitute command inside every file in the quickfix list. We can do this using the :cfdo {cmd} command which executes {cmd} in each file in the quickfix list. The specific {cmd} we want to use is substitute or s for short. The full line would look like:

` :cfdo %s/Sam/Bob/g  `
You can add the c flag to confirm all replacements if you like:

` :cfdo %s/Sam/Bob/gc `
Save all files

` :cfdo update `

On the other hand, you can do substitute in one word:
` :cfdo %s/Sam/Bob/gc | update `
and no confirm question, you can do:
` :cfdo %s/Sam/Bob/g | update `

* ` :cfdo ` tells vim to do something across all file items in our Quickfix list.
* ` %s/Sam/Bob/ ` tells vim to look at every line(%) and substitute all instances.
* ` gc ` tells vim to do this globally on each line and asks us(confirm)
* ` | update ` tells vim to do update the Quickfix list after making changes

Vim sometimes still amazes me. Editing a Django JSON fixture or some other uglily formatted JSON file, just say:

## Format json string
` :%!python -m json.tool `




