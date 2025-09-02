class FilaBanco:
    def __init__(self, ventanillas):
        self.cola = [] 
        self.ventanillas = ventanillas  

    def agregar_persona(self, persona):
        self.cola.append(persona)

    def asignar_ventanilla(self, ventanilla):
        if self.cola:
            persona = self.cola.pop(0)
            ventanilla.atender(persona)  
            return persona
        return None

    def liberar_ventanilla(self, id_ventanilla):
        for v in self.ventanillas:
            if v.id == id_ventanilla:
                v.estado = "libre"

    def proxima_persona(self):
        if not self.cola:
            return None
        return sorted(self.cola, key=lambda p: p.es_prioritaria())[0]
