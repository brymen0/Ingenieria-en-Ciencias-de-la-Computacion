from Agent import Agent
class AgentePonencia(Agent):
    def __init__(self, name, bus):
        super().__init__(name, bus)
        self.cronograma = {}

    def iniciar_ponencia(self, ponente):
        print(f"[{self.name}] Iniciando ponencia de {ponente}")
        self.send_message("AgenteControlEnergia", {"tipo": "ponencia", "ponente": ponente})