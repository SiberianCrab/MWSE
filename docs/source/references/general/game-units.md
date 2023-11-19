# Game Units

Almost all lengths in the engine are measured in-game units. The various properties (e.g. `.position`) and functions in MWSE use these units. One exception is the spell effect radius, which is measured in feet.

The conversion factor used in the engine between units to feet is 22.1 units/foot.

!!! note
	The numbers claimed in the Construction Set help aren't accurate. The value provided here is used in the Morrowind engine to convert spell effect radius from feet to game units.

## Cells and Their Sizes

There are two types of cells: interior cells and exterior cells. The exterior cells form a grid, where each is 8192 x 8192 units big. Each interior cell is a separate space without defined dimensions.

The water level in all the exterior cells is at 0 Z, while the interior cells have custom water level, usually set in the Construction Set, or don't have water at all.

The landscape consists of vertices that can only be moved on the Z axis (up and down). The vertices are 128 units apart, so a "landscape tile" is 128 x 128 units. Each landscape texture covers 512 x 512 units or 4 by 4 landscape tiles.


## Actor Height

The base height of an actor is 128 game units. It's further changed by the racial height modifier.
