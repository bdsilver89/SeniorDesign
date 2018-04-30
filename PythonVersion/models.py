from app import db

class User(db.Model):
	id = db.Column(db.Integer, primary_key=True)
	name = db.Column(db.String(100))
	email = db.Column(db.String(100))
	username = db.Column(db.String(100))
	password = db.Column(db.String(100))

	def __init__(self, name, email, username, password):
		self.name = name
		self.email = email
		self.username = username
		self.password = password
		
# new_transaction = User('ask', 5, 10, 'Gdax', 'BTC')
# db.session.add(new_transaction)
# db.session.commit()
