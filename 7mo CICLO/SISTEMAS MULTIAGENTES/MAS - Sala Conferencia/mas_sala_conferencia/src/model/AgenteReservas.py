from Agent import Agent
class AgenteReservas(Agent):
    def __init__(self, name, bus):
        super().__init__(name, bus)
        self.reservas = []

    def nueva_reserva(self, usuario, hora):
        self.reservas.append((usuario, hora))
        print(f"[{self.name}] Reserva registrada para {usuario} a las {hora}")