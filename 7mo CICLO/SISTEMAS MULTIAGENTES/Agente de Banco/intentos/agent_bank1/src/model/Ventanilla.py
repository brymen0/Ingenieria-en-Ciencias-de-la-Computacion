import pygame  # Es necesario para usar pygame.time.get_ticks()

class Ventanilla:
    def __init__(self, id, estado="libre"):
        self.id = id
        self.estado = estado  
        self.persona_actual = None  
        self.tiempo_inicio_atencion = None  # Nuevo: para controlar el tiempo de atención

    def atender(self, persona):
        self.persona_actual = persona
        self.estado = "ocupada"
        persona.estado = "siendo atendida"
        self.tiempo_inicio_atencion = pygame.time.get_ticks()  # Registra el instante de inicio

    def liberar(self):
        if self.persona_actual:
            self.persona_actual.estado = "atendida"
        self.persona_actual = None
        self.estado = "libre"
        self.tiempo_inicio_atencion = None

    def esta_libre(self):
        return self.estado == "libre"
