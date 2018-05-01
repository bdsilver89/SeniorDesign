from flask import Flask, render_template, request, flash, redirect, url_for, session, logging
from flask_mysqldb import MySQL
from wtforms import Form, StringField, TextAreaField, PasswordField, validators
from passlib.hash import sha256_crypt
from functools import wraps

from data import RecipeLib, startDispensing, readDirection

'''
To Run:
sudo /etc/init.d/mysql stop
sudo -s
mysqld_safe --skip-grant-tables &

'''

app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'superuser'
app.config['MYSQL_PASSWORD'] = 'password'
app.config['MYSQL_DB'] = 'mySeniorDesign'
app.config['MYSQL_CURSORCLASS'] = 'DictCursor'

mysql = MySQL(app)

Recipes = RecipeLib()

# Check if user is logged out
def is_logged_in(f):
	@wraps(f)
	def wrap(*args, **kwargs):
		if 'logged_in' in session:
			return f(*args, **kwargs)
		else:
			flash('Unauthorized, Please login', 'danger')
			return redirect(url_for('login'))
	return wrap


# index page
@app.route('/')
def index():
   return render_template('home.html')


# Recipe homepage
@app.route('/recipes')
def recipes():
	return render_template('recipes.html', recipes=Recipes)


# Recipe
@app.route('/recipe/<string:name>/', methods=['GET', 'POST'])
def recipe(name):
	directions = []
	for r in Recipes:
		if r['name'] == name:
			directions = r['directions']
			description = r['description']
			ingredients = r['ingredients']
			if request.method == 'POST':
				startDispensing(name)
	return render_template('recipe.html', name=name, description=description, directions=directions, ingredients=ingredients)


# Read direction
@app.route('/direction/<string:name>/<string:step>')
@is_logged_in
def direction(name, step):
	readDirection(name, int(step)-1)
	return redirect(url_for('recipe', name=name))	


# Register form class
class RegisterForm(Form):
	name = StringField('Name', [validators.Length(min=1, max=50)])
	username = StringField('Userame', [validators.Length(min=4, max=25)])
	email = StringField('Email', [validators.Length(min=6, max=50)])
	password = PasswordField('Password', [
		validators.DataRequired(),
		validators.EqualTo('confirm', message='Passwords do not match')
	])
	confirm = PasswordField('Confirm Password')
	

# User register
@app.route('/register', methods=['GET', 'POST'])
def register():
	form = RegisterForm(request.form)
	if request.method == 'POST' and form.validate():
		name = form.name.data
		email = form.email.data
		username = form.username.data
		password = sha256_crypt.encrypt(str(form.password.data))

		# Create cursor
		cur = mysql.connection.cursor()
		
		# Execute
		cur.execute("INSERT INTO users(name, email, username, password) VALUES(%s, %s, %s, %s)", (name, email, username, password))
		
		# Commit
		mysql.connection.commit()

		# Close
		cur.close()

		flash('You are now registered and can log in', 'success')

		return redirect(url_for('login'))	
	return render_template('register.html', form=form)


# user login
@app.route('/login', methods=['GET', 'POST'])
def login():
	if request.method == 'POST':
		# get form fields
		username = request.form['username']
		password_candidate = request.form['password']
		
		# create cursor
		cur = mysql.connection.cursor()

		# get user by username
		result = cur.execute("SELECT * FROM users WHERE username = %s", [username])

		if result > 0:
			# Get stored hash
			data = cur.fetchone()
			password = data['password']
			
			# compare passwords
			if sha256_crypt.verify(password_candidate, password):
				# passes
				session['logged_in'] = True
				session['username'] = username
				flash('You are now logged in', 'success')
				return redirect(url_for('dashboard'))
			
			else:
				error = 'Invalid login'
				return render_template('login.html', error=error)				

			# close connection
			cur.close()
			
		else:
			error = 'Username not found'
			return render_template('login.html', error=error)
		
	return render_template('login.html')



# Logout
@app.route('/logout')
def logout():
	session.clear()
	flash('You are now logged out', 'success')
	return redirect(url_for('login'))
	
	
# Dashboard
@app.route('/dashboard')
@is_logged_in
def dashboard():
	return render_template('dashboard.html')
	
	

if __name__ == '__main__':
   app.config['SECRET_KEY'] = 'senior design secret'
   app.run(debug = True)
   
