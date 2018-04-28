import xml.etree.ElementTree as ET
import Ingredient as I
import Motor as M

class Recipe:
	path = ''
	name = ''
	ingredients = []
	directions = []
	
	def __init__(self, path):
		self.path = path
		 
	def parseXML(self):
		tree = ET.ElementTree(file = self.path)
		root = tree.getroot()
		recipe = root.getchildren()[0]
		for section in recipe:
			if(section.tag == 'head'):
				self.name = section.getchildren()[0].text
				
			elif(section.tag == 'ingredients'):
				ingList = []
				ingredients = section.getchildren()
				for ing in ingredients:
					v = ing.getchildren();
					qty = v[0].getchildren()[0];
					unit = v[0].getchildren()[1];
					item = v[1];
					i = I.Ingredient(int(qty.text), unit.text.lower(), item.text.lower())
					self.ingredients.append(i)
					
			elif(section.tag == 'directions'):
				dirList = []
				steps = section.getchildren()
				for s in steps:
					self.directions.append(s.text)
		
		
	def display(self):
		print(self.path)
		print(self.name)
		for i in self.ingredients:
			i.display()
			print('')
		
		print('')
		for d in self.directions:
			print(d)
			
	def	dispense(self):
		print("dispensing")	


