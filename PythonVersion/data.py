import os
import Recipe

RecipeObj = []

def RecipeLib():
	recipes = []
	for file in os.listdir("./saved_recipes"):
		if file.endswith(".xml"):
			path = os.path.join("./saved_recipes", file)
			R = Recipe.Recipe(path)
			R.parseXML()
			d = {}
			d['name'] = R.getName()
			d['directions'] = R.getDirections()
			d['description'] = R.getDescription()
			
			ingList = []
			for i in R.getIngredients():
				ingList.append([i.getQty(), i.getUnit(), i.getType()])
			print(ingList)
			d['ingredients'] = ingList
						
			recipes.append(d)
			RecipeObj.append(R)
	return recipes


def startDispensing(name):
	for r in RecipeObj:
		if r.getName() == name:
			r.dispense()
