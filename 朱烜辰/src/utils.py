import json
import wget
import requests
import tarfile
import bz2
import os
import configparser
import delegator
import distro
import platform
from crontab import CronTab

manager_conf = configparser.ConfigParser()
worker_conf = configparser.ConfigParser()
ctl_conf = configparser.ConfigParser()
# 获取当前目录绝对路径
path = os.getcwd()
# 记录manager的ssl状态
manager_ssl = 0
with open('worker.json', 'r') as rf:
    work = rf.read()
worker_list = eval(work)
rf.close()
crontab = CronTab(user=True)


### Cron管理模块开始
def add_cron(command, time, name):
    job = crontab.new(command=command)
    job.setall(time)
    job.set_comment(name)
    crontab.write_to_user()


def del_cron(name):
    crontab.remove_all(comment=name)
    crontab.write_to_user()
### Cron管理模块结束


### 安装部分开始
# 直接从github获取编译版本
def bin():
    try:
        try:
            res = requests.get("https://api.github.com/repos/tuna/tunasync/releases/latest")
        except:
            res = requests.get("https://api.git.sdut.me/repos/tuna/tunasync/releases/latest")
        dl_url = res.json()['assets'][0]['browser_download_url']
        if dl_url:
            print("Get download URL:" + dl_url)
            try:
                filename = wget.download(dl_url, 'tunasync-linux-bin.tar.bz2')
                print("Download success")
            except:
                dl_url = str(dl_url).replace('github.com', 'github.com.cnpmjs.org')
                print("Try " + dl_url)
                filename = wget.download(dl_url, 'tunasync-linux-bin.tar.bz2')
                print("Download success")
            try:
                archive = tarfile.open(filename, 'r:bz2')
                archive.debug = 1
                for tarinfo in archive:
                    archive.extract(tarinfo, r'.')
                archive.close()
                print("Unzip success")
                try:
                    os.remove(filename)
                except:
                    pass
                delegator.run("chmod +x tunasync tunasynctl")
                delegator.run("mv tunasync tunasynctl /usr/bin")
            except:
                print("Unzip failed")
                try:
                    os.remove(filename)
                except:
                    pass
        else:
            print("Get download URL error")
            return -1
    except:
        print("Get bin error")
        return -1


# Golang的备用安装方法
def go_bin():
    print("Install Go...")
    plat = platform.machine()
    print("当前处理器架构为" + plat)
    if plat == "x86_64":
        mode = 'amd64'
    elif plat == "i386":
        mode = '386'
    elif plat == "aarch64":
        mode = 'arm64'
    elif plat == "arm":
        choice = input("ARM 32位处理器有极大概率无法完成环境配置，是否继续(Y/N)")
        if choice == 'y' or choice == 'Y':
            pass
        else:
            print("终止环境配置...")
            return 0
        mode = 'armv6l'
    else:
        print("Unsupport CPU Type")
        return 0
    url = "https://golang.org/dl/go1.14.4.linux-" + mode + ".tar.gz"
    filename = 'go1.14.4.tar.gz'
    print("Golang download from:" + url)
    wget.download(url, filename)
    print("Start Untar")
    archive = tarfile.open(filename)
    archive.extractall(path='go_bin/')
    archive.close()
    print("Untar Succeed")
    delegator.run("cp -f go_bin/bin/* /usr/bin/")
    print("Install Golang Succeed")


# 安装Golang，使用软件包管理器
def go():
    print("Install Go...")
    like = distro.info()['like']
    print("当前系统为" + like)
    if like == "ubuntu":
        print("配置软件源...")
        cmd = delegator.run("add-apt-repository ppa:longsleep/golang-backports")
        if cmd.return_code == 0:
            print("成功")
        print("更新缓存...")
        cmd = delegator.run("apt update")
        if cmd.return_code == 0:
            print("完成")
        print("安装Golang...")
        cmd = delegator.run("apt install golang-go -y")
        if cmd.return_code == 0:
            print("安装完成")
        else:
            print("尝试使用二进制文件方式安装Golang...")
            go_bin()
    elif like.find("rhel") >= 0:
        print("安装epel...")
        cmd = delegator.run("yum install epel-release -y")
        if cmd.return_code == 0:
            print("成功")
        print("安装Golang...")
        cmd = delegator.run("yum install golang -y")
        if cmd.return_code == 0:
            print("安装完成")
    else:
        print("暂不支持的发行版...\n尝试使用二进制文件方式安装Golang...")
        go_bin()
    print("换用国内镜像源")
    delegator.run("go env -w GO111MODULE=on")
    delegator.run("go env -w GOPROXY=https://goproxy.cn,direct")


# 安装git make
def dep():
    go()
    like = distro.info()['like']
    if like == "ubuntu":
        print("更新缓存...")
        cmd = delegator.run("apt update")
        if cmd.return_code == 0:
            print("完成")
        print("安装 git make...")
        cmd = delegator.run("apt install -y git make")
        if cmd.return_code == 0:
            print("安装完成")
    elif like.find("rhel") >= 0:
        print("安装 git make...")
        cmd = delegator.run("yum install git make -y")
        if cmd.return_code == 0:
            print("安装完成")
    else:
        print("暂不支持的发行版，请手动安装git make")
        # return 0


# 编译tunasync并将二进制文件复制到/usr/bin
def build():
    dep()
    print("克隆项目")
    try:
        os.remove("tunasync")
    except:
        pass
    cmd = delegator.run("git clone https://github.com/tuna/tunasync.git")
    if cmd.return_code == 0:
        print("完成")
    print("开始编译")
    cmd = delegator.run("cd tunasync && make")
    if cmd.return_code == 0:
        print("编译完成")
    print("验证结果...")
    code = 1
    cmd = delegator.run("cd tunasync/build && ./tunasync -v")
    print(cmd.out)
    if cmd.return_code != 0:
        code = 0
    cmd = delegator.run("cd tunasync/build && ./tunasynctl -v")
    print(cmd.out)
    if cmd.return_code != 0:
        code = 0
    if code == 1:
        delegator.run("cp -f tunasync/build/* /usr/bin")
        print("验证完成")
    else:
        print("失败")
        return 0
### 安装部分结束


### 基础设置部分开始
# ssl设置模块
def ssl(mode, name = ''):
    global manager_ssl
    if mode == 0:
        type = input("是否为manager设置SSL(Y/N)")
        manager_conf['server']['ssl_cert'] = '\"\"'
        manager_conf['server']['ssl_key'] = '\"\"'
        if type == 'Y' or type == 'y':
            confirm = input("确认证书文件在ssl/manager目录下，并分别命名为ssl.pem ssl.key(Y/N)")
            if confirm == 'Y' or confirm == 'y':
                manager_conf['server']['ssl_cert'] = "\"" + path + '/ssl/manager/ssl.pem\"'
                manager_conf['server']['ssl_key'] = "\"" + path + '/ssl/manager/ssl.key\"'
                print("同时，别忘了将ca_cert也放置在ssl/manager目录下，并命名为ca.cert")
                manager_ssl = 1
            else:
                print("请放置好文件后重新配置")
                return -1
        else:
            return 0
    else:
        worker_conf['server']['ssl_cert'] = '\"\"'
        worker_conf['server']['ssl_key'] = '\"\"'
        if manager_ssl:
            worker_conf['manager']['ca_cert'] = "\"" + path + '/ssl/manager/ca.cert\"'
        type = input("是否为worker设置SSL(Y/N)")
        if type == 'Y' or type == 'y':
            confirm = input("确认证书文件在ssl/worker目录下，并分别命名为" + name + "-ssl.pem " + name + "-ssl.key(Y/N)")
            if confirm == 'Y' or confirm == 'y':
                worker_conf['server']['ssl_cert'] = "\"" + path + '/ssl/worker/' + name + '-ssl.pem\"'
                worker_conf['server']['ssl_key'] = "\"" + path + '/ssl/worker/' + name + '-ssl.key\"'
            else:
                print("请放置好文件后重新配置")
                return -1
        else:
            return 0


# db设置部分，暂不允许修改
def db():
    manager_conf['files'] = {}
    # db_type = input("数据库类型：(bolt)")
    # if db_type:
    #     pass
    # else:
    db_type = 'bolt'
    manager_conf['files']['db_type'] = "\"" + db_type + "\""
    # db_file = input("数据库文件位置(db/manager.db)")
    # if db_file:
    #     pass
    # else:
    db_file = path + '/db/manager.db'
    manager_conf['files']['db_file'] = "\"" + db_file + "\""
    # ca_cert = input("ca cert()")
    # if db_type:
    #     pass
    # else:
    ca_cert = ''
    manager_conf['files']['ca_cert'] = "\"" + ca_cert + "\""


# manager配置文件生成部分
def init_manager():
    debug = input("是否开启Debug(Y/N)")
    if debug == 'Y' or debug == 'y':
        manager_conf['DEFAULT'] = {'debug': 'true'}
    else:
        manager_conf['DEFAULT'] = {'debug': 'false'}
    manager_conf['server'] = {}
    bind_ip = input("绑定IP：(127.0.0.1)")
    if bind_ip:
        pass
    else:
        bind_ip = '127.0.0.1'
    manager_conf['server']['addr'] = "\"" + bind_ip + "\""
    bind_port = input("绑定端口：(14242)")
    if bind_port:
        pass
    else:
        bind_port = str(14242)
    manager_conf['server']['port'] = bind_port
    worker_list['manager_save'] = {'url': bind_ip + ':' + bind_port}
    with open('worker.json', 'w') as cf:
        cf.write(json.dumps(worker_list))
    cf.close()
    ssl(0)
    db()
    try:
        os.mkdir('/etc/tunasync')
    except:
        pass
    with open('/etc/tunasync/manager.conf', 'w') as mf:
        manager_conf.write(mf)
    mf.close()
    ctl_conf = {"manager_addr": "\"" + bind_ip + "\"", "manager_port": bind_port}
    if manager_ssl:
        ctl_conf["ca_cert"] = "\"" + path + '/ssl/manager/ca.cert\"'
    with open('/etc/tunasync/ctl.conf', 'w') as cf:
        manager_conf.write(cf)
    cf.close()


# worker配置文件生成部分
def add_worker():
    name = input("输入Worker名：(不能重复)")
    worker_conf['global'] = {'name': "\"" + name + "\"", "log_dir": "\"logs/{{.Name}}\""}
    dir = input("输入放置镜像文件的目录：(以/结尾)")
    worker_conf['global']['mirror_dir'] = "\"" + dir + "\""
    con = input("输入线程数：(10)")
    if con:
        pass
    else:
        con = str(10)
    worker_conf['global']['concurrent'] = con
    interval = input("输入同步的周期(分钟)：(1)")
    if interval:
        pass
    else:
        interval = str(1)
    worker_conf['global']['interval'] = interval
    api = input("输入manager地址(http://127.0.0.1:14242)：")
    if api:
        pass
    else:
        api = "http://127.0.0.1:14242"
    token = input("输入token：")
    worker_conf['manager'] = {"api_base": "\"" + api + "\"", "token": "\"" + token + "\""}
    cgroup = input("是否开启cgroup(Y/N)")
    if cgroup == 'Y' or cgroup == 'y':
        base_path = input("输入base_path：")
        group = input("输入group：")
        worker_conf['cgroup'] = {'enable': 'true', 'base_path': "\"" + base_path + "\"", 'group': "\"" + group + "\""}
    else:
        base_path = ""
        group = ""
        worker_conf['cgroup'] = {'enable': 'false', 'base_path': "\"" + base_path + "\"", 'group': "\"" + group + "\""}
    hostname = input("输入主机名：(localhost)")
    if hostname:
        pass
    else:
        hostname = 'localhost'
    # try:
    #     ip = requests.get('https://api-ipv4.ip.sb/ip').text[:-1]
    # except:
    #     ip = '0.0.0.0'
    ip = '127.0.0.1'
    listen_addr = input("绑定IP：(" + ip + ")")
    if listen_addr:
        pass
    else:
        listen_addr = ip
    listen_port = input("绑定端口：(6000)(端口不能重复)")
    if listen_port:
        pass
    else:
        listen_port = str(6000)
    worker_conf['server'] = {'hostname': "\"" + hostname + "\"", 'listen_addr': "\"" + listen_addr + "\"", 'listen_port': listen_port}
    ssl(1)
    mirror_name = input("输入mirror名称：")
    provider = input("输入同步方式：")
    upstream = input("输入同步源：")
    command = ''
    if provider == "command":
        command = '\"' + input("输入同步脚本位置(绝对路径)：") + '\"'
    elif provider == "rsync":
        pass
        # 暂不编写
        # rsync_options = [" "]
    else:
        pass
    c = input("是否启用ipv6?(Y/N)")
    if c == 'Y' or c == 'y':
        use_ipv6 = 'true'
    else:
        use_ipv6 = 'false'
    memory_limit = '\"' + input("内存限制(不填不限制)：") + '\"'
    # exclude_file
    worker_conf['[mirrors]'] = {"name": '\"' + mirror_name + '\"', "provider": '\"' + provider + '\"', "upstream": '\"' + upstream + '\"', "use_ipv6": use_ipv6}
    if command:
        worker_conf['[mirrors]']['command'] = command
    if memory_limit:
        worker_conf['[mirrors]']['memory_limit'] = memory_limit
    with open('/etc/tunasync/worker-' + name + '.conf', 'w') as wf:
        worker_conf.write(wf)
    wf.close()
    worker_list[name] = {mirror_name: dir + mirror_name}
    with open('worker.json', 'w') as cf:
        cf.write(json.dumps(worker_list))
    cf.close()
    return name


# 设置systemd
def systemd():
    print("终止Manager...")
    cmd = delegator.run("systemctl stop tunasync_manger")
    print(cmd.out)
    print("终止Worker...")
    cmd = delegator.run("systemctl stop tunasync_worker")
    print(cmd.out)
    # 将预先写好的文件复制到/etc/systemd/system/
    delegator.run("cp -f systemd/tunasync_manager.service /etc/systemd/system/")
    delegator.run("cp -f systemd/tunasync_worker@.service /etc/systemd/system/")
    print("重载...")
    c = delegator.run("systemctl daemon-reload")
    if c.return_code == 0:
        print("成功")
### 基础设置部分结束


### systemd管理部分开始
def systemd_control(action, mode, name = ''):
    if mode == 'manager':
        return delegator.run("systemctl " + action + " tunasync_manager").out
    elif mode == 'worker':
        return delegator.run("systemctl " + action + " tunasync_worker@" + name).out
### systemd管理部分结束


### worker管理开始
# 删除worker
def del_worker(name):
    print("结束进程...")
    print(delegator.run("systemctl stop tunasync_worker@" + name).out)
    print(delegator.run("systemctl disable tunasync_worker@" + name).out)
    print("删除文件...")
    for mirror in worker_list[name]:
        print(delegator.run("rm -rf " + worker_list[name][mirror] + ' /etc/tunasync/worker-' + name + '.conf').out)
        try:
            # 删除cron
            del_cron(name + '_size')
            del_cron(name + '_retry')
        except:
            pass
    print("删除worker...")
    delegator.run("tunasynctl rm-worker -w " + name)
    worker_list.pop(name)
    with open('worker.json', 'w') as df:
        df.write(json.dumps(worker_list))
    df.close()


def get_list():
    jobs = requests.get("http://" + worker_list['manager_save']['url'] + "/jobs").text
    return json.loads(jobs)


# 添加cron
def enable_auto_refresh_size(name, time_m):
    for mirror in worker_list[name]:
        command = "tunasynctl set-size -w " + name + " " + mirror + " `du -sh " + worker_list[name][mirror] + " | awk '{print $1}'`"
        time = "*/" + str(time_m) + " * * * *"
        add_cron(command, time, name + '_size')


def enable_auto_retry(name, time_m):
    command = "/usr/bin/python3 " + path + "/retry.py " + path + "/sh/retry.py " + name
    time = "*/" + str(time_m) + " * * * *"
    add_cron(command, time, name + '_retry')
### worker管理结束
