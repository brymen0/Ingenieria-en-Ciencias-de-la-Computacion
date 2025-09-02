import base64
from Crypto.Cipher import AES
from agents.agente_base import AgentBase

RABBIT_HOST = "186.43.217.213"
RABBIT_USER = "user"
RABBIT_PASS = "user"

class AgenteDeteccionAmenazas(AgentBase):
    def __init__(self):
        super().__init__(
            name="AgenteDeteccionAmenazas",
            rabbit_host=RABBIT_HOST,
            rabbit_user=RABBIT_USER,
            rabbit_pass=RABBIT_PASS
        )
        self.key = b"0123456789abcdef"
        self.spam_words = ["dinero gratis", "haz ganado", "ganaste un auto"]
        self.start()

    def handle_message(self, msg):
        perf    = msg.get("performative")
        content = msg.get("content", {})
        if perf == "request" and content.get("action") == "scan":
            iv_b64 = content.get("iv", "")
            ct_b64 = content.get("cipher", "")
            iv = base64.b64decode(iv_b64)
            ct = base64.b64decode(ct_b64)
            cipher = AES.new(self.key, AES.MODE_CFB, iv=iv)
            pt_bytes = cipher.decrypt(ct)
            texto = pt_bytes.decode(errors="ignore").lower()
            safe = True
            for word in self.spam_words:
                if word in texto:
                    safe = False
                    break
            response = {
                "from":    content.get("from"),
                "to":      content.get("to"),
                "iv":      iv_b64,
                "cipher":  ct_b64,
                "subject": content.get("subject", ""),
                "safe":    safe
            }
            self.send_acl(
                "inform",
                "AgenteEnvio",
                response
            )
