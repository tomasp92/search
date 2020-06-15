import os

from datetime import datetime, timedelta
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # variable wich shows cash available
    cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])

    rows = db.execute("SELECT * FROM stocks WHERE user_id = :userid", userid=session["user_id"])
    sums = 0
    for row in rows:
        symbol = lookup(row["symbol"])
        row["price"] = symbol["price"]
        row["total"] = float(symbol["price"]) * int(row["shares"])
        sums= row["total"] + sums

    sumtot = sums + cash[0]["cash"]

    return render_template("index.html", cash=cash, rows=rows, sumtot=sumtot)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template ("buy.html")
    else:
        symbol = lookup(request.form.get("symbol"))
        if symbol == None:
            return apology("INVALID SYMBOL")
        else:
            cost = symbol["price"] * int(request.form.get("shares"))
            cash_dict = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])
            username = db.execute("SELECT username FROM users WHERE id = :userid", userid=session["user_id"])

            cash = cash_dict[0]["cash"]

            # Can the user aford it?
            if cost < cash:

                # Insert in table history this particular transaction
                db.execute("INSERT INTO 'history' ('user_id', 'symbol', 'shares', 'price', 'datetime') VALUES (:user_id, :symbol, :shares, :price, :datetime)",
                user_id=session["user_id"],symbol=symbol ["symbol"], shares=request.form.get("shares"), price=symbol["price"], datetime= datetime.now())

                # Charge the user for the stock and update its cash
                cash = cash - cost
                db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash, user_id=session["user_id"])

                # Update stocks that the user currently has
                owned_stock = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                          user_id=session["user_id"], symbol=symbol["symbol"])
                # Check wether the user already has the stock
                if len(owned_stock) == 0:
                    #If it does not insert
                    db.execute("INSERT INTO 'stocks' ('user_id', 'symbol','company_name', 'shares') VALUES (:user_id, :symbol, :company_name, :shares)",
                    user_id=session["user_id"],symbol=symbol ["symbol"], company_name=symbol ["name"], shares=request.form.get("shares"))

                # Else Update
                else:

                    # new_shares = past_shares + shares
                    old_shares = db.execute("SELECT shares FROM stocks WHERE user_id = :user_id AND symbol = :symbol", user_id=session["user_id"], symbol=symbol ["symbol"])
                    new_shares= old_shares [0]["shares"] + int(request.form.get("shares"))

                    #  Update
                    db.execute("UPDATE stocks SET shares = :new_shares WHERE user_id = :user_id AND symbol = :symbol",
                    user_id=session["user_id"], new_shares=new_shares, symbol=symbol ["symbol"])
                return redirect ("/")
            else:
                return apology("YOU CAN´T AFFORD IT")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * FROM history WHERE user_id = :userid", userid=session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "GET":
        return render_template ("quote.html", s = "no")
    else:
        symbol = lookup(request.form.get("symbol"))
        if symbol == None:
            return apology("INVALID SYMBOL")
        else:
            return render_template ("quote.html", s = "yes", symbol = symbol)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must confirm password", 403)

        #Chek paswords are the same
        elif request.form.get("password") != request.form.get("passwordconfirmation"):
            return apology("passwords don´t match", 403)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username does not exist
        if len(rows) != 0:
            return apology("username is not available", 403)

        password = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO 'users' ('username', 'hash') VALUES (:username, :password)",username=request.form.get("username"),password=password)

        login()

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    rows = db.execute("SELECT * FROM stocks WHERE user_id = :userid", userid=session["user_id"])

    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        sold_shares = request.form.get("shares")
        stock = db.execute("SELECT * FROM stocks WHERE user_id = :userid AND symbol = :symbol", userid=session["user_id"], symbol=symbol["symbol"])
        if int(sold_shares) > stock[0]["shares"]:
            return apology("TOO MANY SHARES")
        else:
            cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])
            new_cash = symbol["price"]* int(sold_shares) + cash[0]["cash"]
            db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=new_cash, user_id=session["user_id"])
            update_shares = int(sold_shares) * -1
            db.execute("INSERT INTO 'history' ('user_id', 'symbol', 'shares', 'price', 'datetime') VALUES (:user_id, :symbol, :shares, :price, :datetime)",
            user_id=session["user_id"],symbol=symbol ["symbol"], shares=update_shares, price=symbol["price"], datetime=datetime.now())

            if int(sold_shares) == stock[0]["shares"]:
                db.execute("DELETE FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                    user_id=session["user_id"], symbol=symbol ["symbol"])
                return redirect("/")
            else:
                new_shares = stock[0]["shares"] - int(sold_shares)
                db.execute("UPDATE stocks SET shares = :new_shares WHERE user_id = :user_id AND symbol = :symbol",
                    user_id=session["user_id"], new_shares=new_shares, symbol=symbol ["symbol"])
                return redirect("/")

    else:
        return render_template("sell.html", rows=rows)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add Cash"""

    if request.method == "POST":
        cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])
        cash_amount = request.form.get("cash_amount")
        new_cash = cash[0]["cash"] + int(cash_amount)
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=new_cash, user_id=session["user_id"])
        return redirect("/")
    else:
        return render_template("add_cash.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
