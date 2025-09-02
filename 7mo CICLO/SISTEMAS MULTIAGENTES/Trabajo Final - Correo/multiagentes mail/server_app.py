from flask import Flask, request, jsonify
import sqlite3
import pika
import os

BASE_DIR    = os.path.dirname(__file__)
DB_PATH     = os.path.join(BASE_DIR, "db", "correo.db")
API_PORT    = 5000
RABBIT_HOST = "localhost"

app = Flask(__name__)

def get_db():
    return sqlite3.connect(DB_PATH)

@app.route("/login", methods=["POST"])
def login():
    data   = request.json
    correo = data.get("correo")
    clave  = data.get("password")
    conn   = get_db()
    cur    = conn.cursor()
    cur.execute("SELECT 1 FROM usuarios WHERE correo=? AND password=?", (correo, clave))
    exists = cur.fetchone() is not None
    conn.close()
    if exists:
        return jsonify({"success": True})
    return jsonify({"success": False, "error": "Credenciales inválidas"}), 401

@app.route("/users", methods=["GET"])
def users():
    conn = get_db()
    cur  = conn.cursor()
    cur.execute("SELECT correo FROM usuarios")
    lista = [r[0] for r in cur.fetchall()]
    conn.close()
    return jsonify({"users": lista})

def setup_rabbitmq():
    conn    = pika.BlockingConnection(pika.ConnectionParameters(host=RABBIT_HOST))
    channel = conn.channel()
    channel.exchange_declare(exchange="emails",   exchange_type="direct", durable=True)
    channel.exchange_declare(exchange="fipa_acl", exchange_type="topic",  durable=True)
    db = sqlite3.connect(DB_PATH)
    cur= db.cursor()
    cur.execute("SELECT correo FROM usuarios")
    for (correo,) in cur.fetchall():
        channel.queue_declare(queue=correo, durable=True)
        channel.queue_bind  (queue=correo, exchange="emails",    routing_key=correo)
        channel.queue_declare(queue=correo + "_acl", durable=True)
        channel.queue_bind  (queue=correo + "_acl",
                             exchange="fipa_acl",
                             routing_key=correo)
    db.close()
    agentes = [
        "AgenteEnvio",
        "AgenteCriptografico",
        "AgenteEnrutamiento",
        "AgenteDeteccionAmenazas",
        "AgenteRecepcion",
        "AgenteNotificacion"
    ]
    for ag in agentes:
        channel.queue_declare(queue=ag, durable=True)
        channel.queue_bind  (queue=ag, exchange="fipa_acl", routing_key=ag)

    conn.close()

if __name__ == "__main__":
    setup_rabbitmq()
    app.run(host="0.0.0.0", port=API_PORT)
