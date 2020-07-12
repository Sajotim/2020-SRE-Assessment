from utils import bin, build, init_manager, add_worker, systemd,  worker_list, del_worker, get_list, systemd_control, enable_auto_refresh_size, enable_auto_retry


def menu():
    while 1:
        mode = int(input("欢迎使用tunasync管理系统，请选择功能：(首次需进行初始化)\n1.初始化\n2.新增一个Worker\n3.管理Workers\n4.查看Manager状态\n5.退出\n"))
        if mode == 1:
            mode2 = int(input("1.通过预编译文件方式(仅支持x86_64架构)\n2.通过编译方式\n"))
            try:
                if mode2 == 1:
                    bin()
                else:
                    build()
            except:
                print("安装tunasync时出错...")
            try:
                print("开始设置manager...")
                init_manager()
                print("开始设置服务...")
                systemd()
                print("启动manager...")
                systemd_control('start', 'manager')
                print("设置manager自启...")
                systemd_control('enable', 'manager')
            except:
                print("设置时出错...")
        elif mode == 2:
            name = add_worker()
            print("启动worker...")
            systemd_control('start', 'worker', name)
            print("设置worker自启...")
            systemd_control('enable', 'worker', name)
            ch1 = input("设置自动更新大小的时间间隔(min)(1)：")
            if ch1:
                pass
            else:
                ch1 = 1
            enable_auto_retry(name, ch1)
            ch2 = input("设置自动检测同步错误并重试的时间间隔(min)(1)：")
            if ch2:
                pass
            else:
                ch2 = 1
            enable_auto_refresh_size(name, ch2)
        elif mode == 3:
            print("序号\t\t名称\t\t状态\t\t镜像名\t\t大小\t\t上次同步用时(s)")
            i = 0
            list = get_list()
            for worker in worker_list:
                for mirror in worker_list[worker]:
                    if worker == 'manager_save':
                        pass
                    else:
                        pass_time = ''
                        size = ''
                        status = ''
                        for job in list:
                            if job['name'] == mirror:
                                end_time = job['last_ended_ts']
                                start_time = job['last_started_ts']
                                pass_time = str(end_time - start_time)
                                size = job['size']
                                status = job['status']
                                print(str(i) + '\t\t' + worker + '\t\t' + status + '\t\t' + mirror + '\t\t' + size + '\t\t' + pass_time)
                    i += 1
            id = int(input("输入需要操作的worker序号："))
            i = 0
            name = ''
            for worker in worker_list:
                if i == id:
                    name = worker
                i += 1
            if name == '':
                print("序号不存在")
                break
            mode2 = int(input("请选择操作：\n1.获取进程状态\n2.删除worker\n3.返回\n"))
            if mode2 == 1:
                print(systemd_control('status', 'worker', name))
            elif mode2 == 2:
                del_worker(name)
            else:
                pass
        elif mode == 4:
            print(systemd_control('status', 'manager'))
        else:
            return 0


if __name__ == '__main__':
    menu()
