from kiutils.board import Board
from kiutils.libraries import LibTable
from kiutils.schematic import Schematic
from kiutils.footprint import Footprint
from kiutils.symbol import SymbolLib, Symbol
from kiutils.wks import WorkSheet
from kiutils.dru import DesignRules

from kiutils.items.schitems import SchematicSymbol, SymbolProjectInstance, SymbolProjectPath, Connection, Stroke
from kiutils.items.common import Property
from kiutils.items.common import Position
from kiutils.items.common import Effects
from kiutils.items.common import Font
from kiutils.items.common import Justify

import os
import code
import uuid
import copy

def transform_pos_sym_to_page(pos:Position) -> Position:
    newPos = Position(
        X = pos.X,
        Y = pos.Y*-1,
        angle = pos.angle
    )

    return newPos


def add_pos(pos1:Position, pos2:Position) -> Position:
    newPos = Position(
        X = round(pos1.X + pos2.X, 2),
        Y = round(pos1.Y + pos2.Y, 2),
        angle=pos1.angle
    )

    return newPos

def rotate_pos(pos:Position, degree = 0) -> Position:
    if degree == 0:
        newX = pos.X 
        newY = pos.Y 
    elif degree == 90: # CCW
        newX = -1*pos.Y 
        newY = 1*pos.X
    elif degree == 270: # or 90 CW
        newX = 1*pos.Y 
        newY = -1*pos.X
    elif degree == 180:
        newX = -1*pos.X 
        newY = -1*pos.Y
    
    newPos = Position(X=newX, Y=newY, angle=0)

    return newPos



def symbol_from_lib(lib : SymbolLib, index : int) -> Symbol:
    symbol = lib.symbols[index]
    if symbol.libraryNickname is None:
        libNickname = os.path.splitext(os.path.basename(lib.filePath))[0]
        symbol.libraryNickname = libNickname

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
        self.pins = {}

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

            newPos = rotate_pos(prop.position, self.inst.position.angle)
            newX = self.inst.position.X + newPos.X 
            newY = self.inst.position.Y + newPos.Y

            if self.inst.position.angle == 90: # CCW
                newY -= 2.54*2

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
        # seems like pins show up in child symbols..but I'm unsure why
        # c.f. https://forum.kicad.info/t/kicad-sym-documentation-clarification/32517
        for pin in self.sym.units[1].pins: #hack for now...so far the pins are here
            self.inst.pins[pin.number] = uuid.uuid4()
            self.pins[pin.number] = add_pos(self.inst.position, 
                                            transform_pos_sym_to_page(
                                                rotate_pos(
                                                    pin.position, 
                                                    1*self.inst.position.angle
                                                )
                                            )
                                        )


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
    
    def get_pin_location(self, pin: str) -> Position:
        return self.pins[pin]




def draw_wire(sch:Schematic, comp1:SymbolInstanceBuilder, pin1:str, comp2:SymbolInstanceBuilder, pin2:str):
    if pin1 not in comp1.pins.keys():
        print(f"Error, pin {pin1} not in comp1")

    if pin2 not in comp2.pins.keys():
        print(f"Error, pin {pin2} not in comp2")

    conn = Connection(
            type="wire",
            points=[comp1.get_pin_location(pin1), comp2.get_pin_location(pin2)],
            stroke=Stroke(width=0, type=None),
            uuid=uuid.uuid4()
        )
    
    sch.graphicalItems.append(conn)

idxDevice = {
    "C": 10,
    "Crystal": 37,
    "D": 47,
    "DelayLine": 196,
    "Fuse": 210,
    "R": 456,
    "L": 219,
    "LED": 220,
    "Opamp_Dual": 339,
    }

#Simulation_SPICE
idxSPICE = {
    "IDC": 10,
    "NMOS": 19,
    "PMOS": 25,
    "OPAMP": 23,
    "VDC": 32,
}

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

draw_wire(sch, resInstBuilder, "2", indInstBuilder, "1")
draw_wire(sch, capInstBuilder, "1", indInstBuilder, "2")

# code.interact(local=locals())




sch.to_file('test.kicad_sch')