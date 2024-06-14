
import sys
import code

# Plz don't @ me - this isn't a final way of handling the import :)
sys.path.append("../../system_cpp/build/host")
import netlist_pb2

system = netlist_pb2.System()

with open("../../pb_system.bin", "rb") as f:
    system.ParseFromString(f.read())

netlist = system.netlist
elementlist = system.elementlist

print("Elements")
for element in elementlist.elements:
    # print(f"{node.name}: {[_.name for _ in node.connections]}")
    info = [(_.key + ": " +_.name + ":" + str(_.uid)) for _ in element.nodes]
    # info = ""
    typeName = netlist_pb2.ElementType.Name(element.type)
    print(f"\t{element.name}:{element.uid} --- Type: {typeName} --- Nodes: {{{', '.join(info)}}}")
print("")

print("Nets")
for net in netlist.nets:
    info = [(_.node_name + ":" + str(_.node_uid)) for _ in net.connections]
    print(f"\t{net.name}:{net.uid} {info}")
print("")





