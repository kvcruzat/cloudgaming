import json
import networkx as nx
from networkx.readwrite import json_graph
import httplib2

baseUrl = 'http://localhost:8080/controller/nb/v2'

h = httplib2.Http(".cache")
h.add_credentials('admin', 'admin')
containerName ='default'

def find_edge(edges, headNode, tailNode):
  for edge in odlEdges:
    if edge['edge']['headNodeConnector']['node']['id'] == headNode and edge['edge']['tailNodeConnector']['node']['id'] == tailNode:
      return edge
  return None

def push_path(path, odlEdges, srcIP, dstIP, baseUrl):
  for i, node in enumerate(path[1:-1]):
    flowName = "fromIP" + srcIP[-1:] + "Po" + str(i)
    print node
    print shortest_path
    #ingressEdge = next(edge for edge in odlEdges if edge['edge']['headNodeConnector']['node']['@id'] == shortest_path[i] and edge['edge']['tailNodeConnector']['node']['@id'] == node)
    ingressEdge = find_edge(odlEdges, shortest_path[i], node)
    egressEdge = find_edge(odlEdges, node, shortest_path[i+2])
    #egressEdge = next(edge for edge in odlEdges if edge['edge']['headNodeConnector']['node']['@id'] == node and edge['edge']['tailNodeConnector']['node']['@id'] == shortest_path[i+2])
    newFlow = build_flow_entry(flowName, ingressEdge, egressEdge, node, srcIP, dstIP)
    switchType = newFlow['node']['@type']
    postUrl = build_flow_url(baseUrl, 'default', switchType, node, flowName)
    # post the flow to the controller
    resp, content = post_dict(h, postUrl, newFlow)


def build_url(baseUrl, service, containerName):
  postUrl = '/'.join([baseUrl, service, containerName])
  return postUrl

# Get all the edges/links
resp, content = h.request(build_url(baseUrl, 'topology', containerName), "GET")
edgeProperties = json.loads(content)
odlEdges = edgeProperties['edgeProperties' ]

print json.dumps(edgeProperties, indent = 2)

graph = nx.Graph()
for edge in odlEdges:
  e = (edge['edge']['headNodeConnector']['node']['id'], edge['edge']['tailNodeConnector']['node']['id'])
  graph.add_edge(*e)

print graph.edges()
# Print out graph info as a sanity check
print "shortest path from h1` to ch" 
shortest_path = nx.shortest_path(graph, "00:00:00:00:00:00:00:01", "00:00:00:00:00:00:00:05")
print shortest_path