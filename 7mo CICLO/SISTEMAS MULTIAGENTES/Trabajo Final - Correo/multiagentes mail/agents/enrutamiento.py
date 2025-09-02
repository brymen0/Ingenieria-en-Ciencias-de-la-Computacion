from agents.agente_base import AgentBase

RABBIT_HOST = "186.43.217.213"
RABBIT_USER = "user"
RABBIT_PASS = "user"
ACL_EXCHANGE = "fipa_acl"

class AgenteEnrutamiento(AgentBase):
    def __init__(self):
        super().__init__(
            name="AgenteEnrutamiento",
            rabbit_host=RABBIT_HOST,
            rabbit_user=RABBIT_USER,
            rabbit_pass=RABBIT_PASS
        )
        self.start()

    def handle_message(self, msg):
        perf    = msg.get("performative")
        content = msg.get("content", {})

        if perf == "request" and content.get("action") is None:
            destino = content.get("to")
            payload = {
                "from":    content.get("from"),
                "to":      destino,
                "iv":      content.get("iv"),
                "cipher":  content.get("cipher"),
                "subject": content.get("subject")
            }
            self.send_acl(
                "inform",
                "AgenteEnvio",
                {"payload": payload, "route": "direct"}
            )

