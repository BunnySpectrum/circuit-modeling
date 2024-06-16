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

            if self.inst.position.angle == 0:
                newX = self.inst.position.X + prop.position.X 
                newY = self.inst.position.Y + prop.position.Y 
            elif self.inst.position.angle == 90: # CCW
                newX = self.inst.position.X + -1*prop.position.Y 
                newY = self.inst.position.Y + 1*prop.position.X - 2.54*2
            elif self.inst.position.angle == 270: # or 90 CW
                newX = self.inst.position.X + 1*prop.position.Y 
                newY = self.inst.position.Y + -1*prop.position.X
            elif self.inst.position.angle == 180:
                newX = self.inst.position.X + -1*prop.position.X 
                newY = self.inst.position.Y + -1*prop.position.Y

            instProp = Property(
                key=prop.key,
                value=newValue,
                position=Position(
                    newX,
                    newY,
                    prop.position.angle), #props maintain their rotation from libEntry
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
sch.libSymbols.append(cap)
capInstBuilder = SymbolInstanceBuilder(cap, sch.uuid, 127, 69.85, 0)
capInst = capInstBuilder.get_instance()
sch.schematicSymbols.append(capInst)

ind = symbol_from_lib(deviceLib, idxL)
sch.libSymbols.append(ind)
indInstBuilder = SymbolInstanceBuilder(ind, sch.uuid, 105.41, 63.5, 90)
indInst = indInstBuilder.get_instance()
sch.schematicSymbols.append(indInst)

res = symbol_from_lib(deviceLib, idxR)
sch.libSymbols.append(res)
resInstBuilder = SymbolInstanceBuilder(res, sch.uuid, 80.01, 63.5, 90)
resInst = resInstBuilder.get_instance()
sch.schematicSymbols.append(resInst)







# code.interact(local=locals())
sch.to_file('test.kicad_sch')