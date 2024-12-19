import tkinter
import cv2
import pyperclip
#   REQUIRED: tkinter, cv2, and a field image named "vex field.png"
#   The field image must be in the same directory as this file, and must be an image of ONLY the vex field
#   The field can have items on it (like game objects), but cannot have anything outside of the field walls



#   This program is used to generate a motion profile for the robot
#   The user clicks on the field to place points
#   The program then prints the points in the format that the robot can use
#   The format is used for OKAPILIB motion profiles, see
#   https://okapilib.github.io/OkapiLib/md_docs_tutorials_concepts_twodmotionprofiling.html
#   for more information
# init tk
root = tkinter.Tk()


#get the width and height of the image
img = cv2.imread("vex field.png")
CANVAS_HEIGHT, CANVAS_WIDTH, no_channels = img.shape

#constants
# UNIT is a QLength unit from this page: https://okapilib.github.io/OkapiLib/md_docs_api_units.html
UNIT = "ft"
# the width and height of the field IN THE SPECIFIED UNIT
FIELD_WIDTH = 12
FIELD_HEIGHT = 12
FEETTOPIXELS = FIELD_WIDTH/CANVAS_WIDTH
CIRCLE_SIZE_IN_DIAMETER_PIX = 20


# create canvas
myCanvas = tkinter.Canvas(root, bg="white", height=CANVAS_HEIGHT, width=CANVAS_WIDTH)

# draw image
field = tkinter.PhotoImage(file="vex field.png")
myCanvas.create_image(0, 0, image=field, anchor=tkinter.NW)


points = []


def drawLine(p1, p2):
    myCanvas.create_line(p1.x_pix, p1.y_pix, p2.x_pix, p2.y_pix, fill="red")


class point:
    def __init__(self, x, y, angle):
        self.x = x
        self.y = y
        self.ang = angle
        self.x_pix = x * (1/FEETTOPIXELS)
        self.y_pix = y * (1/FEETTOPIXELS)
        # draw the point
        myCanvas.create_oval(self.x_pix - CIRCLE_SIZE_IN_DIAMETER_PIX, self.y_pix - CIRCLE_SIZE_IN_DIAMETER_PIX, self.x_pix + CIRCLE_SIZE_IN_DIAMETER_PIX, self.y_pix + CIRCLE_SIZE_IN_DIAMETER_PIX, fill="blue")
    
    def __str__(self):
        return f"{{{round(self.x)}_{UNIT}, {round(self.y)}_{UNIT}, {round(self.ang)}_deg}}"


def generateAngle(p1, p2):
    ang = (p2.y_pix - p1.y_pix)/(p2.x_pix - p1.x_pix)
    return ang

def generateAngles():
    for i in points:
        if(i != points[0]):
            i.ang = generateAngle(points[points.index(i)-1], i)

def placePoint(e):
    # add the point to the list
    points.append(point(e.x * FEETTOPIXELS, e.y * FEETTOPIXELS, 0))
    # draw a line between the last two points
    if(len(points) > 1):
        # generateAngles()
        drawLine(points[-2], points[-1])


def printPoints():
    # print the points in the format used by the robot
    output = ""
    output += "generatePath({"
    output += "\n"
    for i in points:
        output += i.__str__() 
        if(i != points[-1]):
            output += ","
            output += "\n"
    output += "},"
    output += f"\"{name}\");"
    return output


# bind mouse click to placePoint
myCanvas.bind("<Button-1>", placePoint)


# add to window and show
myCanvas.pack()
root.mainloop()


name = input("Enter the name of the profile: ")


output = printPoints()
print(output)

pyperclip.copy(output)