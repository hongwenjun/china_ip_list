### 中国大陆白名单数据 和 转换工具
```
### linux 更新 china_ip_list 转换成Windows使用的 add.txt 和 del.txt
git clone https://github.com/hongwenjun/china_ip_list.git
cd china_ip_list && ./auto_add_routes.sh

### Windows 下cmroute.dll 秒载/秒删 china_ip_list 路由表
rundll32.exe cmroute.dll,SetRoutes /STATIC_FILE_NAME add.txt /DONT_REQUIRE_URL /IPHLPAPI_ACCESS_DENIED_OK
```

###  auto_add_routes.sh  源码
```
#!/bin/bash

# auto_add_routes.sh

update(){
    wget -O china_ip_list.txt  https://raw.githubusercontent.com/17mon/china_ip_list/master/china_ip_list.txt
}

update
echo
echo -e "Please wait a moment..."

#  Input:  27.54.192.0/18
#  Out:    add 27.54.192.0 mask 255.255.192.0 default METRIC default IF default

for i in `cat china_ip_list.txt`
do
	ip=$(echo $i | awk -F '[/]' '{print $1}')
	len=$(echo $i | awk -F '[/]' '{print $2}')
	
    # mask=$(tools/mask_len2str $(tools/mask_str2len $ip))
    mask=$(tools/mask_len2str $len)
    
	echo "add ${ip} mask ${mask} default METRIC default IF default" >> /tmp/add.txt
done

mv /tmp/add.txt add.txt
cp add.txt  del.txt

sed -i "s/add/delete/g"  del.txt

echo -e "We worked very hard to finish the job."
```
# auto-add-routes

## 介绍
为使用各类全局代理VPN的windows用户提供国内国外IP的分流服务。原理是将国内IP写进系统路由表，路由表以外的IP走VPN代理。

## 文件说明：

add.txt和del.txt为写入和删除时使用的路由表；

routes-up.bat和routes-down.bat为Tunsafe在连接前和断开后调用的写入/删除路由表的批处理文件。通过Tunsafe的PreUp和PostDown命令调用。

cmroute.dll会被上述两个批处理文件调用，作用是秒载/秒删路由表。即使有数千条路由表也能秒载入，秒删除。

## 使用方法

### Wireguard
#### 1. 下载最新版本Tunsafe，建议使用带rc的版本。

#### 2. 开启Tunsafe的Pre/Post命令功能。在"Option"选择"Allow Pre/Post Commands"

#### 3. 下载[route.zip](https://raw.githubusercontent.com/lmc999/auto-add-routes/master/route.zip)解压到Tunsafe安装目录。

#### 4. Wireguard客户端配置文件加入PreUp,Postdown命令调用批处理文件。

假设你的Tunsafe安装在D盘abc目录下,你需要在客户端配置文件添加以下两条命令

PreUp = start D:\abc\TunSafe\route\routes-up.bat

PostDown = start D:\abc\TunSafe\route\routes-down.bat


#### 5. 正常使用Tunsafe点击connect就会调用routes-up.bat将国内IP写进系统路由表，断开disconnect则会调用routes-down.bat删除路由表。
连接成功后可上 http://ip111.cn/ 测试自己的IP。


### ==================================================

**IPList for China by IPIP.NET**

鉴于众所周知，不用言传你也能意会的理由，我们制作了这份针对于中国大陆地区的 IP 列表。供大家任意发挥使用。

**有几点说明：**

1、一般每月初更新一次。

2、本数据并非完全基于路由表数据生成，IP WHOIS 信息中标注为中国但未做 BGP 公告的数据，也会被列入。

3、因更新频度限制，不对其数据质量做任何承诺，但有问题，可以去我们的 QQ 群反馈，我们根据情况考虑应急更新。

4、我们认为，每天都有 IP 在变动，所以即使有不准的情况，在一个月的更新周期下是正常的情况，如果您有快速更新数据的需求，请与我们联系。

5、为减少条目数量，国内外的运营商骨干网部分 IP 均可能会做模糊化处理，但不影响正常使用。

6、如果觉得我们做的还不错，希望帮忙宣传和支持我们的主力业务。

7、有些多 WAN 口路由器和防火墙设备有 ISP 文件的需求，我们愿意与厂商合作，由我们来提供这个看着细小但实际上很影响用户体验但对我们来说相对轻松的数据，合作形式多样，有兴趣，请与我们联系。

8、IP 地理位置数据库相关讨论 QQ 群: 346280296。

**相关链接：**

1、[IP 地址库免费版下载](https://www.ipip.net/ipdb.html "IPIP.NET IP 归属地数据库")

2、[IPIP.NET 网络工具集](https://www.ipip.net/traceroute.php "IPIP.NET 网络工具集") 目前由我和同事在维护的，全球有 300 多个监测点可供使用，traceroute 功能尤其强大和准确，是你 ping 和 traceroute 的好帮手。

3、[Best Trace 工具](https://www.ipip.net/download.html#ip_trace "Best Trace 工具") 如果你想了解本机发起的 traceroute 情况，并且有地理路径地图可视化需求，请使用我们这个工具，备受好评哦。
