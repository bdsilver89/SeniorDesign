from flask import Flask, render_template, request
from data import RecipeLib, startDispensing

app = Flask(__name__)

Recipes = RecipeLib()

@app.route('/')
def index():
   return render_template('home.html')


@app.route('/recipes')
def recipes():
	return render_template('recipes.html', recipes=Recipes)


@app.route('/recipe/<string:name>/', methods=['GET', 'POST'])
def recipe(name):
	directions = []
	for r in Recipes:
		if r['name'] == name:
			directions = r['directions']
			description = r['description']
			ingredients = r['ingredients']
			if request.method == 'POST':
				val = request.form['text']
				startDispensing(name)
	return render_template('recipe.html', name=name, description=description, directions=directions, ingredients=ingredients)
		





if __name__ == '__main__':
   app.run(debug = True)
