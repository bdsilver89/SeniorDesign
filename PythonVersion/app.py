#from Tkinter import Tk
#import GUI
#import Recipe
from flask import Flask, render_template, request
from data import RecipeLib

app = Flask(__name__)

Recipes = RecipeLib()

@app.route('/')
def index():
   return render_template('home.html')


@app.route('/recipes')
def recipes():
    return render_template('recipes.html', recipes=Recipes)


@app.route('/recipe/<string:id>/', methods=['GET', 'POST'])
def recipe(id):
    if request.method == 'POST':
        val = request.form['text']
        print("Submission: " + val)
    return render_template('recipe.html', id=id)





if __name__ == '__main__':
   app.run(debug = True)

'''
root = Tk()
my_gui = GUI.Application(root)
root.mainloop()
'''