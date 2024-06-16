# README

这是一个PBS作业示例，包括：

- 一个计算素数表的C++程序（prime.cpp），耗时大约一分钟（可以修改素数表上限以改变耗时）
- 配套的编译脚本 Makefile
- PBS作业脚本 job.pbs

使用方法如下：

第一步，进入当前目录，编译程序
```bash
make
```

第二步，使用`qsub`命令提交PBS作业
```bash
qsub job.pbs
```

在提交PBS作业后会返回一个作业号，例如24238.mu01。（下面均以此为例）

可以使用`qstat`查询作业状态，状态可能是:

- `Q`：等待执行
- `R`：正在执行
- `C`：正在退出

注意，程序执行大约耗时一分钟，如果程序运行完成，`qstat`将无法查询到作业信息。


根据PBS脚本中的配置，在作业完成后：

- 在当前目录下会生成一个`prime.o24328`文件，其中记录了当前作业中所有的标准输出和错误输出。脚本在计算命令前后各调用了一次`date`，可以据此估计程序的耗时。
- 计算命令是在使用`qsub`提交作业时的目录下执行的，程序的输出文件（`primes_output_*.txt`）默认也会存放在这里。
