class FilaBanco:
    def __init__(self, ventanillas):
        self.cola = [] 
        self.ventanillas = ventanillas  

    def agregar_persona(self, persona):
        if persona.es_prioritaria():
            for i, p in enumerate(self.cola):
                if not p.es_prioritaria():
                    self.cola.insert(i, persona)
                    return
            self.cola.append(persona)  
        else:
            self.cola.append(persona)

    def asignar_ventanilla(self, ventanilla):
        if self.cola and ventanilla.esta_libre():
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
