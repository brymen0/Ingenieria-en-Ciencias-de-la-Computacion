from Agent import Agent
class AgenteAcceso(Agent):
    def receive_message(self, message):
        super().receive_message(message)
        if message["tipo"] == "asientos":
            disponibles = message["disponibles"]
            print(f"[{self.name}] Asientos disponibles: {disponibles}")
            if disponibles <= 0:
                print(f"[{self.name}] Aforo completo. No permitir ingreso.")