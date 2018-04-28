from Tkinter import Tk, Label, Button, Entry, StringVar, IntVar, END, W, E


class GUI:
	def __init__(self, master):
		self.master = master
		pad = 3
		self._geom = '200x200+0+0'
		master.geometry("{0}x{1}+0+0".format(
			master.winfo_screenwidth()-pad, master.winfo_screenheight()-pad))
		master.title("AutoSpice")
	
		
