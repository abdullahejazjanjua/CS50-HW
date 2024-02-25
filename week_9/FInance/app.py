import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    result = db.execute("SELECT * FROM Stocks WHERE user_id = ?", session["user_id"])
    stocks_info = []
    for row in result:
        symbol = row["Symbol"]
        stock = lookup(symbol)
        stock["Shares"] = row["Shares"]
        stock["Symbol"] = row["Symbol"]
        stock["TotalA"] = usd(stock["price"] * row["Shares"])
        if stock is not None:
            stocks_info.append(stock)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
        "cash"
    ]
    sum = 0
    for stock in stocks_info:
        sum += stock["Shares"] * stock["price"]
    sum += cash
    Fcash = usd(cash)
    Fsum = usd(sum)
    return render_template("index.html", stocks_info=stocks_info, Fcash=Fcash, Fsum=Fsum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol_input = request.form.get("symbol")
        if not symbol_input:
            return apology("Missing symbol")

        shares = request.form.get("shares")
        if shares.isdigit():
            shares = float(shares)
            if shares < 0 or shares % 1 != 0 or not shares:
                return apology("Invalid number of shares")
            else:
                shares = int(shares)
        else:
            return apology("Enter a digit")

        stock = lookup(symbol_input)
        if stock is None:
            return apology("Invalid symbol")

        price = stock["price"]
        total_cost = price * shares

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
            "cash"
        ]
        if total_cost > cash:
            return apology("Not enough cash")

        new_cash = cash - total_cost
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"]
        )

        existing_shares = db.execute(
            "SELECT Shares FROM stocks WHERE user_id = ? AND Symbol = ?",
            session["user_id"],
            symbol_input,
        )
        if existing_shares:
            new_shares = existing_shares[0]["Shares"] + shares
            db.execute(
                "UPDATE stocks SET Shares = ? WHERE user_id = ? AND Symbol = ?",
                new_shares,
                session["user_id"],
                symbol_input,
            )
        else:
            db.execute(
                "INSERT INTO stocks (user_id, Symbol, Shares) VALUES (?, ?, ?)",
                session["user_id"],
                symbol_input,
                shares,
            )
        db.execute(
            "INSERT INTO History (Symbol, Shares, Price, Transacted, user_id) VALUES (?, ?, ?, datetime('now'), ?)",
            symbol_input,
            shares,
            price,
            session["user_id"],
        )
        return redirect("/")

    elif request.method == "GET":
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    result = db.execute("SELECT * FROM History WHERE user_id = ?", session["user_id"])
    stocks_info = []
    for row in result:
        symbol = row["Symbol"]
        stock = lookup(symbol)
        stock["Shares"] = row["Shares"]
        stock["Symbol"] = row["Symbol"]
        stock["TotalA"] = usd(stock["price"] * row["Shares"])
        stock["Transacted"] = row["Transacted"]
        if stock is not None:
            stocks_info.append(stock)
    return render_template("history.html", stocks_info=stocks_info)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    """Get stock quote."""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Symbol doesnt exist")
        else:
            formated_price = usd(quote['price'])
            return render_template("quoted.html", quote=quote, formated_price=formated_price)
    elif request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        user_name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("Password is NOT matching")
        elif not user_name or not password or not confirmation:
            return apology("Dont leave any field blank")
        else:
            existing_user = db.execute(
                "SELECT * FROM users WHERE username = ?", user_name
            )
            hashed_password = generate_password_hash(password)

            if len(existing_user) != 0:
                return apology("User already exists")
            else:
                db.execute(
                    "INSERT INTO users (username, hash) VALUES(?,?)",
                    user_name,
                    hashed_password,
                )
                return redirect("/login")

    elif request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol_input = request.form.get("symbol")
        shares_input = float(request.form.get("shares"))
        if shares_input <= 0 or shares_input % 1 != 0:
            return apology("Invalid number of shares")
        else:
            shares_input = int(shares_input)

        stock = lookup(symbol_input)
        if stock is None:
            return apology("Invalid symbol")

        user_shares = db.execute(
            "SELECT Shares FROM stocks WHERE user_id = ? AND Symbol = ?",
            session["user_id"],
            symbol_input,
        )
        if not user_shares or user_shares[0]["Shares"] < shares_input:
            return apology("Not enough shares to sell")

        price = stock["price"]
        total_earnings = price * shares_input

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
            "cash"
        ]
        new_cash = cash + total_earnings
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"]
        )

        new_shares = user_shares[0]["Shares"] - shares_input
        if new_shares == 0:
            db.execute(
                "DELETE FROM stocks WHERE user_id = ? AND Symbol = ?",
                session["user_id"],
                symbol_input,
            )
        else:
            db.execute(
                "UPDATE stocks SET Shares = ? WHERE user_id = ? AND Symbol = ?",
                new_shares,
                session["user_id"],
                symbol_input,
            )
        db.execute(
            "INSERT INTO History (Symbol, Shares, Price, Transacted, user_id) VALUES (?, ?, ?, datetime('now'), ?)",
            symbol_input,
            -1 * shares_input,
            price,
            session["user_id"],
        )
        return redirect("/")

    elif request.method == "GET":
        symbols = db.execute("SELECT Symbol FROM stocks WHERE user_id = ?", session["user_id"])
        symbols = [symbol['Symbol'] for symbol in symbols]
        return render_template("sell.html", symbols=symbols)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():

    if request.method == "POST":
        amount = float(request.form.get("Amount"))
        if not amount or amount % 1 != 0:
            return apology("Invalid amount")
        else:
            amount = int(amount)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
            "cash"
        ]
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", amount + cash, session["user_id"]
        )
        return redirect("/")

    elif request.method == "GET":
        return render_template("add.html")
