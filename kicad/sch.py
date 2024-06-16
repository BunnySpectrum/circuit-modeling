from kiutils.board import Board
from kiutils.libraries import LibTable
from kiutils.schematic import Schematic
from kiutils.footprint import Footprint
from kiutils.symbol import SymbolLib
from kiutils.wks import WorkSheet
from kiutils.dru import DesignRules

from kiutils.items.schitems import SchematicSymbol, SymbolProjectInstance, SymbolProjectPath
from kiutils.items.common import Property
from kiutils.items.common import Position
from kiutils.items.common import Effects
from kiutils.items.common import Font
from kiutils.items.common import Justify

import os
import code
import uuid

def symbol_for_index(lib : SymbolLib, index):
    symbol = lib.symbols[index]

    # print(symbol.libId)
    # print(symbol.entryName)
    # print(symbol.hidePinNumbers)

    # print(symbol.)
    # print(symbol.)
    # print(symbol.)
    # print(symbol.)
    # print(symbol.)
    return symbol

kicad8SymbolDir = "/Applications/KiCad/KiCad.app/Contents/SharedSupport/symbols/"

deviceSym = os.path.join(kicad8SymbolDir, 'Device.kicad_sym')
idxR = 456
idxL = 219
idxC = 10
#   entryName = C


sch = Schematic.create_new()
sch.uuid = uuid.uuid4()
deviceLib = SymbolLib().from_file(deviceSym)

cap = symbol_for_index(deviceLib, idxC)
ind = symbol_for_index(deviceLib, idxL)
res = symbol_for_index(deviceLib, idxR)
cap.libraryNickname = "Device"
sch.libSymbols.append(cap)

capInst = SchematicSymbol()
capInst.libId = cap.libId
capInst.position.X = 127
capInst.position.Y = 69.85
capInst.position.angle = 0
capInst.unit = 1
capInst.inBom = cap.inBom
capInst.onBoard = cap.onBoard
capInst.dnp = False
capInst.fieldsAutoplaced = True
capInst.uuid = uuid.uuid4() #fingers crossed this is unique enough

capPropRef = Property(
                key = "Reference",
                value = "C1",
                position = Position(130.81, 68.5799, angle=0),
                effects = Effects(font=Font(height=1.27, width=1.27), 
                                    justify=Justify("left")) 
                )
capInst.properties.append(capPropRef)

capPropValue = Property(
                key = "Value",
                value = "C",
                position = Position(130.81, 71.1199, angle=0),
                effects = Effects(font=Font(height=1.27, width=1.27), 
                                    justify=Justify("left")) 
                )
capInst.properties.append(capPropValue)

capPropFootprint = Property(
                key = "Footprint",
                value = "",
                position = Position(127.9652, 73.66, angle=0),
                effects = Effects(font=Font(height=1.27, width=1.27), 
                                    justify=Justify("left"), hide=True) 
                )
capInst.properties.append(capPropFootprint)

capPropDatasheet = Property(
                key = "Datasheet",
                value = "",
                position = Position(127, 69.85, angle=0),
                effects = Effects(font=Font(height=1.27, width=1.27), 
                                    justify=Justify("left"), hide=True) 
                )
capInst.properties.append(capPropDatasheet)

capPropDesc = Property(
                key = "Description",
                value = "Unpolarized capacitor",
                position = Position(127, 69.85, angle=0),
                effects = Effects(font=Font(height=1.27, width=1.27), 
                                    justify=Justify("left"), hide=True) 
                )
capInst.properties.append(capPropDesc)
capInst.pins = {"1": uuid.uuid4(), "2": uuid.uuid4()}

capSymProjPath = SymbolProjectPath(sheetInstancePath="/" + str(sch.uuid),
                                   reference="C1", unit=1)
capProjInst = SymbolProjectInstance(name="", paths=[capSymProjPath])
capInst.instances.append(capProjInst)

print(capInst.to_sexpr())

sch.schematicSymbols.append(capInst)


code.interact(local=locals())
sch.to_file('test.kicad_sch')