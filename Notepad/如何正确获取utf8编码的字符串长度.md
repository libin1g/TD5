# **如何正确获取utf8编码的字符串长度** 

## 先说正确获取utf8编码的字符串长度方法，直接上代码：

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

/**
 * BytesOfCharacter 根据UTF-8字符数据的首字节返回该字符数据字节数
 *
 * NOTE:
 *   Unicode俗称统一码、万国码、单一码,是计算机科学领域里的一项业界标准,包括字符集、编码方案。Unicode是为了解决
 * 传统的字符编码方案的局限而产生的，它为每种语言中的每个字符设定了统一并且唯一的数值，这个数值通常用十六进制表示,
 * 常称为CodePoint, Unicode码。这个CodePoint数值在计算机中的具体存储格式有多种, 称为Unicode Transformation Format, 
 * 即Unicode转换格式，例如UTF-8,UTF-16,UTF-32等。(*按照某种转换格式转换的数值数据就称为字符数据*)
 *
 * UTF-8转换格式对字符的Unicode码进行变长转换, 用n(1<=n<=6)个字节转换Unicode码, 兼容性强，计算机存储效率高, 总结起来只有两条规则:
 *    (1) 字节数n=1, 字节的第一位设为0，则后面7位为这个字符的unicode码, 这种unicode码对应的字符常称为单字节字符。
 *    (2) 相对于单字节字符，其他的字符常称为多字节字符。多字节字符字节数n>1, 第一个字节的前n位都设为1，第n+1位设为0，
 *        后面字节的前两位一律设为10，其他没有提及的二进制位整体为这个字符的unicode码。
 * 所以UTF-8的变长转换可进一步归纳如下表： 
 *    1字节 0xxxxxxx 
 *    2字节 110xxxxx 10xxxxxx 
 *    3字节 1110xxxx 10xxxxxx 10xxxxxx 
 *    4字节 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 
 *    5字节 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
 *    6字节 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
 * 也因此UTF-8中能够用来表示字符编码的实际位数最多有31位，即上表中x所表示的位。
 * 除去那些控制位（每字节开头的10等），这些x表示的位与unicode码是一一相应的，位高低顺序也同样。
 * 字节数n=1，一个字节的7个二进制位就能表示0~127个数值, 如此，UTF8编码就兼容了ANSI的128个标准ASCII编码。 
 *
 *
 * 依据此规则，能够非常方便地根据字符数据的首字节firstByteOfCharacter判断出该字符数据的长度，代码例如以下:
 *
 */
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

**应用举例** 
- 参阅[一个完整的例子](https://github.com/libin1g/TD5/blob/master/CountOfUtf8Characters/CountOfUtf8Characters.cpp)

## 再说说计算机中的字符数据
1. 计算机加工的对象是数据信息，而指挥计算机操作的是控制信息，因此计算机内部的信息可以划分如下：
```

                 +- 指令
                 |
     +- 控制信息 +
     |           |
     |           +- 控制字
     |
信息 +                       +- 定点数
     |                       |
     |           +- 数值数据 +
     |           |           |
     |           |           +- 浮点数
     +- 数据信息 +           
                 |             +- 字符数据 (可按照某种转换方案转换的数值数据就称为字符数据)
                 |             |
                 +- 非数值数据 +
                               |
                               +- 逻辑数据

```
2. 计算机只能处理二进制数据，也就是只能处理数值数据，所以字符数据和逻辑数据在计算机中归根结底必须转化为数值数据存储。 
   这里重点说计算机能处理的字符数据: 字符集及建立在字符集上的编码方案（例如Unicode码）就是提供一套字符和数值相互转换的方案， 
   方案为字符指定了对应的数值（常称为CodePoint）。 这个CodePoint数值在计算机中的具体存储格式可以有多种。

3. 万国码(Unicode)字符转换方案的Codepoint数值常见的转换格式有UTF-8， UTF-16和UTF-32。
    - UTF-8对字符的Unicode码进行变长转换, UTF-8需要1~6个8位长的码元来表示。也因此UTF-8更好的兼容了ANSI ASCII码，标准ASCII码仍然用一个字节存储, 计算机存储效率高。UTF-8应用非常广泛。
    - UTF-16对字符的Unicode码也进行变长转换，UTF-16需要1个或者2个16位长的码元来表示，因此这也是一个变长转换。
      UTF-16比起UTF-8，好处在于大部分字符都以固定长度的字节 (2字节) 储存，但总的来说存储效率较UTF-8低，兼容性差，对于标准ASCII码上，UTF-16统一扩大原一个字节至他的固定长度（扩展时高位用0补齐）。
    - UTF-32对字符的Unicode码进行固定长度转换，统一定为4字节。因为UTF-32对每个字符都使用4字节，就空间而言，是非常没有效率的。目前使用并不广泛。
    - 综上所述，UTF-8兼容ANSI ASCII码，UTF-8对字符的Unicde码的变长转换规则使得建立在标准ASCII码字符数据上的字符数据处理方法(函数)同样奏效。
      而UTF-16，UTF-32都需要2个字节甚至更多字节数来存储字符数据, 尤其是他们扩大原一个字节的ASCII码字符数据至他的固定长度（扩展时高位用0补齐），
      使得原建立在标准ASCII码字符数据上的字符数据处理方法(函数)同样不能奏效。因此我们把这种字符数据对应的称为"宽字符"，也必须要使用一套针对"宽字符"的字符数据处理方法(函数)。 

     ```
     * 目前操作系统普遍已经采用了Unicode字符转换方案，但不同平台缺省采用的Unicode Transformation Format不一样。 
     * linux平台默认采用UTF-8， windows平台默认采用UTF-16。UTF-16不兼容ANSI ASCII，必须使用"宽字符"字符数据处理方法(函数)。
     * 另外，windows平台还基于兼容ANSI ASCII的考虑，建立了一套基于代码页的MBCS方案, MBCS引入代码页CodePage来扩展ASCII码
     * 以支持127个标准ASCII字符以外的字符。MBCS字符数据对于标准ASCII字符仍然采用一个字节存储，对于汉字等采用2个字节存储，
     * 其中高字节作为前导字节设置有标志位，就像UTF-8一样，从而兼容ASCII码，使得建立在标准ASCII码字符数据上的字符数据
     * 处理方法(函数)同样奏效。
     ```

4. 美国信息互换标准代码方案的Codepoint数值转换格式即ANSI ASCII码表。
   常说的ASCII码包括标准ASCII码和扩展ASCII码。 ASCII总共定义了256个字符(即2^8个)，从0-32位为控制字符(ASCII control characters)，
   从33-127位为可打印字符(ASCII printable characters)。从0-127是标准的ASCII编码，从128-255是扩展的ASCII编码。
