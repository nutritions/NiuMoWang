# 编译原理lab0

> 如何创建一个新的 git 分支？如何进行分支切换？如何删除一个分支？什么时候可以安全的删除一个分支？

**以dev分支为例**

创建新的git分支：git branch dev

分支切换：git checkout dev或者git switch dev

删除分支：git branch -d dev

安全删除分支：合并完成之后



> 如何撤销保存在暂存区的修改？如何撤销已经提交的修改？

- 保存在暂存区的修改：   先git reset HEAD $<file>$,再git checkout -- file

- 已经提交的修改：          git reset

  

> 如何从远程仓库抓取更新？

git fetch和git pull



> 解释 git init 的作用？

在当前目录下创建一个.git子目录作为git仓库，并初始化该仓库



> 解释 git fetch 和 git pull 的区别

git fetch只是抓取远程仓库内容，不自动合并到本地分支中

而git pull是抓取远程仓库内容到本地并合并