from Tkinter import *

import Recipe

class Application:
	def __init__(self, master):
		self.master = master
		pad = 3
		self._geom = '200x200+0+0'
		master.geometry("{0}x{1}+0+0".format(
			master.winfo_screenwidth()-pad, master.winfo_screenheight()-pad))
		master.title("AutoSpice")
	
		v = StringVar()
		self.recipe_textEntry = Entry(master, textvariable=v)
		self.recipe_textEntry.pack()
		
		
		
		
		
		
#R = Recipe.Recipe('./saved_recipes/test2.xml')
#R.parseXML()
#R.display()
#R.dispense()
