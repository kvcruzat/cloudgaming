import requests
from requests.auth import HTTPBasicAuth
from subprocess import Popen, PIPE

# Make system commands
def systemCommand(cmd):
	terminalProcess = Popen(cmd, stdout=PIPE, stderr=PIPE, shell=True)
	terminalOutput, stderr = terminalProcess.communicate()
	print "\n*** Flow Deleted\n"

numSwitches = 7
numClients = 3
numServers = 8

# Loops over every switch and every possible installed flow and deletes them
countSwitch = 1
while countSwitch <= numSwitches:
	countClients = 1
	while countClients <= numClients:
		countServers = 4
		while countServers < numServers+4:
			print "Switch " + str(countSwitch)
			print "Client " + str(countClients)
			print "Server " + str(countServers)
			#Delete source to destination flow
			flowURL = "http://127.0.0.1:8181/restconf/config/opendaylight-inventory:nodes/node/openflow:"+ str(countSwitch) +"/table/0/flow/"+str(countClients)+str(countServers)+"1"
			command = 'curl --user "admin":"admin" -H "Accept: application/xml" -H "Content-type: application/xml" -X DELETE ' + flowURL
			systemCommand(command)

			#Delete destination to source flow
			flowURL = "http://127.0.0.1:8181/restconf/config/opendaylight-inventory:nodes/node/openflow:"+ str(countSwitch) +"/table/0/flow/"+str(countClients)+str(countServers)+"2"
			command = 'curl --user "admin":"admin" -H "Accept: application/xml" -H "Content-type: application/xml" -X DELETE ' + flowURL
			systemCommand(command)
			
			countServers = countServers + 1
		countClients = countClients + 1
	countSwitch = countSwitch + 1