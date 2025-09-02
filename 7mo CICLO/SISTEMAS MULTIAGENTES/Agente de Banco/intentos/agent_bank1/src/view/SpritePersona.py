import pygame
from model.constantes import ESTADOS_FILA
class SpritePersona(pygame.sprite.Sprite):
    def __init__(self, persona, tipo_imagen, *groups):
        super().__init__(*groups)
        self.persona = persona
        self.tipo_imagen = tipo_imagen
        self.image = pygame.image.load(f"resources/{tipo_imagen}.png").convert_alpha()

        self.pos_x, self.pos_y = 935,700  # punto de entrada
        self.rect = self.image.get_rect(topleft=(self.pos_x, self.pos_y))
        self.index_cola = 0 #inicialmente
        #self.destinos = []  # Lista de pasos por recorrer
        self.destino_actual = None
        self.velocidad = 2
        self.en_ventanilla = False  # Estado especial

    def update_destino (self, destino): self.destino_actual = tuple(destino)

    '''
    def actualizar_destino(self, lista_destinos):
        """Recibe una lista de destinos [[x1, y1], [x2, y2], ...] y las convierte en tuplas"""
        self.destinos = [tuple(dest) for dest in lista_destinos]  # Convertir elementos a tuplas
        if self.destinos: self.destino_actual = self.destinos.pop(0) '''

    def mover_hacia_destino(self):
        """Mueve la persona de manera progresiva hasta su destino."""
        if not self.destino_actual:
            return
        #print(f"Moviendo hacia {self.destino_actual} desde ({self.pos_x}, {self.pos_y})")
        dx, dy = self.destino_actual
        dir_x = dx - self.pos_x
        dir_y = dy - self.pos_y
        dist = (dir_x ** 2 + dir_y ** 2) ** 0.5

        if dist <= self.velocidad:
            # Si ya está en su destino, actualizar su posición final
            self.pos_x, self.pos_y = dx, dy
            self.rect.topleft = (int(self.pos_x), int(self.pos_y))
            self.destino_actual = None  # Se queda quieto al llegar
        elif dist > 0:
            # Movimiento gradual hacia el destino
            paso_x = self.velocidad * dir_x / dist
            paso_y = self.velocidad * dir_y / dist
            self.pos_x += paso_x
            self.pos_y += paso_y
            self.rect.topleft = (int(self.pos_x), int(self.pos_y))

    def mover_hacia_destino1(self):
        if not self.destino_actual:
            return
        dx, dy = self.destino_actual
        dir_x = dx - self.pos_x
        dir_y = dy - self.pos_y
        dist = (dir_x ** 2 + dir_y ** 2) ** 0.5

        if dist <= self.velocidad:
            self.pos_x, self.pos_y = dx, dy
            self.rect.topleft = (int(self.pos_x), int(self.pos_y))

            # Al llegar, avanzar al siguiente destino
            if self.destinos:
                self.destino_actual = self.destinos.pop(0)
            else:
                self.destino_actual = None  # Se queda quieto
        elif dist > 0:
            paso_x = self.velocidad * dir_x / dist
            paso_y = self.velocidad * dir_y / dist
            self.pos_x += paso_x
            self.pos_y += paso_y
            self.rect.topleft = (int(self.pos_x), int(self.pos_y))

    '''
    def llego_al_destino(self):
        """Devuelve True si llegó y no tiene más pasos pendientes"""
        return self.destino_actual is None'''

    def update(self):
        self.mover_hacia_destino()
