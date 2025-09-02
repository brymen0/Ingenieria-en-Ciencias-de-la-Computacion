class Ventanilla:
    def __init__(self, id, estado="libre"):
        self.id = id
        self.estado = estado  
        self.persona_actual = None  

    def atender(self, persona):
        self.persona_actual = persona
        self.estado = "ocupada"
        persona.estado = "siendo atendida"

    def liberar(self):
        if self.persona_actual:
            self.persona_actual.estado = "atendida"
        self.persona_actual = None
        self.estado = "libre"

    def esta_libre(self):
        return self.estado == "libre"