#!/bin/bash

curl --user "admin":"admin" -H "Accept: application/json" -H "Content-type: application/json" -X POST http://127.0.0.1:8080/one/nb/v2/lb/default/create/pool -d '{"name":"PoolRR","lbmethod":"roundrobin"}'

if [[ $? == 0 ]] ; then
echo " load balancer pool Created "
fi

curl --user "admin":"admin" -H "Accept: application/json" -H "Content-type: application/json" -X POST http://127.0.0.1:8080/one/nb/v2/lb/default/create/vip -d '{"name":"VIP-RR","ip":"10.0.0.20","protocol":"TCP","port":"5550","poolname":"PoolRR"}'
echo " Create load balancer VIP "
curl --user "admin":"admin" -H "Accept: application/json" -H "Content-type: application/json" -X PUT http://127.0.0.1:8080/one/nb/v2/lb/default/update/vip -d '{"name":"VIP-RR","poolname":"PoolRR"}'

if [[ $? == 0 ]] ; then
echo " load balancer VIP Created "
fi
echo "Creating Pool Members"
for members in 2 3 4
do

curl --user "admin":"admin" -H "Accept: application/json" -H "Content-type: application/json" -X POST http://127.0.0.1:8080/one/nb/v2/lb/default/create/poolmember -d '{"name":"PM'$members'","ip":"10.0.0.'$members'","poolname":"PoolRR"}'

if [[ $? == 0 ]] ; then
echo " Pool Member PM"$members" Created "
fi
done

curl --user "admin":"admin" -H "Accept: application/json" -H "Content-type: application/json" -X GET http://127.0.0.1:8080/one/nb/v2/lb/default/PoolRR/pms