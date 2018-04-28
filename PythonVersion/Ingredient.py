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


class Ingredient:	
	def __init__(self, q, u, i):
		self.qty = q
		self.unit = u
		self.item = i
		if(i in SpiceDict):
			self.isSpice = True
			self.calculate()
		else:
			self.isSpice = False
	
	def display(self):
		print(self.item)
		print(self.qty)
		print(self.unit)
		if(self.isSpice):
			print(self.weight)
			print(self.time)
		else:
			print("Is NOT a spice")
			
	def calculate(self):
		if(self.isSpice):
			self.weight = self.qty * SpiceDict[self.item] * MeasureToTeaspoon[self.unit]
			self.time = 5 * self.qty * MeasureToTeaspoon[self.unit]
