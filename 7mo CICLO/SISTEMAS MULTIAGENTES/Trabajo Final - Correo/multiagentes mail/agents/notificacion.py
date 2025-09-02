from agents.agente_base import AgentBase

RABBIT_HOST  = "186.43.217.213"
RABBIT_USER  = "user"
RABBIT_PASS  = "user"
ACL_EXCHANGE = "fipa_acl"

class AgenteNotificacion(AgentBase):
    def __init__(self):
        super().__init__(
            name="AgenteNotificacion",
            rabbit_host=RABBIT_HOST,
            rabbit_user=RABBIT_USER,
            rabbit_pass=RABBIT_PASS
        )
        self.start()

    def handle_message(self, msg):
        if msg.get("performative") == "inform":
            contenido = msg.get("content", {})
            destinatario = contenido.get("to")
            self.send_acl(
                "inform",
                destinatario,
                contenido
            )
