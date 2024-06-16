from kiutils.board import Board
from kiutils.libraries import LibTable
from kiutils.schematic import Schematic
from kiutils.footprint import Footprint
from kiutils.symbol import SymbolLib, Symbol
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
import copy



def symbol_from_lib(lib : SymbolLib, index : int) -> Symbol:
    symbol = lib.symbols[index]
    if symbol.libraryNickname is None:
        libNickname = os.path.splitext(os.path.basename(lib.filePath))[0]
        symbol.libraryNickname = libNickname

    # print(symbol.libId)
    # print(symbol.entryName)
    # print(symbol.hidePinNumbers)

    return symbol


class SymbolInstanceBuilder():
    refOffset = (3.81, -1.27)
    valueOffset = (3.81, 1.27)
    footprintOffset = (0.97, 3.81)
    datasheetOffset = (0, 0)
    descOffset = (0, 0)
    visibleProps = ('Reference', 'Value')

    assignedRefs = {}

    def add_ref(ref: str) -> int:
        if ref not in SymbolInstanceBuilder.assignedRefs.keys():
            SymbolInstanceBuilder.assignedRefs[ref] = 0

        SymbolInstanceBuilder.assignedRefs[ref] += 1

        return SymbolInstanceBuilder.assignedRefs[ref]
            

    def __init__(self, sym : Symbol, schUUID, x: float, y: float, angle: float=0):
        self.ref = "ERR"
        self.sym = sym
        self.properties = []

        currentUnit = 1

        self.inst = SchematicSymbol(
            libraryNickname=self.sym.libraryNickname,
            entryName=self.sym.entryName,
            unit=currentUnit, #TODO determine how multi-unit parts are represented
            inBom=self.sym.inBom,
            onBoard=self.sym.onBoard,
            fieldsAutoplaced=True,
            uuid=uuid.uuid4(),
            dnp=False
        )

        # for now, set position once at creation
        self._set_position(x, y, angle)

        # try to copy props directly from symbolLib entry
        #   ...with some sneaky tweaks
        for prop in self.sym.properties:

            # Tweak #1: Increment refdes
            if prop.key == "Reference":
                refdesNum = SymbolInstanceBuilder.add_ref(prop.value)
                newValue = prop.value + str(refdesNum)
                self.ref = newValue
            else:
                newValue = prop.value

            instProp = Property(
                key=prop.key,
                value=newValue,
                position=Position(
                    self.inst.position.X + prop.position.X,
                    self.inst.position.Y + prop.position.Y,
                    self.inst.position.angle + prop.position.angle),
                effects = copy.copy(prop.effects)
            )

            # Tweak #2: default certain fields to visible
            if(instProp.key in SymbolInstanceBuilder.visibleProps):
                instProp.effects.hide = False 
            else:
                instProp.effects.hide = True

            self.inst.properties.append(instProp)

        # add pins
        for pin in self.sym.pins:
            self.inst.pins[pin.number] = uuid.uuid4()


        # This path/inst likely needs to move out to a schematic.insert() sort of method
        symProjPath = SymbolProjectPath(sheetInstancePath="/" + str(schUUID),
                                   reference=self.ref, 
                                   unit=currentUnit) 
        

        symProjInst = SymbolProjectInstance(name="", paths=[symProjPath])
        self.inst.instances.append(symProjInst)


    # For now, don't call this after init(). It won't update locations of props
    def _set_position(self, x: float, y: float, angle: float = 0):
        self.inst.position.X = x 
        self.inst.position.Y = y
        self.inst.position.angle = angle

    def get_instance(self):
        # in future could let this method trigger any final resolutions/calcs
        return self.inst

    def get_reference(self) -> str:
        return self.ref





kicad8SymbolDir = "/Applications/KiCad/KiCad.app/Contents/SharedSupport/symbols/"
deviceSym = os.path.join(kicad8SymbolDir, 'Device.kicad_sym')
idxR = 456
idxL = 219
idxC = 10


sch = Schematic.create_new()
sch.uuid = uuid.uuid4()
deviceLib = SymbolLib().from_file(deviceSym)

cap = symbol_from_lib(deviceLib, idxC)
# ind = symbol_from_lib(deviceLib, idxL)
# res = symbol_from_lib(deviceLib, idxR)
# cap.libraryNickname = "Device"
sch.libSymbols.append(cap)

capInstBuilder = SymbolInstanceBuilder(cap, sch.uuid, 127, 69.85, 0)
capInst = capInstBuilder.get_instance()

# capInst = SchematicSymbol()
# capInst.libId = cap.libId
# capInst.position.X = 127
# capInst.position.Y = 69.85
# capInst.position.angle = 0
# capInst.unit = 1
# capInst.inBom = cap.inBom
# capInst.onBoard = cap.onBoard
# capInst.dnp = False
# capInst.fieldsAutoplaced = True
# capInst.uuid = uuid.uuid4() #fingers crossed this is unique enough

# capPropRef = Property(
#                 key = "Reference",
#                 value = "C1",
#                 position = Position(130.81, 68.5799, angle=0),
#                 effects = Effects(font=Font(height=1.27, width=1.27), 
#                                     justify=Justify("left")) 
#                 )
# capInst.properties.append(capPropRef)

# capPropValue = Property(
#                 key = "Value",
#                 value = "C",
#                 position = Position(130.81, 71.1199, angle=0),
#                 effects = Effects(font=Font(height=1.27, width=1.27), 
#                                     justify=Justify("left")) 
#                 )
# capInst.properties.append(capPropValue)

# capPropFootprint = Property(
#                 key = "Footprint",
#                 value = "",
#                 position = Position(127.9652, 73.66, angle=0),
#                 effects = Effects(font=Font(height=1.27, width=1.27), 
#                                     justify=Justify("left"), hide=True) 
#                 )
# capInst.properties.append(capPropFootprint)

# capPropDatasheet = Property(
#                 key = "Datasheet",
#                 value = "",
#                 position = Position(127, 69.85, angle=0),
#                 effects = Effects(font=Font(height=1.27, width=1.27), 
#                                     justify=Justify("left"), hide=True) 
#                 )
# capInst.properties.append(capPropDatasheet)

# capPropDesc = Property(
#                 key = "Description",
#                 value = "Unpolarized capacitor",
#                 position = Position(127, 69.85, angle=0),
#                 effects = Effects(font=Font(height=1.27, width=1.27), 
#                                     justify=Justify("left"), hide=True) 
#                 )
# capInst.properties.append(capPropDesc)
# capInst.pins = {"1": uuid.uuid4(), "2": uuid.uuid4()}

# capSymProjPath = SymbolProjectPath(sheetInstancePath="/" + str(sch.uuid),
#                                    reference=capInstBuilder.get_reference(), 
#                                    unit=1) #FIXME spot for multi-unit fix
# capProjInst = SymbolProjectInstance(name="", paths=[capSymProjPath])
# capInst.instances.append(capProjInst)

# print(capInst.to_sexpr())

sch.schematicSymbols.append(capInst)


# code.interact(local=locals())
sch.to_file('test.kicad_sch')