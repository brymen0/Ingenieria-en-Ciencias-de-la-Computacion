import pika, threading, json

class AgentBase:
    def __init__(self, name, rabbit_host="186.43.217.213", rabbit_user="user", rabbit_pass="user"):
        self.name = name

        creds = pika.PlainCredentials(rabbit_user, rabbit_pass)
        params = pika.ConnectionParameters(
            host=rabbit_host,
            credentials=creds,
            heartbeat=60,      
            blocked_connection_timeout=30
        )

        self.conn    = pika.BlockingConnection(params)
        self.channel = self.conn.channel()

        self.channel.exchange_declare(
            exchange="fipa_acl",
            exchange_type="topic",
            durable=True
        )

        self.channel.queue_declare(queue=self.name, durable=True)
        self.channel.queue_bind(
            queue=self.name,
            exchange="fipa_acl",
            routing_key=self.name
        )

    def send_acl(self, performative, receiver, content):
        msg = {
            "performative": performative,
            "sender":       self.name,
            "receiver":     receiver,
            "ontology":     "email",
            "content":      content
        }
        self.channel.basic_publish(
            exchange="fipa_acl",
            routing_key=receiver,
            body=json.dumps(msg),
            properties=pika.BasicProperties(delivery_mode=2)
        )

    def start(self):
        def on_message(ch, method, props, body):
            msg = json.loads(body)
            self.handle_message(msg)

        threading.Thread(
            target=lambda: (self.channel.basic_consume(
                                queue=self.name,
                                on_message_callback=on_message,
                                auto_ack=True
                             ), self.channel.start_consuming()),
            daemon=True
        ).start()
