from Agent import Agent
class AgenteOcupacion(Agent):
    def __init__(self, name, bus):
        super().__init__(name, bus)
        self.ocupacion = 0

    def contar_personas(self, cantidad):
        self.ocupacion = cantidad
        self.send_message("AgenteControlTemperatura", {"tipo": "ocupacion", "valor": self.ocupacion})
        self.send_message("AgenteAcceso", {"tipo": "asientos", "disponibles": 50 - self.ocupacion})