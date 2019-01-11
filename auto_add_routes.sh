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

