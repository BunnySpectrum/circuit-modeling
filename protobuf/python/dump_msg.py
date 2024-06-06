
import sys
import code

# Plz don't @ me - this isn't a final way of handling the import :)
sys.path.append("../../cppsim/build/host")
import netlist_pb2

nodelist = netlist_pb2.NodeList()
netlist = netlist_pb2.NetList()

with open("../../pb_netlist.bin", "rb") as f:
    netlist.ParseFromString(f.read())

# print(nodelist.nodes)

# print("Nodes")
# for node in nodelist.nodes:
#     # print(f"{node.name}: {[_.name for _ in node.connections]}")
#     print(f"\t{node.name}")
# print("")

print("Nets")
for net in netlist.nets:
    print(f"\t{net.name}: {[_.name for _ in net.connections]}")
print("")




# code.interact(local=locals())

