import constants

def indeciesFromMatrix(xStart, xEnd, yStart, yEnd=None):
    """returns indecies of a word from the given matrix, assumes matrix (0, 0) is top left"""
    indecies = []
    for y in range(0, constants.CLOCK_HEIGHT):
        if (yEnd is None and y == yStart) or (y >= yStart and y <= yEnd):
            yPos = y

            if constants.CLOCK_ORIGIN == constants.ORIGIN_BOTTOM_LEFT or constants.CLOCK_ORIGIN == constants.ORIGIN_BOTTOM_RIGHT:
                yPos = constants.CLOCK_HEIGHT - yPos

            for x in range(0, constants.CLOCK_WIDTH):
                if x >= xStart and x <= xEnd:
                    xPos = x

                    if constants.CLOCK_ORIGIN == constants.ORIGIN_TOP_RIGHT or constants.CLOCK_ORIGIN == constants.ORIGIN_BOTTOM_RIGHT:
                        if y % 2 == 0:
                            xPos = (constants.CLOCK_WIDTH - 1) - xPos
                    elif constants.CLOCK_ORIGIN == constants.ORIGIN_TOP_LEFT or constants.CLOCK_ORIGIN == constants.ORIGIN_BOTTOM_LEFT:
                        if y % 2 == 1:
                            xPos = (constants.CLOCK_WIDTH - 1) - xPos
                    
                    indecies.append((yPos * constants.CLOCK_WIDTH) + xPos)

    return indecies
    

Its = indeciesFromMatrix(0, 2, 0)

HappyBirthDay = indeciesFromMatrix(7, 11, 1) + indeciesFromMatrix(7, 11, 5) + indeciesFromMatrix(9, 11, 9)

FiveM = indeciesFromMatrix(7, 10, 2)
TenM = indeciesFromMatrix(8, 10, 0)
TwentyM = indeciesFromMatrix(0, 5, 1)
Minutes = indeciesFromMatrix(0, 6, 3)

Half = indeciesFromMatrix(4, 7, 0)
AQuarter = indeciesFromMatrix(6, 6, 1) + indeciesFromMatrix(0, 6, 2)

To = indeciesFromMatrix(8, 9, 3)
Past = indeciesFromMatrix(0, 3, 4)

One = indeciesFromMatrix(5, 7, 4)
Two = indeciesFromMatrix(8, 10, 4)
Three = indeciesFromMatrix(1, 5, 5)
Four = indeciesFromMatrix(4, 7, 6)
Five = indeciesFromMatrix(8, 11, 6)
Six = indeciesFromMatrix(0, 2, 7)
Seven = indeciesFromMatrix(3, 7, 7)
Eight = indeciesFromMatrix(0, 4, 8)
Nine = indeciesFromMatrix(8, 11, 7)
Ten = indeciesFromMatrix(1, 3, 10)
Eleven = indeciesFromMatrix(5, 10, 8)
Noon = indeciesFromMatrix(0, 3, 6)
Midnight = indeciesFromMatrix(0, 7, 9)

Oclock = indeciesFromMatrix(6, 11, 11)

AndXMinutes = indeciesFromMatrix(8, 11, 12)