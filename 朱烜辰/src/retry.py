import json
import delegator
import sys


name = sys.argv[1]
list = json.loads(delegator.run("tunasynctl list --all").out)
for worker in list:
    if worker['name'] == name and worker['status'] == 'failed':
        print(name + "执行失败，开始重试...")
        delegator.run("systemctl restart tunasync_worker@" + name)
