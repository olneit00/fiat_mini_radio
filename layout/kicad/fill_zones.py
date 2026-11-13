#!/usr/bin/env python3
"""Fill the existing GND copper zone using KiCad's own pcbnew engine."""
import sys
import pcbnew

if len(sys.argv) != 3:
    raise SystemExit("Usage: fill_zones.py input.kicad_pcb output.kicad_pcb")

source, target = sys.argv[1:]
board = pcbnew.LoadBoard(source)
zones = board.Zones()
if len(zones) == 0:
    raise SystemExit("No copper zones found; refusing to write output")
print("Zones found:", len(zones))
for zone in zones:
    print("Zone:", zone.GetNetname(), zone.GetLayerName())
pcbnew.ZONE_FILLER(board).Fill(zones)
pcbnew.SaveBoard(target, board)
print("Filled board saved:", target)
