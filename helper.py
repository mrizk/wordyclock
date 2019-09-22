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