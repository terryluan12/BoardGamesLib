import sys
import os

path_to_python_module = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../../../build/languages/python'))
sys.path.insert(0, path_to_python_module)

import dogan

if __name__ == "__main__":
    config = dogan.ConfigBuilder().build()
    game = dogan.Game(config)
    game.addPlayer(0)
    game.giveResources(0, [10, 10, 10, 10, 10])
    
    coordinate = dogan.Coordinate2D(0, 0)
    game.buildStructure(\
                        0, \
                        dogan.DoganStructureType.Type_VILLAGE, \
                        coordinate, \
                        dogan.AxialDirection.Direction_NORTH, [0, 0, 0, 0, 0], False)
    print(game.getResourceCount(0))