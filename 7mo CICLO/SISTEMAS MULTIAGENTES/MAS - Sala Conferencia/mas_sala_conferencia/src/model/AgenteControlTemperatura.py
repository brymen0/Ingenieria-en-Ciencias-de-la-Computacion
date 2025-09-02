from Agent import Agent
class AgenteControlTemperatura(Agent):
    def __init__(self, name, bus):
        super().__init__(name, bus)
        self.ocupacion = 0
        self.temperatura = 22

    def receive_message(self, message):
        super().receive_message(message)
        if message["tipo"] == "ocupacion":
            self.ocupacion = message["valor"]
            self.ajustar_temperatura()
    
    def ajustar_temperatura(self):
        self.temperatura = 20 + int(self.ocupacion / 10)
        print(f"[{self.name}] Temperatura ajustada a {self.temperatura}°C")
        self.send_message("AgenteControlEnergia", {"tipo": "ajuste_clima", "valor": self.temperatura})