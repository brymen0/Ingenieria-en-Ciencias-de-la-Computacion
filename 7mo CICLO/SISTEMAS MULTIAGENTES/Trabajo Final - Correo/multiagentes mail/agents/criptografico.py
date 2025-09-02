import base64
import threading
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from agents.agente_base import AgentBase

RABBIT_HOST = "186.43.217.213"
RABBIT_USER = "user"
RABBIT_PASS = "user"
ACL_EXCHANGE = "fipa_acl"

class AgenteCriptografico(AgentBase):
    def __init__(self):
        super().__init__(
            name="AgenteCriptografico",
            rabbit_host=RABBIT_HOST,
            rabbit_user=RABBIT_USER,
            rabbit_pass=RABBIT_PASS
        )
        self.key = b"0123456789abcdef"
        self.start()

    def handle_message(self, msg):
        print("[AgenteCriptografico] recibe:", msg["content"])
        perf    = msg.get("performative")
        content = msg.get("content", {})
        if perf == "request" and content.get("action") == "encrypt":
            iv    = get_random_bytes(16)
            cipher = AES.new(self.key, AES.MODE_CFB, iv=iv)
            pt = content.get("body", "").encode()
            ct = cipher.encrypt(pt)

            payload = {
                "from":    content["from"],
                "to":      content["to"],
                "subject": content.get("subject", ""),
                "iv":      base64.b64encode(iv).decode(),
                "cipher":  base64.b64encode(ct).decode()
            }
            self.send_acl("inform", msg["sender"], payload)

        elif perf == "request" and content.get("action") == "decrypt":
            iv_b64 = content.get("iv", "")
            ct_b64 = content.get("cipher", "")
            iv = base64.b64decode(iv_b64)
            ct = base64.b64decode(ct_b64)

            cipher = AES.new(self.key, AES.MODE_CFB, iv=iv)
            pt = cipher.decrypt(ct)
            body = pt.decode(errors="ignore")

            payload = {
                "from":    content["from"],
                "to":      content["to"],
                "subject": content.get("subject", ""),
                "body":    body
            }
            self.send_acl("inform", msg["sender"], payload)
