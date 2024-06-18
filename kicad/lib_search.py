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
import argparse

kicad8SymbolDir = "/Applications/KiCad/KiCad.app/Contents/SharedSupport/symbols/"
parser = argparse.ArgumentParser()
parser.add_argument("lib", type=str, help="Library name")
parser.add_argument("name", type=str, help="Symbol name to find.")
parser.add_argument("--dir", default=kicad8SymbolDir, help="Kicad dir with symbol libs.")
args = parser.parse_args()


deviceSym = os.path.join(kicad8SymbolDir, args.lib + '.kicad_sym')
# print(deviceSym)

deviceLib = SymbolLib().from_file(deviceSym)
for idx, symbol in enumerate(deviceLib.symbols):
    if symbol.entryName == args.name:
        print(f"Found: {args.name} at {idx}.")
        break

# code.interact(local=locals())


def symbol_from_lib(lib : SymbolLib, index : int) -> Symbol:
    symbol = lib.symbols[index]
    if symbol.libraryNickname is None:
        libNickname = os.path.splitext(os.path.basename(lib.filePath))[0]
        symbol.libraryNickname = libNickname

    return symbol




