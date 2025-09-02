from Agent import Agent
class AgenteControlEnergia(Agent):
    def receive_message(self, message):
        super().receive_message(message)
        if message["tipo"] == "ajuste_clima":
            print(f"[{self.name}] Ajustando energía por nuevo clima: {message['valor']}°C")