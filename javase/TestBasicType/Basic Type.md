# 基本数据类型

| basic type | size of | range    |description|
| :-:        | :-      | :-:      |:-         |
| byte       | 1byte   | -128~127 |byte with signed |
| short      | 2byte   |          |byte with signed |
| int        | 4byte   |          |byte with signed |
| long       | 8byte   |          |byte with signed |
| char       | 2byte   |          |byte with unsigned |
| float      | 4byte   |          |byte with signed |
| double     | 8byte   |          |byte with signed |
| boolean    | 1bit    |          |bit|



```
//*隐式类型转换(编译器隐式类型转换原则：目标类型能表示源类型变量)*
        char --.
                \
                 v
byte -> short -> int -> long
                 |  \    |
                 |   \   |
                 |    .  |
                 v     v v
             float -> double

```

