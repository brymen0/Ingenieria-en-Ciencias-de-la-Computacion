class Persona:
    def __init__(self, edad, embarazada=False, bebe_en_brazos=False, discapacidad=False):
        self.edad = edad
        self.embarazada = embarazada
        self.bebe_en_brazos = bebe_en_brazos
        self.discapacidad = discapacidad
        self.estado = "esperando"  # puede ser: 'esperando', 'siendo atendida', 'atendida'

    def es_prioritaria(self):
        return (
            self.edad >= 60
            or self.embarazada
            or self.bebe_en_brazos
            or self.discapacidad
        )