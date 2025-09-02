import sqlite3
import os

DB_PATH = os.path.join(os.path.dirname(__file__), "correo.db")

def init_db():
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute("""
    CREATE TABLE IF NOT EXISTS usuarios (
        id       INTEGER PRIMARY KEY AUTOINCREMENT,
        correo   TEXT UNIQUE NOT NULL,
        password TEXT NOT NULL
    );
    """)
    cur.execute("INSERT OR IGNORE INTO usuarios (correo,password) VALUES (?,?)",
                ("david.romeroa@ejemplo.com","1234"))
    cur.execute("INSERT OR IGNORE INTO usuarios (correo,password) VALUES (?,?)",
                ("bryan.mendoza@ejemplo.com","abcd"))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    init_db()
