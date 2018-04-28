import xml.etree.ElementTree as ET
import time
import Adafruit_PCA9685


SpiceDict = {
	"salt": 5.69,
	"pepper": 2.3,
	"garlic powder": 3.1
}

MeasureToTeaspoon = {
	"pinch": 0.125,
	"pinches": 0.125,
	"teaspoon": 1.0,
	"teaspoons": 1.0,
	"tablespoon": 3.0,
	"tablespoons": 3.0,
	"cup": 48.0,
	"cups": 48.0
}

class SpiceContainers:
	def __init__(self):
		self.containers = {
			'salt' : 0,
			'pepper' : 1,
			'garlic powder' : 2
		}
		
	def addSpice(self, key, value):
		self.containers[key] = value
		
	def removeSpice(self, key):
		r = self.containers(key)
		del r[key]
		
	def getContainer(self, key):
		if key in self.containers:
			return self.containers[key]
		return -1



class Motor:
	def __init__(self):
		self.driver = Adafruit_PCA9685.PCA9685();
		self.driver.set_pwm_freq(60);
		self.allStop()

	def spin(self, n, speed):
		self.driver.set_pwm(n, 0, 355)
		
	def stop(self, n):
		self.driver.set_pwm(n, 0, 0)

	def allStop(self):
		for n in range(0, 16):
			self.driver.set_pwm(n, 0, 0)
			

class Ingredient:	
	def __init__(self, q, u, i):
		self.qty = q
		self.unit = u
		self.item = i
		if self.isSpice():
			self.calculate()
	
	def display(self):
		print(self.item)
		print(self.qty)
		print(self.unit)
		if(self.isSpice()):
			print(self.weight)
			print(self.time)
		else:
			print("Is NOT a spice")
			
	def calculate(self):
		self.weight = self.qty * SpiceDict[self.item] * MeasureToTeaspoon[self.unit]
		self.time = 5 * self.qty * MeasureToTeaspoon[self.unit]
	
	def isSpice(self):
		if(self.item in SpiceDict):
			return True
		else:
			return False
			
	def getTime(self):
		return self.time
		
	def getType(self):
		return self.item
		
	def getQty(self):
		return self.qty
		
	def getUnit(self):
		return self.unit



class Recipe:
	def __init__(self, path):
		self.path = path
		self.description = ""
		self.ingredients = []
		self.spices = []
		self.directions = []
		self.motors = Motor()
		self.Vials = SpiceContainers()
		 
	def parseXML(self):
		tree = ET.ElementTree(file = self.path)
		root = tree.getroot()
		recipe = root.getchildren()[0]
		for section in recipe:
			if(section.tag == 'head'):
				self.name = section.getchildren()[0].text
				self.description = section.getchildren()[1].text
							
			elif(section.tag == 'ingredients'):
				ingList = []
				ingredients = section.getchildren()
				for ing in ingredients:
					v = ing.getchildren();
					qty = v[0].getchildren()[0];
					unit = v[0].getchildren()[1];
					item = v[1];
					i = Ingredient(int(qty.text), unit.text.lower(), item.text.lower())
					if i.isSpice():
						self.spices.append(i)
						self.ingredients.append(i)
					else:
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

	def getName(self):
		return self.name
		
	def getIngredients(self):
		 return self.ingredients
			 
	def getDirections(self):
		return self.directions
		
	def getDescription(self):
		return self.description
			
	def	dispense(self):
		for s in self.spices:
			index = self.Vials.getContainer(s.getType()) 
			if(index != -1):
				self.motors.spin(index, 355)
				time.sleep(s.getTime())
				self.motors.stop(index)
		self.motors.allStop()

