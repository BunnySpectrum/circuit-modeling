
import sys
import code

# Plz don't @ me - this isn't a final way of handling the import :)
sys.path.append("../../cppsim/build/host")
import netlist_pb2

system = netlist_pb2.System()

with open("../../pb_system.bin", "rb") as f:
    system.ParseFromString(f.read())

nodelist = system.nodelist
netlist = system.netlist
elementlist = system.elementlist

# with open("../../pb_nodelist.bin", "rb") as f:
#     nodelist.ParseFromString(f.read())

# with open("../../pb_netlist.bin", "rb") as f:
#     netlist.ParseFromString(f.read())

# with open("../../pb_elementlist.bin", "rb") as f:
#     elementlist.ParseFromString(f.read())

# code.interact(local=locals())
print("Elements")
for element in elementlist.elements:
    # print(f"{node.name}: {[_.name for _ in node.connections]}")
    info = [(_.name + ":" + str(_.uid)) for _ in element.nodes]
    # info = ""
    typeName = netlist_pb2.ElementType.Name(element.type)
    print(f"\t{element.name}:{element.uid} --- Type: {typeName} --- Nodes: {info}")
print("")

print("Nodes")
for node in nodelist.nodes:
    # print(f"{node.name}: {[_.name for _ in node.connections]}")
    print(f"\tname = {node.name}, uid = {node.uid}, key = {node.key}")
print("")

print("Nets")
for net in netlist.nets:
    info = [(_.node_name + ":" + str(_.node_uid)) for _ in net.connections]
    print(f"\t{net.name}:{net.uid} {info}")
print("")





