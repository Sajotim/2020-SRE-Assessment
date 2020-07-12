### 选择的题目 ###
选择的是题目一

### 运行的环境 ###
必须有 python3、pip、systemd、cron

对于tunasync的安装我提供了两种方法
#### 1.预编译文件方式安装 ####
由于官方仅提供x86_64的二进制编译文件，故该方法仅支持x86_64架构的处理器
#### 2.编译方式 ####
因为需要安装golang、git、make，安装默认使用包管理器，故

在CentOS7+/Ubuntu18.04+环境上能较好的完成，其他系统/架构未经测试

在x86_64的CentOS7、Ubuntu18.04和aarch64的CentOS7上均完成了测试

### 使用方法 ###
`pip3 install -r requirements.txt` 先安装依赖

后执行main.py，先选择初始化，将安装tunasync至/usr/bin，然后根据向导设置，之后会启动服务并设置自启

使用添加worker来添加镜像（每个镜像不同worker），按照向导设置完后将启动并设置自启，然后需要设置更新镜像大小和检测错误的周期，通过添加cron实现

可能需要手动启动crond `systemctl enable crond` `systemctl start crond`

此外，还支持查看镜像同步状态、当前镜像大小、上次同步用时、删除worker和查看进程状态

### 其他 ###
仅在aarch64+CentOS7环境下对rsync方式的多任务同步进行了测试，其他环境或设置诸如ssl、command方式同步未经测试，故无法预计运行效果
