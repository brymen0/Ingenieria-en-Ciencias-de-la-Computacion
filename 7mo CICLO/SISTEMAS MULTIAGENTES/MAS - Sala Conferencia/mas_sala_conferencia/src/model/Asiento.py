class Asiento:
    def __init__(self, id, estado="libre"):
        self.id = id
        self.estado = estado  

    def ocupar(self):
        self.estado = "ocupada"

    def liberar(self):
        self.estado = "libre"

    def esta_libre(self):
        return self.estado == "libre"