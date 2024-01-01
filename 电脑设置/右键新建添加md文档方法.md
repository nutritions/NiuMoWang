## 右键新建md文档

**原直接修改注册表方法已失效**

- 在typora文件夹下添加typora.txt文件

- 修改内容为如下并保存：

  ```
  Windows Registry Editor Version 5.00
  
  [HKEY_CLASSES_ROOT\.md]
  @="Typora.md"
  "Content Type"="text/markdown"
  "PerceivedType"="text"
  
  [HKEY_CLASSES_ROOT\.md\ShellNew]
  "NullFile"=""
  ```

- 修改后缀为.reg（注意关闭隐藏扩展名选项）

- 运行.reg文件

- 资源管理器中重启Windows管理器