import constants

def indecies_from_matrix(xStart, xEnd, yStart, yEnd=None):
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
    

Its = indecies_from_matrix(0, 2, 0)

HappyBirthDay = indecies_from_matrix(7, 11, 1) + indecies_from_matrix(7, 11, 5) + indecies_from_matrix(9, 11, 9)

FiveM = indecies_from_matrix(7, 10, 2)
TenM = indecies_from_matrix(8, 10, 0)
TwentyM = indecies_from_matrix(0, 5, 1)
Minutes = indecies_from_matrix(0, 6, 3)

Half = indecies_from_matrix(4, 7, 0)
AQuarter = indecies_from_matrix(6, 6, 1) + indecies_from_matrix(0, 6, 2)

To = indecies_from_matrix(8, 9, 3)
Past = indecies_from_matrix(0, 3, 4)

One = indecies_from_matrix(5, 7, 4)
Two = indecies_from_matrix(8, 10, 4)
Three = indecies_from_matrix(1, 5, 5)
Four = indecies_from_matrix(4, 7, 6)
Five = indecies_from_matrix(8, 11, 6)
Six = indecies_from_matrix(0, 2, 7)
Seven = indecies_from_matrix(3, 7, 7)
Eight = indecies_from_matrix(0, 4, 8)
Nine = indecies_from_matrix(8, 11, 7)
Ten = indecies_from_matrix(1, 3, 10)
Eleven = indecies_from_matrix(5, 10, 8)
Noon = indecies_from_matrix(0, 3, 6)
Midnight = indecies_from_matrix(0, 7, 9)

Oclock = indecies_from_matrix(6, 11, 11)

AndXMinutes = indecies_from_matrix(8, 11, 12)