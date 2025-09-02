import pika, json, threading
from agents.agente_base import AgentBase
from agents.usuarios import AgenteUsuarios

RABBIT_HOST   = "186.43.217.213"
RABBIT_USER   = "user"
RABBIT_PASS   = "user"
EMAIL_EXCHANGE = "emails"

class AgenteRecepcion(AgentBase):
    def __init__(self):
        super().__init__(
            name="AgenteRecepcion",
            rabbit_host=RABBIT_HOST,
            rabbit_user=RABBIT_USER,
            rabbit_pass=RABBIT_PASS
        )

        creds = pika.PlainCredentials(RABBIT_USER, RABBIT_PASS)
        params = pika.ConnectionParameters(host=RABBIT_HOST, credentials=creds)
        self.conn2 = pika.BlockingConnection(params)
        self.chan2 = self.conn2.channel()
        self.chan2.exchange_declare(
            exchange=EMAIL_EXCHANGE,
            exchange_type="direct",
            durable=True
        )
        self.chan2.queue_declare(queue=self.name, durable=True)
        usuarios = AgenteUsuarios(api_url="http://186.43.217.213:5000").listar()
        for u in usuarios:
            self.chan2.queue_bind(
                queue=self.name,
                exchange=EMAIL_EXCHANGE,
                routing_key=u
            )
        self.start()
        threading.Thread(target=self.consume_emails, daemon=True).start()

    def consume_emails(self):
        def callback(ch, method, props, body):
            m = json.loads(body)
            self.send_acl(
                "request",
                "AgenteCriptografico",
                {
                    "action": "decrypt",
                    "iv":     m.get("iv"),
                    "cipher": m.get("cipher"),
                    "from":   m.get("from"),
                    "to":     m.get("to"),
                    "subject": m.get("subject", "")
                }
            )
        self.chan2.basic_consume(
            queue=self.name,
            on_message_callback=callback,
            auto_ack=True
        )
        self.chan2.start_consuming()

    def handle_message(self, msg):
        if msg.get("performative") == "inform" and msg.get("sender") == "AgenteCriptografico":
            content = msg.get("content", {})
            self.send_acl(
                "inform",
                content.get("to"),
                content
            )
