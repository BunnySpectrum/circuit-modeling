
import sys
import code

# Plz don't @ me - this isn't a final way of handling the import :)
sys.path.append("../../cppsim/build/host")
import netlist_pb2

nodelist = netlist_pb2.NodeList()
with open("../../pb_netlist.bin", "rb") as f:
    nodelist.ParseFromString(f.read())

# print(nodelist.nodes)


for node in nodelist.nodes:
    print(f"{node.name}: {[_.name for _ in node.connections]}")
          

# code.interact(local=locals())

