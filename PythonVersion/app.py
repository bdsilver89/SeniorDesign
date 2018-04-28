from __future__ import division
import time

from Tkinter import Tk

import Recipe
import GUI

root = Tk()
my_gui = GUI.GUI(root)
root.mainloop()

#R = Recipe.Recipe('./saved_recipes/test2.xml')
#R.parseXML()
#R.display()
#R.dispense()
