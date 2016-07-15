import os

path = "D:\\tools\\switchhosts\\"
hostpath = "C:\\Windows\\System32\\drivers\\etc\\"

os.chdir(path)

hosts = open(hostpath + "hosts", "r+");
COMMON = open("hosts\\COMMON.hosts").readlines()
hostlist = open("hostlist").readlines()


print("\n************ current host ************")
print(hosts.readline(), end="")
print("*****************************************")
print("select host:\n")
for i in range(0, len(hostlist)):
    print(str(i) + ": " + hostlist[i])

while True:
    num = int(input("select host: "))
    if num >= len(hostlist):
        print("unexpected number")
        continue
    else:
        break

# 修改配置文件
lines = []
lines.append("#" + hostlist[num])
selectedHost = open("hosts\\" + hostlist[num].rstrip() + ".hosts").readlines()
lines.extend(selectedHost)

lines.append("\n#COMMON\n")
lines.extend(COMMON)

print(lines)

hosts.writelines(lines)
hosts.close()

print("\n\ncurrent config: " + hostlist[num])

