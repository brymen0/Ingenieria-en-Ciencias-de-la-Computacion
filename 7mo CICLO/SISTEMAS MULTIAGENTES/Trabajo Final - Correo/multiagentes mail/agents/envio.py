import json
import pika
from agents.agente_base import AgentBase
from pika import BasicProperties

RABBIT_HOST = "186.43.217.213"
RABBIT_USER = "user"
RABBIT_PASS = "user"
EMAIL_EXCHANGE = "emails"
ACL_EXCHANGE   = "fipa_acl"

class AgenteEnvio(AgentBase):
    def __init__(self):
        super().__init__(
            name="AgenteEnvio",
            rabbit_host=RABBIT_HOST,
            rabbit_user=RABBIT_USER,
            rabbit_pass=RABBIT_PASS
        )
        creds = pika.PlainCredentials(RABBIT_USER, RABBIT_PASS)
        params = pika.ConnectionParameters(host=RABBIT_HOST, credentials=creds)
        self.email_conn = pika.BlockingConnection(params)
        self.email_channel = self.email_conn.channel()
        self.email_channel.exchange_declare(
            exchange=EMAIL_EXCHANGE,
            exchange_type='direct',
            durable=True
        )
        self.start()

    def handle_message(self, msg):
        perf    = msg.get("performative")
        content = msg.get("content", {})
        if perf == "request" and content.get("action") == "send_email":
            remitente    = content.get("from")
            destinatario = content.get("to")
            asunto       = content.get("subject")
            cuerpo       = content.get("body")
            if not destinatario or not cuerpo:
                self.send_acl(
                    "inform",
                    remitente,
                    {"status": "error", "reason": "Faltan campos (to o body)"}
                )
                return
            self.send_acl(
                "request",
                "AgenteCriptografico",
                {
                    "action":  "encrypt",
                    "from":    remitente,
                    "to":      destinatario,
                    "subject": asunto,
                    "body":    cuerpo
                }
            )
        elif perf == "inform" and msg.get("sender") == "AgenteCriptografico":
            cifrado = content
            self.send_acl(
                "request",
                "AgenteDeteccionAmenazas",
                {
                    "action": "scan",
                    "from":   cifrado["from"],
                    "to":     cifrado["to"],
                    "iv":     cifrado["iv"],
                    "cipher": cifrado["cipher"],
                    "subject": cifrado.get("subject", "")
                }
            )
        elif perf == "inform" and msg.get("sender") == "AgenteDeteccionAmenazas":
            resultado = content
            if not resultado.get("safe", False):
                self.send_acl(
                    "inform",
                    "AgenteNotificacion",
                    {
                        "from":    "FiltroSpam",
                        "to":      resultado["from"],
                        "subject": f"Correo BLOQUEADO: {resultado.get('subject', '')}",
                        "body":    "Tu correo ha sido bloqueado porque contiene SPAM."
                    }
                )
            else:
                self.send_acl(
                    "request",
                    "AgenteEnrutamiento",
                    {
                        "from":    resultado["from"],
                        "to":      resultado["to"],
                        "iv":      resultado["iv"],
                        "cipher":  resultado["cipher"],
                        "subject": resultado.get("subject", "")
                    }
                )
        elif perf == "inform" and msg.get("sender") == "AgenteEnrutamiento":
            payload = content.get("payload", content)
            self.email_channel.basic_publish(
                exchange=EMAIL_EXCHANGE,
                routing_key=payload["to"],
                body=json.dumps(payload),
                properties=BasicProperties(delivery_mode=2)
            )
